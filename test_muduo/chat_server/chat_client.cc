/*
 * =====================================================================================
 *
 *       Filename:  chat_client.cc
 *        Version:  1.0
 *        Created:  2014年08月03日 15时57分30秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "saltadd.h"
#include <muduo/base/Mutex.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoopThread.h>
#include <muduo/net/TcpClient.h>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#iinclude <iostream>
#include <stdio.h>
using namespace muduo;
using namespace muduo::net;

class ChatClient : boost::noncopyable{
public :
	ChatClient(EventLoop* loop,
			const InetAddress& serveraddr)
	:chatclient(loop,serveraddr,"chat client"),
	salt_(boost::bind(&ChatClient::onMessage,this,_1,_2,_3)){
		chatclient.setConnectionCallback(
				boost::bind(&ChatClient::onConnection,this,_1));
		chatclient.setMessageCallback(
				boost::bind(&salt::onMessageSalt,&salt_,_1,_2,_3));
		chatclient.enableRetry();
	}

	void connect(){
		chatclient.connect();
	}

	void cut_connect(){
		chatclient.disconnect();
	}

	void write(const StringPiece& message){
		MutexLockGuard lock(mutex_);
		if(conn_){
			salt_.sendback(get_pointer(conn_),message);
		}
	}
private :
	void onConnection(TcpConnectionPtr& conn){
		std::cout<< conn->localAddress().toIpPort() << "->"
			<<conn->peerAddress().toIpPort() << "is"
			<<(conn->connected() ? "connected":"connected failed");
		MutexLockGuard lock(mutex_);
		if(conn->connected()){
			conn_ = conn;
		}else{
			conn_.reset();
		}
	}

	void onMessage(const TcpConnectionPtr& conn,
				const string& message,
				Timestamp){
		printf("%s\n",message.c_str());
	}
	TcpClient chatclient;
	salt salt_;
	MutexLock mutex_;
	TcpConnectionPtr conn_;

};
int main(int argc, char *argv[]){
	LOG_INFO << "pid = "<<getpid();
	EventLoopThread threadloop;
	uint16_t port = static_cast<uint16_t>(atoi(argv[2]));
	InetAddress serveraddr(argv[1],port);
	ChatClient client(threadloop.startLoop(),serveraddr);
	client.connect();
	std::string msg;
	while(std::getline(std::cin,msg)){
		client.write(msg);
	}
	client.cut_connect();
	CurrentThread::sleepUsec(1000*1000);
	return 0;
}

