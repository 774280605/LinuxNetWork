#pragma once
#include "EventHandler.h"
#include "Reactor.h"
#include "LFThreadPool.h"

class LFAcceptor:
	public EventHandler{
public:
	LFAcceptor(EventHandler*handler,Reactor*reactor,LFThreadPool* lfThreadPool);
	virtual ~LFAcceptor();


	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;

private:
	Reactor*reactor_;
	LFThreadPool*lfThreadPool_;

	EventHandler*concreteHandler_;
};
