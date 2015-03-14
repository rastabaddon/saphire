//============================================================================
// Name        : saphire-core.cpp
// Author      : Rafal KLimaszewski
// Version     :
// Copyright   : GPL
// Description : Hello World in C++, Ansi-style
//============================================================================

/*** PASY
PASS		[VIDEO] 		[PHYSICS] 		[SOUND] [NETWORK] [CONTROLERS] [AI]		[SCRIPT]
0															RECIVE		RECIVE						EVENTS
1																								  LOGIC	EVENTS
2																											RUNSTEP,EVENTS
3							RECALCULATE  															EVENTS
4			RENDER																						EVENTS
5			SWAP																							EVENTS
6												PLAY		 SEND		 FEDBACK					EVENTS
7			SYNC			SYNC				SYNC		 SYNC		 SYNC						EVENTS


*/
#include "core/CoreModule.h"
using namespace std;
Saphire::Core::CoreModule * core = NULL;

int main(int argc, char *argv[]) {
	    std::cout << "Start \n ";
	    core = new Saphire::Core::CoreModule();
		return core->run(argc,argv);

}


void* operator new (size_t size)
{
	if(core&&core->getMemoryManager()) return core->getMemoryManager()->allocate(size);
	return malloc(size);
 }

void* operator new[ ] (size_t size)
{
	if(core&&core->getMemoryManager()) return core->getMemoryManager()->allocate(size);
   return  malloc(size);
}

void operator delete (void* pointerToDelete)
{
	if(core&&core->getMemoryManager()) return core->getMemoryManager()->deallocate(pointerToDelete);
   free(pointerToDelete);
}

void operator delete[ ] (void* arrayToDelete)
{
	if(core&&core->getMemoryManager())  return core->getMemoryManager()->deallocate(arrayToDelete);
	free(arrayToDelete);
}
