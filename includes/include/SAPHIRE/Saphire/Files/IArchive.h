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
						virtual const Saphire::Core::Types::String getName()=0;
						virtual Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable=false)=0;

						virtual Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos){ return 0; };
						virtual bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char){ return false; };

						virtual bool  isFileExists(const Saphire::Core::Types::String & name) { return false; }
						virtual bool  isDirExists(const Saphire::Core::Types::String & name) { return false; }
				};


		}
	}
}





#endif /* IARCHIVE_H_ */
