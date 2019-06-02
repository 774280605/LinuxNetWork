#include "LFThreadPool.h"

LFThreadPool::LFThreadPool(Reactor*reactor)
	:reactor_(reactor)
{
}

LFThreadPool::~LFThreadPool(){

}

void LFThreadPool::join(){
	std::unique_lock<std::mutex> lock(mutex_);
	for (;;){
		while (leaderId_!=noCurrentId_){
			conditionVariable_.wait(lock);
		}		
		leaderId_ = std::this_thread::get_id();
		lock.unlock();
		///promoteNewLeader();
		reactor_->handlerEvents();		
		lock.lock();
	}
}

void LFThreadPool::promoteNewLeader(){
	std::unique_lock<std::mutex> lock(mutex_);
	if (leaderId_!= std::this_thread::get_id()){
		return;
	}
	leaderId_ = noCurrentId_;
	conditionVariable_.notify_one();
}

void LFThreadPool::deactivate(int fd, EVENT_TYPE type){
	reactor_->removeHandler(fd, type);
}

void LFThreadPool::reactivate(int fd, EVENT_TYPE type){
	reactor_->registerHandler(fd, type);
}
