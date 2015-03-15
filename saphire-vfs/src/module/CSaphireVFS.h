/*
 * ModuleManager.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREVFS_H_
#define CSAPHIREVFS_H_

#include "../include/inc.h"
#include "native/CNativeFileSystem.h"
#include "memory/CMemoryFileSystem.h"
#include "zip/CZipFileSystem.h"

namespace Saphire {
namespace Module {

class CSaphireVFS : public Saphire::Module::IVFSModule {
public:
	CSaphireVFS(Saphire::Module::ICoreModule * core);
	virtual ~CSaphireVFS();

	void init(Saphire::Core::Types::String path);

	Saphire::Core::Types::String getName();
	bool registerVFSManager(Saphire::Core::Types::String name,Saphire::Core::Files::IFileSystem * fileSystem);
	Saphire::Module::IModule * addVFSManager(Saphire::Core::Types::String name);
	Saphire::Core::Files::IFileSystem *  getVFSManager(Saphire::Core::Types::String name);


	Saphire::Core::Files::IArchive * addArchive(Saphire::Core::Types::String path);

	//File manipulate
	Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable=false);
	 bool  isFileExists(const Saphire::Core::Types::String & name);
	 bool  isDirExists(const Saphire::Core::Types::String & name);

private:
	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::Types::String nativePath;
	Saphire::Core::Types::String currentDir;
	Saphire::Core::Files::IFileSystem * NFS; //Native file system
	Saphire::Core::Files::IFileSystem * MEMORYFS; //Memory file system
	Saphire::Core::Files::IFileSystem * ZIPFS; //Native file system

	//File systems
	Saphire::Core::Types::List<Saphire::Core::Files::IFileSystem *> fileSystems;
};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREVFS_H_ */
