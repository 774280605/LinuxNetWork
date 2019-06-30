#include "SockAcceptor.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <netinet/in.h>
#include "Session.h"
SockAcceptor::SockAcceptor(){
}

SockAcceptor::~SockAcceptor(){
}

int SockAcceptor::open(Reactor* reactor){
	this->setHandle(socket(AF_INET, SOCK_STREAM, 0));
	
	if (this->getHandle()<0){

		return -1;
	}
	auto ret = -1;
	ret = this->enableNoBlocking(true);
	if (ret<0){
		return -1;
	}

	ret = this->setReuseAddrOpt();
	if (ret < 0)
		return -1;

	struct sockaddr_in sin{};
	
	sin.sin_family = AF_INET;
	sin.sin_port = htons(27015);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(this->getHandle(), reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin));
	if (ret<0){
		return -1;
	}

	ret = listen(this->getHandle(), SOMAXCONN);
	if (ret < 0)
		return  -1;
	
	return 0;
}

int SockAcceptor::accept(Session* session){
	
	sockaddr_in sin{};
	uint32_t len{};

	uintmax_t accept = ::accept(this->getHandle(), (struct sockaddr*)&sin, &len);
	if (accept<0){
		return -1;
	}
	session->setHandle(accept);
	

	return 0;
}
