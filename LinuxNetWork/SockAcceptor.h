#pragma once
#include <cstdint>
class Reactor;
class Session;
class SockAcceptor
{
public:
	SockAcceptor();
	virtual ~SockAcceptor();


	int open(Reactor* reactor);

	int accept(Session*session);


private:
	uintmax_t listen_{};
};
