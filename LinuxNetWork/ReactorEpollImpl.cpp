#include "ReactorEpollImpl.h"
#include <sys/epoll.h>
#include "EventHandler.h"
#include <iostream>
#include <errno.h>
ReactorEpollImpl::ReactorEpollImpl()
{
	epollHandler_ = epoll_create(1024);
}

ReactorEpollImpl::~ReactorEpollImpl(){
}

void ReactorEpollImpl::registerHandler(int fd, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	const auto result =  epoll_ctl(epollHandler_, EPOLL_CTL_ADD, 
		fd, &ev);
	if (result==0){
		
	}
		
}

void ReactorEpollImpl::registerHandler(EventHandler* handler, EVENT_TYPE type) {
	struct epoll_event ev { 0, 0 };

	int how = 0;

	int what = handler->getEventMask();
	if (what > 0)
		how = EPOLL_CTL_MOD;
	else
		how = EPOLL_CTL_ADD;
	

	what |= type;
	if (what&READ_EVENT)
		ev.events |= EPOLLIN;
	if (what& WRITE_EVENT)
		ev.events |= EPOLLOUT;
	
	ev.data.fd = handler->getHandle();
	const auto  result = epoll_ctl(epollHandler_, how,handler->getHandle(), &ev);
	if (result == 0) {
		handlers_[handler->getHandle()] = handler;
		handler->enableEventMask(static_cast<EVENT_TYPE>(what));
	}	
}

void ReactorEpollImpl::removeHandler(int fd, EVENT_TYPE type){
	struct epoll_event ev{0,0};


	ev.events = EPOLLIN;
	ev.data.fd = fd;
	const auto result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,fd, &ev);
	if (result == 0) {
	}
	
}

void ReactorEpollImpl::removeHandler(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	int what = handler->getEventMask();

	what &= (~type);
	auto how = 0;
	if(what>0){
		how = EPOLL_CTL_MOD;
		if(what&READ_EVENT)
			ev.events |= EPOLLIN;
		if (what&WRITE_EVENT)
			ev.events |= EPOLLOUT;
	}else{
		how = EPOLL_CTL_DEL;
		if (type&READ_EVENT)
			ev.events |= EPOLLIN;
		if (type&WRITE_EVENT)
			ev.events |= EPOLLOUT;
	}
	
	ev.data.fd = handler->getHandle();
	const  auto result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,handler->getHandle(), &ev);
	if (result == 0) {
		handler->disableEventMask(type);
		auto it = handlers_.find(handler->getHandle());
		if(it!= handlers_.end()){
			handlers_.erase(it);
		}
	}
}

void ReactorEpollImpl::handlerEvents(){
	

	auto num = 0;
	do{
		num = epoll_wait(epollHandler_, resultEvent_, MAX_LEN, -1);
		if (num > 0) {
			for (auto i = 0;i < num;++i) {
				int whats = resultEvent_[i].events;
				if (whats& EPOLLIN) {
					int tmpFd = resultEvent_[i].data.fd;
					auto it = handlers_.find(tmpFd);
					auto handler = it->second;
					handler->handlerInput(tmpFd);
				}
			}
		}
	}
	while ((num<0) && (errno == EINTR));
}

void ReactorEpollImpl::reactivate(int fd, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	auto it = handlers_.find(fd);
	if (it == handlers_.end())
		return;
	auto tmpHandler = it->second;

	int how = 0;
	int what = tmpHandler->getEventMask();
	if (what > 0) 
		how = EPOLL_CTL_MOD;
	else
		how = EPOLL_CTL_ADD;

	what |= type;
	if (what&READ_EVENT) 
		ev.events |= EPOLLIN;
	if (what&WRITE_EVENT)
		ev.events |= EPOLLOUT;
	ev.data.fd = fd;
	const auto result = epoll_ctl(epollHandler_, how,fd, &ev);
	if (result>=0)
		tmpHandler->enableEventMask(type);
	
}

void ReactorEpollImpl::reactivate(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	int how = 0;
	int what = handler->getEventMask();
	if (what>0)
		how = EPOLL_CTL_MOD;	
	else
		how = EPOLL_CTL_ADD;	

	what |= type;
	if(what&READ_EVENT)
		ev.events |= EPOLLIN;	
	if(what&WRITE_EVENT)
		ev.events |= EPOLLOUT;	
	
	ev.data.fd = handler->getHandle();
	const auto result = epoll_ctl(epollHandler_, how,handler->getHandle(), &ev);
	if (result>=0)
		handler->enableEventMask(type);
	
}

void ReactorEpollImpl::deactivate(int fd, EVENT_TYPE type){

	auto it = handlers_.find(fd);
	if (it == handlers_.end())
		return;
	auto tmpHandler = it->second;

	struct epoll_event ev{0,0};

	auto how = 0;
	auto what = tmpHandler->getEventMask();
	what &= (~type);
	if (what > 0) {
		how = EPOLL_CTL_MOD;
		if (what&READ_EVENT) 
			ev.events |= EPOLLIN;
		if (what&WRITE_EVENT)
			ev.events |= EPOLLOUT;
	}else {
		how = EPOLL_CTL_DEL;
		if (type&READ_EVENT) 
			ev.events |= EPOLLIN;
		if (type&WRITE_EVENT)
			ev.events |= EPOLLOUT;
	}

	ev.data.fd = fd;

	const auto result = epoll_ctl(epollHandler_, how,fd, &ev);
	if (result>=0)
		tmpHandler->disableEventMask(type);

}

void ReactorEpollImpl::deactivate(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	auto how = 0;
	auto what = handler->getEventMask();
	what &= (~type);
	if (what > 0){
		how = EPOLL_CTL_MOD;
		if(what&READ_EVENT)
			ev.events |= EPOLLIN;
			
		if (what&WRITE_EVENT)
			ev.events |= EPOLLOUT;
	}else{//<=0 说明没有事件标志
		how = EPOLL_CTL_DEL;
		if (type&READ_EVENT) 
			ev.events |= EPOLLIN;
		if (type&WRITE_EVENT)
			ev.events |= EPOLLOUT;
	}

	const auto result = epoll_ctl(epollHandler_, how,handler->getHandle(), &ev);
	if (result>=0)
		handler->disableEventMask(type);
	
}
