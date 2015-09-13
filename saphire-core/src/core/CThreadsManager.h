/*
 * CThreadsManager.h
 *
 *  Created on: 6 wrz 2015
 *      Author: rast
 */

#ifndef SRC_CORE_CTHREADSMANAGER_H_
#define SRC_CORE_CTHREADSMANAGER_H_

#include "SAPHIRE/xSaphire.h"
#include "CCpuThread.h"

namespace Saphire {
namespace Threads {

typedef struct  {
	Saphire::Core::Objects::ICallbackFunction * callback;
	Saphire::Core::Types::IAnyType param;
	Saphire::Core::Types::String name;
} thread_job;

class CThreadsManager : public Saphire::Module::IThreadsModule {
public:
	CThreadsManager(Saphire::Module::ICoreModule * core);
	virtual ~CThreadsManager();

	 const Saphire::Core::Types::String getModuleName(){ return "saphire-threads"; };
	 const Saphire::Core::Types::String getDebugName(){ return "TMNG"; };

	bool addFuntionToThreadPool(Saphire::Core::Types::String name,Saphire::Core::Objects::ICallbackFunction * callback,Saphire::Core::Types::IAnyType param);
	template<class T>
	bool addFuntionToThreadPool( Saphire::Core::Types::String name,T *object, int(T::*callback)(void * param),Saphire::Core::Types::IAnyType param);

	bool  doNext();
	Saphire::Module::ICoreModule * SPTR_core;
	bool doMain();

	private:

		CCpuThread * mainThread;
		Saphire::Core::Types::List<thread_job> threadPool;
		Saphire::Core::Types::List<CCpuThread *> threads;
};

} /* namespace Threads */

} /* namespace Saphire */

#endif /* SRC_CORE_CTHREADSMANAGER_H_ */
