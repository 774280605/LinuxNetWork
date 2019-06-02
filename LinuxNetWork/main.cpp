#include <cstdio>
#include "EventHandler.h"
#include "LFAcceptor.h"
#include "Acceptor.h"
#include "ThreadManager.h"
int main()
{
	Reactor*reactor = new Reactor();
	EventHandler*acceptor = new Acceptor();
	LFThreadPool*lfThreadPool = new LFThreadPool(reactor);
	EventHandler* lfAcceptor = new LFAcceptor(acceptor,reactor,lfThreadPool);

	ThreadManager manager(reactor, lfThreadPool);
	manager.startup();
	

    return 0;
}
