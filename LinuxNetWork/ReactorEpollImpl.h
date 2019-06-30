#pragma once
#include <sys/epoll.h>
#include "Global.h"
#include "ReactorImpl.h"
#include <map>
#define MAX_LEN 1024

class EventHandler;


class ReactorEpollImpl:
	public ReactorImpl{
public:
	ReactorEpollImpl();
	virtual ~ReactorEpollImpl();
	void registerHandler(int fd, EVENT_TYPE type) override;
	void registerHandler(EventHandler* handle, EVENT_TYPE type) override;
	void removeHandler(int fd, EVENT_TYPE type) override;
	void removeHandler(EventHandler* handle, EVENT_TYPE type) override;
	void handlerEvents() override;

	/*
	 * 重新激活事件
	 */
	void reactivate(int fd, EVENT_TYPE type) override;
	void reactivate(EventHandler* handler, EVENT_TYPE type) override;
	/*
	 * 注销事件
	 */
	void deactivate(int fd, EVENT_TYPE type) override;
	void deactivate(EventHandler* handler, EVENT_TYPE type) override;
private:
	int epollHandler_{0};


	struct epoll_event resultEvent_[MAX_LEN]{0};
	std::map<int, EventHandler*> handlers_;
};
