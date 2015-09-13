/*
 * CCpuThread.cpp
 *
 *  Created on: 25-02-2013
 *      Author: rast
 */

#include "CCpuThread.h"
#include "CThreadsManager.h"

namespace Saphire {
namespace Threads {

CCpuThread::CCpuThread(CThreadsManager *  manager,bool first,Saphire::Core::Types::u32 id) {



	threadManager = manager;
	bSleep = false;
	bRunning = false;
	sleepTime = 1;
	maxSleepTime = 100;
	threadName = "#";
	threadName += id;
	idThread = id;

	bLoop = true;
	bFreeRun = true;

	if(first)
	{
		bRunning = false;
		thread = pthread_self();
		bLoop = true;


	} else {



		if(pthread_create ( &thread, NULL, CCpuThread::EntryPoint_bootStrap, this )==0)
		{

				while(!bRunning)
				{

						pthread_yield();

				}

			//	pCore->Debug("Thread","%s","Waiting DONE");

		} else {

			threadManager->SPTR_core->Error("Thread","%s","Can`t create thread");
		}



	}


}

CCpuThread::~CCpuThread() {
	if(bRunning)
	{
			bRunning = false;
			bLoop = false;

		  	  if(pthread_equal(thread,pthread_self()) != 0)
			  {
		  		  runningMutex.unlock(__FILE__,__LINE__);

				  return;
			  } else {
				  runningMutex.lock(__FILE__,__LINE__);
				  //pthread_join (thread, NULL);
				  runningMutex.unlock(__FILE__,__LINE__);
			  }


	}
}

bool	CCpuThread::isFree()
{
	return bFreeRun;
}

void*	CCpuThread::EntryPoint_bootStrap( void* pThis )
{

	  CCpuThread * pt = (CCpuThread*)pThis;
	  pt->EntryPoint ();
	  return 0;
}

void	CCpuThread::EntryPoint()
{

	lock(__FILE__,__LINE__);



	 /** @fixed if too many time execute clone **/
	if(bRunning) { unlock(__FILE__,__LINE__); return; }


	thread = pthread_self();
	bRunning = true;

	unlock(__FILE__,__LINE__);

	//Wait until not add to mng
	runningMutex.lock(__FILE__,__LINE__);

	char buffer [50];
	int s =0;
	#ifdef xWINDOWS
		s=sprintf (buffer, "#%p:%i",thread.p,thread.x );
	#else
		s=sprintf (buffer, "#%lu",thread);
	#endif
	threadName = "";
	threadName.append(buffer,s);




	idile();

	 runningMutex.unlock(__FILE__,__LINE__);


}

bool CCpuThread::wakeUp()
{

	if(!bSleep) return false;

	lock(__FILE__,__LINE__);
	sleepTime = 0;

	unlock(__FILE__,__LINE__);

	return true;
}

void CCpuThread::yeld(Saphire::Core::Types::s32 forceWait)
{

		pthread_yield ();

		if(forceWait==0||sleepTime>forceWait)
		{
			if(sleepTime<1) { sleepTime = 0; if(bSleep){ bSleep = false;
			threadManager->SPTR_core->Debug("Thread","%s Wake up now! %i ms",threadName.c_str(),0);
			}
			 return; }
			if(sleepTime>50) { sleepTime=maxSleepTime; }
			forceWait = sleepTime;
		}


		if(!bSleep && forceWait>80){ bSleep = true;
		threadManager->SPTR_core->Debug("Thread","%s Go sleep %i ms",threadName.c_str(),forceWait);
		}
		if(bSleep && forceWait<50){ bSleep = false;
		threadManager->SPTR_core->Debug("Thread","%s Wake up leater %i ms",threadName.c_str(),forceWait);
		}

		if(forceWait>0)
		{
			goSleep(forceWait);
		}

		//pthread_testcancel();

		return;
}

bool CCpuThread::goSleep(Saphire::Core::Types::u32 time)
{
#ifdef LINUX
				timespec	 tsleep1;
				tsleep1.tv_sec = 0;
				tsleep1.tv_nsec = time *NANO_SECOND_MULTIPLIER;
				nanosleep(&tsleep1 ,NULL);
			#endif
			#ifdef WINDOWS
				Sleep(time / NANO_SECOND_MULTIPLIER);
			#endif
}
//#define DBG

void CCpuThread::dosomthing()
{


	threadManager->doNext();
	yeld();
}

void CCpuThread::idile()
{



		if(bRunning && !bLoop)
		{
			dosomthing();

		} else {

			while(bRunning && bLoop)
			{
				dosomthing();
			}

		}


		bRunning = false;
		bLoop = false;


}



ICpuThread * CCpuThread::getSelf()
{



		return NULL;
}

u32 CCpuThread::getID()
{
	return idThread;
}






bool CCpuThread::shutDown()
{

	bLoop = false;

	while(bRunning)
	{
		goSleep(1);
	}

	goSleep(1);
	//threadManager->SPTR_core->Debug("CpuThread","Wait for shutdown...");

	return true;

}

pthread_t CCpuThread::pthread_owner()
{
	return thread;
}

pthread_t	 CCpuThread::getThreadID()
{

		return   pthread_self();

}

} /* namespace Thread */
} /* namespace xEngine */
