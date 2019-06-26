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

void ReactorEpollImpl::registerHandler(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	ev.data.u64 = 0;
	ev.events = EPOLLIN;
	ev.data.fd = handler->getHandle();
	const auto  result = epoll_ctl(epollHandler_, EPOLL_CTL_ADD,
		handler->getHandle(), &ev);
	if (result == 0) {
		handlers_[handler->getHandle()] = handler;
	}	
}

void ReactorEpollImpl::removeHandler(int fd, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	ev.events = EPOLLIN;
	ev.data.fd = fd;
	const auto result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		fd, &ev);
	if (result == 0) {
	}
	
}

void ReactorEpollImpl::removeHandler(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev{0,0};
	ev.events = EPOLLIN;
	ev.data.fd = handler->getHandle();
	const  auto result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		handler->getHandle(), &ev);
	if (result == 0) {

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
	struct epoll_event ev;
	ev.events = EPOLLIN;
	//ev.data.ptr = handler;
	const auto result = epoll_ctl(epollHandler_, EPOLL_CTL_ADD,
		fd, &ev);
	if (result<0){
		std::cout << "epoll_ctl" << std::endl;
	}
}

void ReactorEpollImpl::reactivate(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = handler;
	const auto result = epoll_ctl(epollHandler_, EPOLL_CTL_ADD,
		handler->getHandle(), &ev);
	if (result<0){
		std::cout << "epoll_ctl" << std::endl;
	}
}

void ReactorEpollImpl::deactivate(int fd, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;

	const auto result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		fd, &ev);
	if (result<0){
		std::cout << "epoll_ctl" << std::endl;

	}
}

void ReactorEpollImpl::deactivate(EventHandler* handler, EVENT_TYPE type){
	struct epoll_event ev;
	ev.events = EPOLLIN;

	const auto result = epoll_ctl(epollHandler_, EPOLL_CTL_DEL,
		handler->getHandle(), &ev);
	if (result<0){
		std::cout << "epoll_ctl" << std::endl;

	}
}
