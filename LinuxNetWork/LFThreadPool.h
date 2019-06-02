#pragma once
#include <mutex>
#include "Reactor.h"
#include <thread>
#include <condition_variable>

class LFThreadPool
{
public:
	LFThreadPool(Reactor*reactor);
	virtual ~LFThreadPool();

	void join();
	void promoteNewLeader();
	void deactivate(int fd, EVENT_TYPE type);
	void reactivate(int fd, EVENT_TYPE type);

private:
	std::mutex mutex_;
	std::condition_variable conditionVariable_;
	std::thread::id leaderId_;

	std::thread::id noCurrentId_;
	Reactor*reactor_;
};
