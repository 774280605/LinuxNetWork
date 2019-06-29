#pragma once
#include <unordered_map>
class EventHandler;
class HandlerManager
{
public:
	HandlerManager();
	virtual ~HandlerManager();


	void add(EventHandler*handler);

	void remove(EventHandler*handler);


private:
	std::unordered_map<int, EventHandler*> handlers_;
};
