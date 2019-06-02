#include "Reactor.h"
#include "ReactorEpollImpl.h"
Reactor::Reactor():impl_(nullptr){
	impl_ = new ReactorEpollImpl();
}

Reactor::~Reactor(){

	if (impl_)
		delete impl_;
}

void Reactor::registerHandler(int fd, EVENT_TYPE type){
	impl_->registerHandler(fd,type);
}

void Reactor::registerHandler(EventHandler* handle, EVENT_TYPE type){
	impl_->registerHandler(handle, type);
}

void Reactor::removeHandler(int fd, EVENT_TYPE type){
	impl_->removeHandler(fd, type);
}

void Reactor::removeHandler(EventHandler* handle, EVENT_TYPE type){
	impl_->registerHandler(handle, type);
}

void Reactor::handlerEvents(){
	impl_->handlerEvents();
}

void Reactor::reactivate(int fd, EVENT_TYPE type){
}

void Reactor::reactivate(EventHandler* handler, EVENT_TYPE type){
}

void Reactor::deactivate(int fd, EVENT_TYPE type){
}

void Reactor::deactivate(EventHandler* handler, EVENT_TYPE type){
}
