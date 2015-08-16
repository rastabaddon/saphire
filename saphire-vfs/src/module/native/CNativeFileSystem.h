/*
 * CNativeFileSystem.h
 *
 *  Created on: 14 lut 2015
 *      Author: rast
 */

#ifndef CNATIVEFILESYSTEM_H_
#define CNATIVEFILESYSTEM_H_
#include "../include/inc.h"
#include "CNativeArchive.h"

#include <dirent.h>

namespace Saphire {
namespace Core {
namespace Files {

	class CNativeFileSystem : public Saphire::Core::Files::IFileSystem {
	public:
		CNativeFileSystem(Saphire::Module::ICoreModule * core);
		virtual ~CNativeFileSystem();
		 const Saphire::Core::Types::String getFileSystemDescription(){
			 return "Native file system ";
		 };
		bool  setNativeBaseDir(Saphire::Core::Types::String path);
		const Saphire::Core::Types::String getName();
		const Saphire::Core::Types::String getDebugName();

		bool  isFileExists(const Saphire::Core::Types::String & name);
		bool  isDirExists(const Saphire::Core::Types::String & name);

		Saphire::Core::Files::IArchive * openArchive(const Saphire::Core::Types::String & path);

		Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable);

		 Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> scanDir(Saphire::Core::Types::String path);

	private:
		Saphire::Module::ICoreModule * SPTR_core;
		Saphire::Core::Types::String currentPath;

		//Archives
			Saphire::Core::Types::List<Saphire::Core::Files::IArchive  *> archives;
	};

}
} /* namespace Manager */
} /* namespace Saphire */

#endif /* CNATIVEFILESYSTEM_H_ */
