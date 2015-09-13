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
			NFS = 0;
			Grab(SPTR_core);
		}


		void CSaphireVFS::init(Saphire::Core::Types::String path)
		{

			NFS = new Saphire::Core::Files::CNativeFileSystem(SPTR_core);
			((Saphire::Core::Files::CNativeFileSystem *)NFS)->setNativeBaseDir(path);
			addArchive("/");
			addArchive("/xEngine");


			MEMORYFS = new Saphire::Core::Files::CMemoryFileSystem(SPTR_core);
			addArchive("/");

			ZIPFS = new Saphire::Core::Files::CZipFileSystem(SPTR_core);




			Saphire::Core::Files::IFile * file = openFile("/text.txt",true);


			Free(file);
		}

		CSaphireVFS::~CSaphireVFS() {
			Free(SPTR_core);
		}



			bool  CSaphireVFS::isFileExists(const Saphire::Core::Types::String & path)
			{
					 for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
					{


						if((*it)->isFileExists(path)) return true;
					}

					return false;

			}

			 bool  CSaphireVFS::isDirExists(const Saphire::Core::Types::String & path)
			{
				 for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
				{
					if((*it)->isDirExists(path)) return true;
				}
				 return false;
			}

		Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> CSaphireVFS::scanDir(Saphire::Core::Types::String path)
		{
			Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> files;
			Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry> tmp_files;

			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
					tmp_files = (*it)->scanDir(path);
					for (Saphire::Core::Types::List<Saphire::Core::Files::IDirEntry>::iterator itA=tmp_files.begin(); itA != tmp_files.end(); ++itA)
					{
							files.push_back((*itA));
					}
			}

			return files;
		}

		Saphire::Core::Files::IFile * CSaphireVFS::openFile(Saphire::Core::Types::String path,bool writable)
		{
			if(!isFileExists(path)) {
				SPTR_core->Debug(getDebugName(),"Can`t open file %s , file not exists",path.c_str());
				return NULL;
			}

			Saphire::Core::Files::IFile * file = NULL;

			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{

				file = (*it)->openFile(path,writable);
				if(file) { break; }
			}

			if(!file) {
				SPTR_core->Debug(getDebugName(),"Can`t open file %s ",path.c_str());
			}

			return file;
		}

		Saphire::Core::Files::IArchive * CSaphireVFS::addArchive(Saphire::Core::Types::String path)
		{

			Saphire::Core::Files::IArchive * archive = NULL;
			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
				archive = (*it)->openArchive(path);
				if(archive) { break; }
			}
			if(!archive) {
				SPTR_core->Debug(getDebugName(),"Can`t open archive: %s ",path.c_str());
			return NULL; }


			return NULL;
		}

		Saphire::Core::Files::IFileSystem *  CSaphireVFS::getVFSManager(Saphire::Core::Types::String name)
		{


			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
				if((*it)->getName()==name) {
					return (*it);
				}
			}

			return NULL;
		}

		bool CSaphireVFS::registerVFSManager(Saphire::Core::Types::String name,Saphire::Core::Files::IFileSystem * fileSystem)
		{
			if(!fileSystem) return false;

			for (std::list<Saphire::Core::Files::IFileSystem *>::iterator it=fileSystems.begin(); it != fileSystems.end(); ++it)
			{
				if((*it)->getName()==name) {
					SPTR_core->Debug(getDebugName(),"Can`t register %s , name exists.",name.c_str());
					return false;
				}
			}

			SPTR_core->Debug(getDebugName(),"registered new vfs `%s` : `%s` ",name.c_str(),fileSystem->getFileSystemDescription().c_str());
			Grab(fileSystem);
			fileSystems.push_front(fileSystem);

			return true;
		}

		Saphire::Module::IModule * CSaphireVFS::addVFSManager(Saphire::Core::Types::String name)
		{
			Saphire::Module::IModule * module = NULL;
			SPTR_core->Debug(getDebugName(),"UNSUPORTED addVFSManager. Can`t add %s ",name.c_str());

			return module;
		}

		const Saphire::Core::Types::String CSaphireVFS::getModuleName()
		{
			return "saphire-vfs";
		}

		const Saphire::Core::Types::String CSaphireVFS::getDebugName()
		{
			return "saphire-vfs";
		}
} /* namespace Manager */
} /* namespace Saphire */
