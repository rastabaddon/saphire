/*
 * IArchive.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef IARCHIVE_H_
#define IARCHIVE_H_

namespace Saphire {
	namespace Core {

		namespace Files {


				class IArchive : public Saphire::Core::Files::IFile
				{
					public:

					virtual Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable=false)=0;
				};


		}
	}
}





#endif /* IARCHIVE_H_ */
