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
	listenSocket_ = socket(AF_INET, SOCK_STREAM, 0);
	int ret = -1;
	uint reuseaddr = 1;
	ret = setsockopt(listenSocket_, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(uint));
	if(ret<0){
		return -1;
	}

	uint mode = 1;
	ret= ioctl(listenSocket_, FIONBIO, &mode);
	
	if (ret<0){
		return -1;
	}
	struct sockaddr_in sin{};
	sin.sin_family = AF_INET;
	sin.sin_port = htons(27015);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listenSocket_, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin));

	ret = listen(listenSocket_, SOMAXCONN);
	if (ret < 0)
		std::cout << "error";

	reactor_->registerHandler(this, READ_EVENT);

	return 0;
}

int Acceptor::acceptFin(int fd){
	auto tmpSession = new Session(fd,this->reactor_,&this->handlerManager_);
	this->handlerManager_.add(tmpSession);
	return(0);
}

int Acceptor::handlerInput(int fd){

	struct sockaddr_in sin;
	unsigned int len = sizeof(sin);

	const auto accept = ::accept(listenSocket_, reinterpret_cast<struct sockaddr*>(&sin), &len);
	if (accept<0){
		return -1;
	}
	ulong mode = 1;
	auto flag = ioctl(accept, FIONBIO, &mode);
	if(flag<0){		
		perror("ioctl:");
	}
	acceptFin(accept);

	
	return accept;
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
	return listenSocket_;
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

