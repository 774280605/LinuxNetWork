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
	listen_ = socket(AF_INET, SOCK_STREAM, 0);
	if (listen_<0){

		return -1;
	}
	auto ret = -1;
	const auto flags = fcntl(listen_, F_GETFL, 0);
	ret = fcntl(listen_, F_SETFL, flags | O_NONBLOCK);

	struct sockaddr_in sin{};
	
	sin.sin_family = AF_INET;
	sin.sin_port = htons(27015);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	ret = bind(listen_, reinterpret_cast<struct sockaddr*>(&sin), sizeof(sin));
	if (ret<0){
		return -1;
	}

	ret = listen(listen_, SOMAXCONN);
	if (ret < 0)
		return  -1;


	/*
	 * 成功
	 */
	return 0;
}

int SockAcceptor::accept(Session* session){
	
	sockaddr_in sin{};
	uint32_t len{};

	uintmax_t accept = ::accept(listen_, (struct sockaddr*)&sin, &len);
	if (accept<0){
		return -1;
	}
	session->setHandle(accept);
	

	return 0;
}
