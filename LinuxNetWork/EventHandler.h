#pragma once
#include "Global.h"
class EventHandler
{
public:
	EventHandler();
	virtual ~EventHandler();

	virtual int handlerInput(int fd)=0;
	virtual int handlerOutput(int fd)=0;
	virtual int handlerTimeout(int fd)=0;
	virtual int handlerClose(int fd)=0;
	virtual int getHandle()=0;
	virtual int getEventMask() = 0;
	virtual void enableEventMask(EVENT_TYPE type) = 0;
	virtual void disableEventMask(EVENT_TYPE type) = 0;
};
