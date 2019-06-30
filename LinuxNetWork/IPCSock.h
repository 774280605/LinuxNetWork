#pragma once
#include <cstdint>

class IPCSock
{
public:
	IPCSock()=default;
	virtual ~IPCSock()=default;

	uintmax_t getHandle();
	void setHandle(uintmax_t fd);

	int enableNoBlocking(bool mode);

	int setReuseAddrOpt();

private:
	uintmax_t fd_;
};
