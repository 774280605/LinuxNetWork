#pragma once
#include "Global.h"

class EventHandler;

class ReactorImpl
{
public:
	ReactorImpl();
	virtual ~ReactorImpl();

	virtual void registerHandler(int fd, EVENT_TYPE type)=0;
	virtual void registerHandler(EventHandler*handle, EVENT_TYPE type)=0;
	virtual void removeHandler(int fd, EVENT_TYPE type)=0;
	virtual void removeHandler(EventHandler*handle, EVENT_TYPE type)=0;

	virtual void handlerEvents()=0;
	virtual void reactivate(int fd, EVENT_TYPE type)=0;
	virtual void reactivate(EventHandler*handler, EVENT_TYPE type)=0;

	virtual void deactivate(int fd, EVENT_TYPE type)=0;
	virtual void deactivate(EventHandler*handler, EVENT_TYPE type)=0;
};
