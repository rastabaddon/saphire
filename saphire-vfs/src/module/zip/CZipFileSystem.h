/*
 * CNativeFileSystem.h
 *
 *  Created on: 14 lut 2015
 *      Author: rast
 */

#ifndef CZIPFILESYSTEM_H_
#define CZIPFILESYSTEM_H_
#include "../include/inc.h"
#include "CZipArchive.h"

namespace Saphire {
namespace Core {
namespace Files {

	class CZipFileSystem : public Saphire::Core::Files::IFileSystem {
	public:
		CZipFileSystem(Saphire::Module::ICoreModule * core);
		virtual ~CZipFileSystem();

		 const Saphire::Core::Types::String getFileSystemDescription(){
			 return "Compressed zif file VFS ";
		 };

		bool  setNativeBaseDir(Saphire::Core::Types::String path);
		const Saphire::Core::Types::String getName();
		bool  isFileExists(const Saphire::Core::Types::String & name);
		bool  isDirExists(const Saphire::Core::Types::String & name);

		Saphire::Core::Files::IArchive * openArchive(const Saphire::Core::Types::String & path);

		Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable);

	private:
		Saphire::Module::ICoreModule * SPTR_core;
		Saphire::Core::Types::String currentPath;

		//Archives
			Saphire::Core::Types::List<Saphire::Core::Files::IArchive  *> archives;
	};

}
} /* namespace Manager */
} /* namespace Saphire */

#endif /* CZIPFILESYSTEM_H_ */
