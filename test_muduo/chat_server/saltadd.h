/*
 * =====================================================================================
 *
 *       Filename:  saltadd.h
 *        Version:  1.0
 *        Created:  2014年08月03日 11时32分12秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#ifndef _SALTADD_H
#define _SALTADD_H

#ifdef __cplusplus
extern "C":
{
#endif

#include <muduo/base/logging.h>
#include <muduo/net/Buffer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/Endian.h>
#include <boost/function.hpp>
#include <boost/noncopyable.h>

class salt : boost::noncopyable { 
public :
	typedef boost::function<void (const muduo::net::TcpConnectionPtr& ,
					const muduo::string& message,
					muduo::Timestamp)>  
		MessageCallback;
	explicit salt(const MessageCallback& cb)
		:messagecallback_(cb){

		}
	void onMessageSalt(const muduo::net::TcpConnectionPtr& conn,
				muduo::net::Buffer *buf,
				muduo::Timestamp time_){
		//...
	}
	void sendback(muduo::net::TcpConnection* conn,
				const muduo::StringPiece& message){


	}
private :
	MessageCallback messagecallback_;
};

#ifdef __cplusplus
}
#endif
#endif
