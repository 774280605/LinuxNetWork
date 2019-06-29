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
	this->reactor_->registerHandler(this, READ_EVENT);
}

Session::~Session(){
	this->reactor_->removeHandler(this, READ_EVENT | WRITE_EVENT);
	close(this->fd_);
}

int Session::handlerInput(int fd){

	char buffer[1024] = {0};
	auto bytes = recv(fd, buffer, 1024, 0);
	std::cout << buffer << std::endl;
	if(bytes==0){
		handlerManager_->remove(this);
		return 0;
	}

	const auto msg = "zhangxiaofei";
	uint len = strlen(msg);
	auto tansBytes =  ::send(fd, msg, len, 0);
	


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
	return  this->fd_;
}

int Session::getEventMask(){
	return this->event_;
}

void Session::enableEventMask(EVENT_TYPE type) {
	this->event_ |= type;
}

void Session::disableEventMask(EVENT_TYPE type){
	this->event_ &= (~type);
}

void Session::setHandle(uintmax_t handle){
	this->fd_ = handle;
}
