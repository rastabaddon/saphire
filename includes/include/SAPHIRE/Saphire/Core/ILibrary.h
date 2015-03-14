/*
 * ILibrary.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef ILIBRARY_H_
#define ILIBRARY_H_

	namespace Saphire {
		namespace Core {
			class ILibrary  : public Saphire::IBaseObject {
				public:

				//	virtual ILibrary(Saphire::Core::Types::String format)=0;
					//void *dlopen(const char *filename, int flag);
					//virtual bool open(Saphire::Core::Types::String format)=0;

					//char *dlerror(void);
					//virtual char *dlerror(void)=0;

					//void *dlsym(void *handle, const char *symbol);
					virtual void * getEntrance(Saphire::Core::Types::String symbol)=0;

					//int dlclose(void *handle);
					//virtual bool close()=0;


			};


		}
	}

#endif /** ILIBRARY_H_ */
