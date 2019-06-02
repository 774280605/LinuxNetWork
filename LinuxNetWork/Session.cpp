#include "Session.h"
#include <sys/socket.h>
#include <iostream>

Session::Session(int fd):fd_(fd){
}

Session::~Session(){

}

int Session::handlerInput(int fd){

	char buffer[1024] = {0};
	auto bytes = recv(fd, buffer, 1024, 0);
	std::cout << buffer << std::endl;
	return bytes;
}

int Session::handlerOutput(int fd){
	return 0;
}

int Session::handlerTimeout(int fd){
	return 0;
}

int Session::handlerClose(int fd){
	return 0;
}

int Session::getHandle(){
	return  this->fd_;
}
