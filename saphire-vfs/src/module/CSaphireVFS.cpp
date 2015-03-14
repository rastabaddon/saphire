/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireVFS.h"


namespace Saphire {
namespace Module {

		CSaphireVFS::CSaphireVFS(Saphire::Module::ICoreModule * core) {
			SPTR_core = core;
			Grab(SPTR_core);
		}


		void CSaphireVFS::init(Saphire::Core::Types::String path)
		{

			NFS = new Saphire::Core::Files::CNativeFileSystem(SPTR_core);
			((Saphire::Core::Files::CNativeFileSystem *)NFS)->setNativeBaseDir(path);


			addArchive("/");


			Saphire::Core::Files::IFile * file = openFile("/text.txt",true);
			if(file)
			{


				Delete(file);
			}
		}

		CSaphireVFS::~CSaphireVFS() {
			Free(SPTR_core);
		}

		Saphire::Core::Files::IFile * CSaphireVFS::openFile(Saphire::Core::Types::String path,bool writable)
		{
			SPTR_core->Debug(getName(),"Try open file %s ",path.c_str());
			Saphire::Core::Files::IFile * file = NULL;
			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
				file = (*it)->openFile(path,writable);
				if(file) { break; }
			}

			if(!file) {
				SPTR_core->Debug(getName(),"Can`t open file %s ",path.c_str());
			}
			return file;
		}

		Saphire::Core::Files::IArchive * CSaphireVFS::addArchive(Saphire::Core::Types::String path)
		{
			Saphire::Core::Types::String vpath;
			Saphire::Core::Types::String npath;
			Saphire::Core::Types::String test = path.substr(0,1);

			SPTR_core->Debug(getName(),"Add %s ",path.c_str());

			Saphire::Core::Files::IArchive * archive = NULL;
			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
				archive = (*it)->openArchive(path);
				if(archive) { break; }
			}
			if(!archive) {
				SPTR_core->Debug(getName(),"Can`t open archive: %s ",path.c_str());
			return NULL; }


			return NULL;
		}

		bool CSaphireVFS::registerVFSManager(Saphire::Core::Types::String name,Saphire::Core::Files::IFileSystem * fileSystem)
		{

			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
				if((*it)->getName()==name) {
					SPTR_core->Debug(getName(),"Can`t register %s , name exists.",name.c_str());
					return false;
				}
			}

			SPTR_core->Debug(getName(),"registered new vfs ",name.c_str());
			fileSystems.push_front(fileSystem);

			return true;
		}

		Saphire::Module::IModule * CSaphireVFS::addVFSManager(Saphire::Core::Types::String name)
		{
			Saphire::Module::IModule * module = NULL;
			SPTR_core->Debug(getName(),"Can`t open %s ",name.c_str());

			return module;
		}

		Saphire::Core::Types::String CSaphireVFS::getName()
		{
			return Saphire::Core::Types::String("saphire-vfs");
		}

} /* namespace Manager */
} /* namespace Saphire */
