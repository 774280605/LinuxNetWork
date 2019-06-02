#include "ThreadManager.h"

void work(ThreadManager*threadManager){
	threadManager->work();
}

ThreadManager::ThreadManager(Reactor*reactor,LFThreadPool*lfThreadPool)
	:reactor_(reactor),lfThreadPool_(lfThreadPool)
{
}

ThreadManager::~ThreadManager(){
}

void ThreadManager::startup(){

	for (auto i=0;i<4;i++){
		threads_.emplace_back(::work, this);
	}

	lfThreadPool_->join();
}

void ThreadManager::work(){
	lfThreadPool_->join();
}

LFThreadPool* ThreadManager::getThreadPool(){
	return lfThreadPool_;
}
