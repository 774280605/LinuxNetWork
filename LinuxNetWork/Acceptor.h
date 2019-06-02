#pragma once
#include "EventHandler.h"

class Acceptor:public EventHandler
{
public:
	Acceptor();
	virtual ~Acceptor();


	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;

private:
	int listenSocket_;
};
