#include "IPCStream.h"
#include <netinet/in.h>
#include <cerrno>

IPCStream::IPCStream(){
}

IPCStream::~IPCStream(){
}

int IPCStream::recv(void* buf, int len){
	int bytes;

	do{
		bytes= ::recv(this->getHandle(), static_cast<char*>(buf), len, 0);
	}
	while (bytes<0 && errno==EINTR);
	
	return bytes;

}

int IPCStream::send(void* buf, int len){
	int bytes=0;
	int transfer = 0;
	do{
		transfer = ::send(this->getHandle(), static_cast<char*>(buf), len, 0);
		bytes += transfer;
		char* p = static_cast<char*>(buf);
		p += bytes;
		buf = p;

	}
	while (transfer<0 && errno==EINTR && bytes!= len);

	return bytes;
}
