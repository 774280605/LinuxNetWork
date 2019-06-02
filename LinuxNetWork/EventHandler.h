#pragma once

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
};
