#include "ReactorEpollImpl.h"
#include <sys/epoll.h>
#include "EventHandler.h"
#include <iostream>
#include <errno.h>
ReactorEpollImpl::ReactorEpollImpl():
	epollHandler_(-1)
{
	epollHandler_ = epoll_create(1024);
}

ReactorEpollImpl::~ReactorEpollImpl(){
}

void ReactorEpollImpl::registerHandler(int fd, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	int result =  epoll_ctl(epollHandler_, EPOLL_CTL_ADD, 
		fd, &ev);
	if (result==0){
		
	}
		
}

void ReactorEpollImpl::registerHandler(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev;
	ev.data.u64 = 0;
	ev.events = EPOLLIN;
	ev.data.fd = handler->getHandle();
	int result = epoll_ctl(epollHandler_, EPOLL_CTL_ADD,
		handler->getHandle(), &ev);
	if (result == 0) {
		handlers_[handler->getHandle()] = handler;
	}	
}

void ReactorEpollImpl::removeHandler(int fd, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	int result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		fd, &ev);
	if (result == 0) {
	}
	
}

void ReactorEpollImpl::removeHandler(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = handler->getHandle();
	int result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		handler->getHandle(), &ev);
	if (result == 0) {
		///handlers_[handler->getHandle()] = handler;
	}
}

void ReactorEpollImpl::handlerEvents(){

ROLLBACK:
	int fds = epoll_wait(epollHandler_, resultEvent_, MAX_LEN, -1);
	if (fds>0){
		for (auto i=0;i< fds;++i){
			int whats = resultEvent_[i].events;
			if (whats& EPOLLIN){
				//EventHandler*handler = static_cast<EventHandler*>(resultEvent_[i].data.ptr);
				int tmpFd = resultEvent_[i].data.fd;
				auto it= handlers_.find(tmpFd);
				auto handler = it->second;
				handler->handlerInput(tmpFd);
			}
		}
	}
	else if(fds==-1){
		std::cout << "epoll_wait error:" << errno;
		if (errno== EINTR) 
			goto ROLLBACK;
	}


}

void ReactorEpollImpl::reactivate(int fd, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	//ev.data.ptr = handler;
	int result = epoll_ctl(epollHandler_, EPOLL_CTL_ADD,
		fd, &ev);
}

void ReactorEpollImpl::reactivate(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = handler;
	int result = epoll_ctl(epollHandler_, EPOLL_CTL_ADD,
		handler->getHandle(), &ev);
}

void ReactorEpollImpl::deactivate(int fd, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;

	int result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		fd, &ev);
}

void ReactorEpollImpl::deactivate(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;

	int result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		handler->getHandle(), &ev);
}
