#include "Acceptor.h"
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include "Session.h"
Acceptor::Acceptor(Reactor*reactor):
reactor_(reactor)
{
	
}

Acceptor::~Acceptor(){
	
}

int Acceptor::open(){
	acceptor_.open(reactor_);

	reactor_->registerHandler(this, READ_EVENT);

	return 0;
}

Session* Acceptor::makeService(){
	auto tmpSession = new Session(0, this->reactor_, &this->handlerManager_);
	
	return(tmpSession);
}

int Acceptor::acceptFin(Session* service){
	service->activate();
	this->handlerManager_.add(service);
}

int Acceptor::handlerInput(int fd){
	auto tmpService = makeService();
	acceptor_.accept(tmpService);
	acceptFin(tmpService);
	return 0;
}

int Acceptor::handlerOutput(int fd){
	return 0;
}

int Acceptor::handlerTimeout(int fd){
	return 0;
}

int Acceptor::handlerClose(int fd){

	return 0;
}

int Acceptor::getHandle(){
	return acceptor_.getHandle();
}

int Acceptor::getEventMask(){

	return this->event_;
}

void Acceptor::enableEventMask(EVENT_TYPE type){
	this->event_ |= type;
}

void Acceptor::disableEventMask(EVENT_TYPE type){
	this->event_ &= (~type);
}

