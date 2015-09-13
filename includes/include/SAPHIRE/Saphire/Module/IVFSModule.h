/*
 * IModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IVFSMODULE_H_
#define IVFSMODULE_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IVFSModule : public Saphire::Module::IModule
		{
			public:
				virtual void init(Saphire::Core::Types::String path)=0;
				virtual Saphire::Module::IModule * addVFSManager(Saphire::Core::Types::String name)=0;
				virtual bool registerVFSManager(Saphire::Core::Types::String name,Saphire::Core::Files::IFileSystem * fileSystem)=0;
				virtual Saphire::Core::Files::IArchive * addArchive(Saphire::Core::Types::String path)=0;
				virtual Saphire::Core::Files::IFileSystem *  getVFSManager(Saphire::Core::Types::String name)=0;

				//FIle
				virtual Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable=false)=0;
				virtual bool  isFileExists(const Saphire::Core::Types::String & name)=0;
				virtual bool  isDirExists(const Saphire::Core::Types::String & name)=0;
				virtual Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> scanDir(Saphire::Core::Types::String path)=0;
		};


	}
}
#endif /* IVFSMODULE_H_ */
