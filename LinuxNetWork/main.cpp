#include <cstdio>
#include "EventHandler.h"
#include "Acceptor.h"
#include "Reactor.h"
#include "MessageBlock.h"
#include <cstring>
#include <ostream>
#define MESSAGE "#AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA#"

int main()
{
	MessageBlock mb;
	for (auto i=0;i<3;++i){
		mb.add(MESSAGE, strlen(MESSAGE));
	}
	char buffer[1024]={0};
	for (auto i=0;i<3;++i){
		mb.remove(buffer, strlen(MESSAGE));

		printf(buffer);
		printf("\n");
		memset(buffer,0,1024);
	}

	/*Reactor* reactor = new Reactor;

	Acceptor* acceptor = new Acceptor(reactor);
	acceptor->open();


	while (true){
		reactor->handlerEvents();
	}*/

    return 0;
}
