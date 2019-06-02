#pragma once
#include "EventHandler.h"
class Session:
	public EventHandler{
public:
	Session(int fd);
	virtual ~Session();


	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;


private:

	int fd_;
};
