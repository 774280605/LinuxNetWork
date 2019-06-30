#pragma once
#include <cstdint>
#include "IPCSock.h"
class IPCStream:public IPCSock
{
public:
	IPCStream();
	virtual ~IPCStream();


	int recv(void*buf,int len);

	int send(void*buf,int len);

};
