/*
 * CCpuThread.h
 *
 *  Created on: 25-02-2013
 *      Author: rast
 */

#ifndef CCPUTHREAD_H_
#define CCPUTHREAD_H_

#include "SAPHIRE/xSaphire.h"

#ifdef LINUX
	#define NANO_SECOND_MULTIPLIER  1000
#endif

#ifdef WINDOWS
	#define NANO_SECOND_MULTIPLIER  100
#endif

namespace Saphire {
namespace Threads {
class CThreadsManager;


typedef struct {
			Saphire::Threads::	ICpuThread * self;
} threadSpecific_data_t;

class CCpuThread : public Saphire::Threads::ICpuThread {
public:
	CCpuThread(CThreadsManager *  manager,bool first=false,Saphire::Core::Types::u32 id=0);
	virtual ~CCpuThread();



	void	EntryPoint();
	static void*	EntryPoint_bootStrap( void* pThis );

	static Saphire::Threads::ICpuThread * getSelf();
	static pthread_t  getThreadID();

	u32 getID();
	static u32 getStaticID();


	void dosomthing(); //Iddile loop
	void idile(); //Iddile loop
	void yeld(Saphire::Core::Types::s32 forceWait=0);
	bool isFree();
	bool wakeUp();


	pthread_t pthread_owner();

	bool shutDown();
	bool goSleep(Saphire::Core::Types::u32 time);

private:

	Saphire::Threads::threadSpecific_data_t 	threadData;

	 #ifdef xLINUX
	 timespec tsleep1,tsleep2;
	 #endif
	 mutable pthread_t thread;
	 mutable  bool bRunning;
	 mutable  bool bLoop;
	 mutable bool bFreeRun;
	 Saphire::Core::Types::String threadName;
	 Saphire::Threads::IMutex runningMutex;
	 s32 sleepTime;
	 s32 maxSleepTime;
	 bool bSleep;
	 u32 idThread;

	 CThreadsManager *  threadManager;
};

} /* namespace Threads */

} /* namespace xEngine */
#endif /* CCPUTHREAD_H_ */
