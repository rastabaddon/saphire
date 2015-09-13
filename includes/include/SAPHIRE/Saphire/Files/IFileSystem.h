/*
 * IFileSystem.h
 *
 *  Created on: 18 sty 2015
 *      Author: rast
 */

#ifndef IFILESYSTEM_H_
#define IFILESYSTEM_H_

namespace Saphire {
	namespace Core {

		namespace Files {


				class IFileSystem : public Saphire::IBaseObject
				{
					public:
						virtual const Saphire::Core::Types::String getDebugName()=0;
						virtual const Saphire::Core::Types::String getName()=0;

						virtual bool  isFileExists(const Saphire::Core::Types::String & name)=0;
						virtual bool  isDirExists(const Saphire::Core::Types::String & name)=0;

						virtual Saphire::Core::Files::IArchive * openArchive(const Saphire::Core::Types::String & path)=0;
						virtual const Saphire::Core::Types::String getFileSystemDescription(){ return "No description"; };
						//file
						virtual Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable)=0;
						virtual Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> scanDir(Saphire::Core::Types::String path)=0;
				};


		}
	}
}



#endif /* IFILESYSTEM_H_ */
