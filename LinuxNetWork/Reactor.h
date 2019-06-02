#pragma once
#include "Global.h"

class EventHandler;
class ReactorImpl;
class Reactor
{
public:
	Reactor();
	virtual ~Reactor();

	virtual void registerHandler(int fd,EVENT_TYPE type );
	virtual void registerHandler(EventHandler*handle, EVENT_TYPE type);
	virtual void removeHandler(int fd, EVENT_TYPE type);
	virtual void removeHandler(EventHandler*handle, EVENT_TYPE type);

	virtual void handlerEvents();
	virtual void reactivate(int fd, EVENT_TYPE type);
	virtual void reactivate(EventHandler*handler, EVENT_TYPE type);

	virtual void deactivate(int fd, EVENT_TYPE type);
	virtual void deactivate(EventHandler*handler, EVENT_TYPE type);
private:
	
	ReactorImpl*impl_;
};
