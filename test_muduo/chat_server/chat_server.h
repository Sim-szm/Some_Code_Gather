/*
 * =====================================================================================
 *
 *       Filename:  chat_server.h
 *        Version:  1.0
 *        Created:  2014年08月03日 11时47分54秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _CHAT_SERVER_H
#define _CHAR_SERVER_H

#ifdef __cpluspluc
extern "C":
{
#endif

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/logging.h>
#include <boost/bind.hpp>
#include <set>

using namespace muduo;
using namespace muduo::net;

#include "saltadd.h"

class ChatServer : boost::noncopyable{
public : 

	ChatServer(EventLoop* loop,
				const InetAddress& localaddr)
	: 	chatserver_(loop,localaddr,"chat_server"),
		salt_(boost::bind(&CharServer::onMessageBack,this,_1,_2,_3)){
		chatserver_.setConnectionCallback(
				boost::bind(&ChatServer::onConnection,this,_1));
		charsever_.setMessageCallback(
				boost::bind(&ChatServer::onMessageSalt,&salt_,_1,_2,_3));
	}
	void chatstart{
		chatserver_.start();
	}

private : 
	void onConnection(const TcpConnectionPtr& conn){
		LOG_INFO << conn->localAddress().toIpPort() << "<-"
			 << conn->peerAddress().toIpPort() << "is"
			 << (conn->connected() ? "connected":"connection failed");
		if(conn->connected()){
			conn_.insert(conn);
		}else{
			conn_.erase(conn);
		}
	}
	void onMessageBack(const TcpConnectionPtr&,
				const muduo::base::string& message,
				Timestamp){
		for(Conn_list::iterator it = conn_.begin();
					it != conn_.end();
					it++){
			salt_.sendback(get_pointer(*it),message);
		}
	}
	TcpServer chatserver_;
	salt salt_;
	typedef std::set<TcpConnectionPtr> Conn_list;
	Conn_list conn_;
};
#ifdef __cplusplus
}
#endif
#endif
