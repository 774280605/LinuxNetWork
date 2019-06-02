#pragma once
#include "EventHandler.h"
#include "LFThreadPool.h"

class LFSession:
	public EventHandler{
public:
	LFSession(EventHandler*handler,LFThreadPool*lfThreadPool,Reactor*reactor);
	virtual ~LFSession();


	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;

private:
	LFThreadPool*lfThreadPool_;
	Reactor*reactor_;
	EventHandler*concreteHandler_;
};
