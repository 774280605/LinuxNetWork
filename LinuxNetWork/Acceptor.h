#pragma once
#include "EventHandler.h"
#include "Reactor.h"
#include "HandlerManager.h"
class Acceptor:public EventHandler
{
public:
	Acceptor(Reactor*reactor);
	virtual ~Acceptor();


	int open();
	int acceptFin(int fd);

	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;


	int getEventMask() override;
	void enableEventMask(EVENT_TYPE type) override;

	void disableEventMask(EVENT_TYPE type) override;
private:
	int listenSocket_{};

	Reactor*reactor_{};
	EVENT_TYPE event_{ 0 };
	HandlerManager handlerManager_;
};
