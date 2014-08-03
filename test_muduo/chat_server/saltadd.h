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
		while(buf->readableBytes() >= headerlen){
			void* data = buf->peek();
			int32_t header = *static_cast<const int32_t*> data;
			int32_t data_len = muduo::net::sockets::networkToHost32(header); 
			//data_len as the message size,also is the message_header
			if(data_len > 65536 || data_len < 0){
				LOG_ERR << "message length error"<<data_len;
				conn->shutdown();//muduo use half-close , if it matters ,change to use close();
				break;
			}else if(buf->readableBytes() >= data_len + headerlen){
				buf->retrieve(headerlen);
				muduo->string messageback(buf->peek(),data_len);
				messagecallback_(conn,messageback,time_);
				buf->retrieve(data_len);
			}else{
				break;
			}
		}
	}
	void sendback(muduo::net::TcpConnection* conn,
				const muduo::StringPiece& message){
		muduo::net::Buffer buf;
		int32_t data_len = static_cast<const int32_t>(message.size());
		int32_t header = muduo::net::ockets::hostToNetwork32(data_len);
		buf.append(&header,sizeof(int32_t));
		buf.append(message.data(),message.size());
		conn->send(&buf);

	}
private :
	MessageCallback messagecallback_;
	const static size_t headerlen = sizeof(int32_t);
};

#ifdef __cplusplus
}
#endif
#endif
