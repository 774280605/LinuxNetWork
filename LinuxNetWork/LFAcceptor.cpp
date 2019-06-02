#include "LFAcceptor.h"
#include "LFSession.h"
#include "Session.h"

LFAcceptor::LFAcceptor(EventHandler* handler, 
	Reactor* reactor, 
	LFThreadPool* lfThreadPool):
reactor_(reactor),
concreteHandler_(handler),
lfThreadPool_(lfThreadPool){
	reactor_->registerHandler(this, READ_EVENT);
}

LFAcceptor::~LFAcceptor(){
}

int LFAcceptor::handlerInput(int fd){
	lfThreadPool_->deactivate(fd, READ_EVENT);

	lfThreadPool_->promoteNewLeader();
	int acceptfd =  concreteHandler_->handlerInput(fd);
	EventHandler* wrapper = new Session(acceptfd);
	EventHandler* client = new LFSession(wrapper,lfThreadPool_,reactor_);
	lfThreadPool_->reactivate(fd, READ_EVENT);
	return 0;
}

int LFAcceptor::handlerOutput(int fd){
	return 0;
}

int LFAcceptor::handlerTimeout(int fd){
	return 0;

}

int LFAcceptor::handlerClose(int fd){
	return 0;
}

int LFAcceptor::getHandle(){
	return concreteHandler_->getHandle();
}
