#include "Acceptor.h"
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
Acceptor::Acceptor(){
	listenSocket_ = socket(AF_INET, SOCK_STREAM, 0);
	int ret =- 1;
	int flags = fcntl(listenSocket_, F_GETFL, 0);
	ret= fcntl(listenSocket_, F_SETFL, flags | O_NONBLOCK);

	struct sockaddr_in sin;
	memset(&sin,0,sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(27015);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listenSocket_, (struct sockaddr*)&sin, sizeof(sin));

	ret= listen(listenSocket_, SOMAXCONN);
	if (ret <0)
		std::cout<<"error";
}

Acceptor::~Acceptor(){
	
}

int Acceptor::handlerInput(int fd){

	struct sockaddr_in sin;
	unsigned int len = sizeof(sin);

	int accept = ::accept(listenSocket_, (struct sockaddr*)&sin, &len);
	if (accept==-1){
		return -1;
	}

	auto flags = fcntl(listenSocket_, F_GETFL, 0);
	fcntl(listenSocket_, F_SETFL, flags | O_NONBLOCK);
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
