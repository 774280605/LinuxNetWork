#pragma once
#include <cstdint>
#include "IPCSock.h"
class Reactor;
class Session;
class SockAcceptor:public IPCSock
{
public:
	SockAcceptor();
	virtual ~SockAcceptor();


	int open(Reactor* reactor);

	int accept(Session*session);
};
