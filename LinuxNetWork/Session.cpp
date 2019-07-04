#include "Session.h"
#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
Session::Session(int fd, Reactor*reactor, HandlerManager*handlerManager):
fd_(fd),
reactor_(reactor),
handlerManager_(handlerManager)
{
	
}

Session::~Session(){
	this->reactor_->removeHandler(this, static_cast<EVENT_TYPE>(READ_EVENT | WRITE_EVENT));
	close(this->fd_);
}

int Session::handlerInput(int fd){
	/*
	 * 测试：注销read事件
	 */
	//this->reactor_->deactivate(fd, READ_EVENT);


	char buffer[1024] = {0};
	auto bytes = this->stream_.recv(buffer, 1024);
	
	if(bytes==0){
		handlerManager_->remove(this);
		return 0;
	}

	auto msg = (char*)"zhangxiaofei";
	uint len = strlen(msg);
	auto tansBytes = this->stream_.send(static_cast<void*>(msg), len);

	/*
	 * 测试：激活read事件
	 */
	//this->reactor_->reactivate(fd, READ_EVENT);
	return bytes;
}

int Session::handlerOutput(int fd){
	return 0;
}

int Session::handlerTimeout(int fd){
	return 0;
}

int Session::handlerClose(int fd){
	return 0;
}

int Session::getHandle(){
	return  stream_.getHandle();
}

int Session::getEventMask(){
	return this->eventMask_;
}

void Session::enableEventMask(EVENT_TYPE type) {
	this->eventMask_ |= type;
}

void Session::disableEventMask(EVENT_TYPE type){
	this->eventMask_ &= (~type);
}

void Session::setHandle(uintmax_t handle){
	stream_.setHandle( handle);
}

void Session::activate(){
	stream_.enableNoBlocking(true);
	
	this->reactor_->registerHandler(this, READ_EVENT);
	
}
