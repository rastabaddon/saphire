/*
 * IBaseObject.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IBASEOBJECT_H_
#define IBASEOBJECT_H_



namespace Saphire {


		class IBaseObject
		{
			public:
				IBaseObject(){
					_ref_count=1;
				};

				virtual Saphire::Core::Types::String getObjectType() { return "IBaseObject"; };

				virtual ~IBaseObject(){
					_ref_count--;
					if(_ref_count>0) {
						printf("Memory leek %i \n",_ref_count);
					} else {
						//printf("Normal delete object\n");
					}
				};

				void grab(){  _ref_count++; }
				void drop(){  _ref_count--;
					if(_ref_count==0) {
						//printf("Force remove object %i \n",_ref_count);
						delete this;
					} else if(_ref_count<0) {
						printf("Memory leek %i \n",_ref_count);
					}
				}

				bool trylock(const char * where="",int line=0) { return _mutex.trylock(where,line); };
				bool lock(const char * where="",int line=0) { return _mutex.lock(where,line); };
				bool unlock(const char * where="",int line=0) { return _mutex.unlock(where,line); };
				bool islock() { return _mutex.isLock(); };


				Saphire::Core::Types::s32 getRefCount(){ return _ref_count; }

			private:
				 Saphire::Core::Types::s32 _ref_count;
				 Saphire::Threads::IMutex _mutex;
		};

}




#endif /* IBASEOBJECT_H_ */
