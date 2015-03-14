/*
 * IMutex.h
 *
 *  Created on: 19-02-2013
 *      Author: rast
 */

#ifndef IMUTEX_H_
#define IMUTEX_H_

//! Main namespace
namespace Saphire {

	//! Core thing`s namespace
	namespace Core {

		namespace Thread {

		typedef Saphire::Core::Types::u64 THREAD_ID;

	class IMutex
	{

		  public:
			virtual bool isMyLock()=0;
			virtual bool trylock() =0;
			virtual void lock(const char * where="",int line=0) =0;
			virtual void unlock(const char * where="",int line=0) =0;
			virtual bool isLock() =0;
			virtual THREAD_ID  getThreadID() =0;
			virtual THREAD_ID getUsesThreadID() =0;


	};



		}
	}
}



#endif /* IMUTEX_H_ */
