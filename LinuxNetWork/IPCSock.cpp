#include "IPCSock.h"
#include <sys/ioctl.h>
#include <sys/socket.h>

uintmax_t IPCSock::getHandle(){
	return this->fd_;
}

void IPCSock::setHandle(uintmax_t fd){
	this->fd_ = fd;
}

int IPCSock::enableNoBlocking(bool mode){
	unsigned long block;
	if(mode)
		block = 1;	
	else
		block = 0;	
	return ioctl(static_cast<int>(this->getHandle()), FIONBIO, &block);
}

int IPCSock::setReuseAddrOpt(){
	uint reuseaddr = 1;
	return  setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(uint));
}
