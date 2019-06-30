#pragma once
#include "EventHandler.h"
#include "Reactor.h"
#include "HandlerManager.h"
#include "SockAcceptor.h"
class Session;
class Acceptor:public EventHandler
{
public:
	Acceptor(Reactor*reactor);
	virtual ~Acceptor();


	int open();
	Session*makeService();
	int acceptFin(Session* service);

	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;


	int getEventMask() override;
	void enableEventMask(EVENT_TYPE type) override;

	void disableEventMask(EVENT_TYPE type) override;
private:
	

	Reactor*reactor_{};
	int event_{ 0 };
	HandlerManager handlerManager_;
	SockAcceptor acceptor_;
};
