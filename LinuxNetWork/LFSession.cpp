#include "LFSession.h"

LFSession::LFSession(EventHandler* handler,
	LFThreadPool* lfThreadPool,
	Reactor* reactor) :
	concreteHandler_(handler),
	reactor_(reactor),
	lfThreadPool_(lfThreadPool){
	reactor_->registerHandler(this, READ_EVENT);
}

LFSession::~LFSession(){

}

int LFSession::handlerInput(int fd){
	lfThreadPool_->deactivate(fd, READ_EVENT);
	lfThreadPool_->promoteNewLeader();
	concreteHandler_->handlerInput(fd);

	lfThreadPool_->reactivate(fd, READ_EVENT);

	return 0;
}

int LFSession::handlerOutput(int fd){
	return 0;
}

int LFSession::handlerTimeout(int fd){
	return 0;
}

int LFSession::handlerClose(int fd){
	return 0;
}

int LFSession::getHandle(){
	return concreteHandler_->getHandle();
}
