/*
 * IMutex.h
 *
 *  Created on: 4 wrz 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_CORE_THREADS_IMUTEX_H_
#define INCLUDE_SAPHIRE_SAPHIRE_CORE_THREADS_IMUTEX_H_

namespace Saphire {
	namespace Threads {

	class IMutex
		{

			  public:

			  IMutex() {
				  bMutexLocked = false;
				#ifndef WINDOWS
				  	 cs = PTHREAD_MUTEX_INITIALIZER;
			   #else
				  	 //cs->x = 0;
				  	// cs->p = NULL;
				#endif

				     pthread_mutexattr_init(&csAttr);
				    //pthread_mutexattr_settype(&csAttr,PTHREAD_MUTEX_ERRORCHECK) ;
					//pthread_mutex_init(&cs,&csAttr);



					lastLockWhere = "";
					lastLockLine = 0;

					lastUnLockWhere = "";
					lastUnLockLine = 0;

					memset((void *)&threadLockID,0,sizeof(pthread_t));

					//printf("TWORZYSZ MUTEX  AA (%p) \n\r",&cs);

			  };

			  virtual ~IMutex() {

					//printf(" NISZCZYSZ MUTEX AA %p \n\r",&cs);
					pthread_mutex_lock(&cs);
					pthread_mutex_unlock(&cs);
					//printf(" NISZCZYSZ MUTEX BB %p \n\r",&cs);

				  pthread_mutex_destroy(&cs);
				  memset(&threadLockID,0,sizeof(pthread_t));

			  };

			  virtual bool isMyLock()
			  {

				  if(pthread_equal(threadLockID,pthread_self()) != 0)
				  {
					  return true;
				  } else {
					  return false;
				  }
			  }

			  virtual bool trylock(const char * where="",int line=0)  {


							  if(!isMyLock())
				  			  {

				  				  if( pthread_mutex_trylock(&cs )  !=0 )
				  				  {

									  return false;
				  				  } else {

									  threadLockID = pthread_self();

									  lastLockWhere = where;
									  lastLockLine = line;
									  bMutexLocked = true;

									  return true;

				  				  }

				  			  } else {
				  				  return false;
				  			  }
			  }

			  virtual bool lock(const char * where="",int line=0)  {



					  int waitTime = 0;

					  while(pthread_mutex_trylock(&cs ) !=0)
					  {

						  waitTime++;
						  if(waitTime>10000000) {
							  waitTime = 0;
							  printf("Lock timeout... !!!\n\r");
							  printf("Try lock from: %s:%i \n\r",where,line);
							  printf("Last lock in: %s:%i \n\r",lastLockWhere,lastLockLine);
							  #ifdef xWINDOWS
							 //	printf("Lock id:[%p][%p] \n\r",threadLockID.p,(void *)pthread_self().p);
							  #else
							  	  printf("Lock id:[%p][%p] \n\r",threadLockID,(void *)pthread_self());
							  #endif
							  fflush(stdout);
						  }

						   #ifdef xWINDOWS
						  	  	  Sleep(0);

							#else
						  	  	pthread_yield();
							#endif
					  }


					  threadLockID = pthread_self();
					  bMutexLocked = true;
					  lastLockWhere = where;
					  lastLockLine = line;


					  return true;

			  };



			  virtual bool unlock(const char * where="",int line=0)  {

					  memset(&threadLockID,0,sizeof(pthread_t));

					  lastUnLockWhere =  where;
					  lastUnLockLine = line;

					  bMutexLocked = false;
					  pthread_mutex_unlock( &cs);
					  return true;

			  };

			 bool isLock()
			  {
					 return bMutexLocked;
			  }

			  pthread_t  getThreadID()
			  {
				  return pthread_self();
			  }

			 virtual pthread_t getUsesThreadID()
			  {
				  return threadLockID;
			  }

			  private:

			    pthread_mutex_t cs;
			    pthread_mutexattr_t csAttr;
			    pthread_t threadLockID;

			    const char * lastLockWhere;
			    int lastLockLine;

			    const char *   lastUnLockWhere;
			    int lastUnLockLine;
			    mutable bool bMutexLocked;
		};

	}
}



#endif /* INCLUDE_SAPHIRE_SAPHIRE_CORE_THREADS_IMUTEX_H_ */
