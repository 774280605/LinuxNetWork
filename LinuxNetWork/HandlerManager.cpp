#include "HandlerManager.h"
#include "EventHandler.h"
HandlerManager::HandlerManager(){
}

HandlerManager::~HandlerManager(){
}

void HandlerManager::add(EventHandler* handler){
	this->handlers_[handler->getHandle()] = handler;


}

void HandlerManager::remove(EventHandler* handler){
	auto it = this->handlers_.find(handler->getHandle());
	if(it!=this->handlers_.end()){
		delete it->second;
	}
	this->handlers_.erase(it);

}
