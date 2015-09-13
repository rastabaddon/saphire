/*
 * CThreadsManager.cpp
 *
 *  Created on: 6 wrz 2015
 *      Author: rast
 */

#include "CThreadsManager.h"

namespace Saphire {
namespace Threads {

CThreadsManager::CThreadsManager( Saphire::Module::ICoreModule * core) {

	SPTR_core = core;
	CCpuThread * thread = NULL;

	SPTR_core->Debug(getDebugName(),"Init thread manager");

	SPTR_core->Debug(getDebugName(),"Init thread manager done");


	for(Saphire::Core::Types::u32 i=0; i<1; i++)
	{
		thread = new CCpuThread(this,false,i);
		threads.push_back(thread);
	}



}

CThreadsManager::~CThreadsManager() {
	SPTR_core->Debug(getDebugName(),"Shutdown thread manager");
	for( Saphire::Core::Types::List<CCpuThread *>::iterator iter=threads.begin(); iter != threads.end(); iter++ )
	{
			(*iter)->shutDown();
			Free((*iter));
	}

	threads.clear();
	SPTR_core->Debug(getDebugName(),"Shutdown thread manager done");
}

bool CThreadsManager::doMain()
{
	mainThread->EntryPoint();

	SPTR_core->Debug("CpuThread","Back from entry main point for shutdown...");

	return true;
}

bool CThreadsManager::addFuntionToThreadPool(Saphire::Core::Types::String name,Saphire::Core::Objects::ICallbackFunction * callback,Saphire::Core::Types::IAnyType param){
	thread_job job;
	job.callback = callback;
	job.param = param;
	job.name = name;

	threadPool.lock();
	Grab(callback);
	threadPool.push_front(job);
	threadPool.unlock();
}

template<class T>
bool CThreadsManager::addFuntionToThreadPool( Saphire::Core::Types::String name,T *object, int(T::*callback)(void * param),Saphire::Core::Types::IAnyType param){
	Saphire::Core::Objects::ICallbackFunction * mcalback = new Saphire::Core::Objects::ICallbackMethod<T>( object, T::callback);
	addFuntionToThreadPool(name,callback,param);
	Free(mcalback);
}

bool CThreadsManager::doNext()
{
	thread_job job;
	job.callback = NULL;

	threadPool.lock();
	if(threadPool.size()) {
		job = threadPool.back();
		threadPool.pop_back();
	}
	threadPool.unlock();

	if(job.callback) {
		job.callback->execute(job.param);
		Free(job.callback);
	}
	return true;
}

} /* namespace Threads */
} /* namespace Saphire */
