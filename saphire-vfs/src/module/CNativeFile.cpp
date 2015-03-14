/*
 * CNativeFile.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CNativeFile.h"

namespace Saphire {
namespace Core {
namespace Files {

CNativeFile::CNativeFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable) {
	SPTR_core->grab();
	SPTR_core = core;
	this->writable = writable;

	if(writable)
	{
		pFile = fopen(path.c_str(),"r+");
	} else {
		pFile = fopen(path.c_str(), "r");
	}



	if(pFile)
	{
		fseek(pFile, 0, SEEK_END); // seek to end of file
		size = ftell(pFile); // get current file pointer
		fseek(pFile, 0, SEEK_SET);
		buffer = core->getMemoryManager()->createMemoryBuffer(size);
		if(buffer)
		{
			fread(buffer->getPointer(), buffer->getSize(), 1, pFile);

		} else {
			buffer = NULL;
			size=0;
			this->writable = false;
			SPTR_core->Debug("NativeFIle","Can`t create buffer");
		}
	} else {

		buffer->drop();
		buffer = NULL;
		this->writable = false;
		SPTR_core->Debug("NativeFIle","Cant open file ",path.c_str());
	}

}

CNativeFile::~CNativeFile() {

	this->writable = false;

	buffer->drop();
	buffer = NULL;
	if(pFile) fclose(pFile);
	pFile = NULL;
	SPTR_core->drop();
}

Saphire::Core::Types::size CNativeFile::getSize()
{
	return size;
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
