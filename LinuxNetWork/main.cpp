#include <cstdio>
#include "EventHandler.h"
#include "Acceptor.h"
#include "Reactor.h"

int main()
{
	Reactor* reactor = new Reactor;

	Acceptor* acceptor = new Acceptor(reactor);
	acceptor->open();


	while (true){
		reactor->handlerEvents();
	}

    return 0;
}
