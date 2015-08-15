/*
 * CNativeArchive.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CMemoryArchive.h"

namespace Saphire {
namespace Core {
namespace Files {

CMemoryArchive::CMemoryArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core) {
	SPTR_core = core;
	Grab(SPTR_core);
	path = name;
	SPTR_core->Debug(getName(),"Archive open %s ",path.c_str());
	//Directory
	root = new CMemoryRecord(path,NULL,NULL);
	records.push_back(root);
}

CMemoryArchive::~CMemoryArchive() {
	Free(SPTR_core);
}

void * CMemoryArchive::getPointer(Saphire::Core::Types::size pos)
{
	return NULL;
}

const Saphire::Core::Types::String CMemoryArchive::getName() {
	return path;
}

const Saphire::Core::Types::String CMemoryArchive::getFileName() {
	return path;
}

Saphire::Core::Types::size CMemoryArchive::getSize()
{
	return 0;
}

Saphire::Core::Files::IFile * CMemoryArchive::openFile(Saphire::Core::Types::String path,bool writable)
{

	for (std::list<Saphire::Core::Files::CMemoryRecord  *>::iterator it=records.begin(); it != records.end(); ++it)
	{
		if ((*it)->getPath()==path&&(*it)->getFile()) return (*it)->getFile();
	}

	if(!writable) return NULL;


	//Check directory patch exists;
	CMemoryRecord * parent = root;

	Saphire::Core::Files::IFile * file = new CMemoryFile(SPTR_core,path,writable);
	CMemoryRecord * mr = new CMemoryRecord(path,parent,file);
	records.push_back(root);

	return mr->getFile();
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
