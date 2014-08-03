/*
 * =====================================================================================
 *
 *       Filename:  chat_server.cc
 *        Version:  1.0
 *        Created:  2014年08月03日 14时49分54秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include "saltadd.h"
//#include <stdio.h>
//#include <muduo/base/Logging.h>
//#include <muduo/net/EventLoop.h>
//#include <muduo/net/TcpServer.h>
//#include <boost/bind.hpp>

#include "chat_server.h"

using namespace muduo;
using namespace muduo::net;
int main(int argc, char *argv[]){
	LOG_INFO << "pid = "<<getpid();
	muduo::net::EventLoop eventloop;
	muduo::net::InetAddress localaddr(9527);
	ChatServer chat_(&eventloop,localaddr);
	chat_.chatstart();
	eventloop.loop();
	return 0;
}

