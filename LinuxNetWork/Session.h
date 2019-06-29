#pragma once
#include "EventHandler.h"
#include <cstdint>
#include "Reactor.h"
#include "HandlerManager.h"
class Session:
	public EventHandler{
public:
	Session(int fd,Reactor*reactor,HandlerManager*handlerManager);
	virtual ~Session();


	int handlerInput(int fd) override;
	int handlerOutput(int fd) override;
	int handlerTimeout(int fd) override;
	int handlerClose(int fd) override;
	int getHandle() override;


	int getEventMask() override;
	void enableEventMask(EVENT_TYPE type) override;

	void disableEventMask(EVENT_TYPE type) override;
	void setHandle(uintmax_t handle);
private:

	int fd_;
	EVENT_TYPE event_{0};
	Reactor*reactor_{nullptr};
	HandlerManager*handlerManager_{nullptr};
};
