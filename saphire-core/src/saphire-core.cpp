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
		int ret = 0;
		core = NULL;
	    core = new Saphire::Core::CoreModule();

		ret = core->run(argc,argv);


		return ret;
}


void* operator new (size_t size)
{
	if(core) {
		Saphire::Module::IMemoryModule * memoryModule = core->getMemoryManager();
		if(memoryModule) return memoryModule->allocate(size);
	}
	return malloc(size);
 }

void* operator new[ ] (size_t size)
{
	if(core) {
		Saphire::Module::IMemoryModule * memoryModule = core->getMemoryManager();
		if(memoryModule) return memoryModule->allocate(size);
	}
   return  malloc(size);
}

void operator delete (void* pointerToDelete)
{
	if(core) {
		Saphire::Module::IMemoryModule * memoryModule = core->getMemoryManager();
		if(memoryModule) return memoryModule->deallocate((Saphire::Core::Types::pointer)pointerToDelete);
	}
   free(pointerToDelete);
}

void operator delete[ ] (void* arrayToDelete)
{
	if(core) {
		Saphire::Module::IMemoryModule * memoryModule = core->getMemoryManager();
		if(memoryModule) return memoryModule->deallocate((Saphire::Core::Types::pointer)arrayToDelete);
	}
	free(arrayToDelete);
}
