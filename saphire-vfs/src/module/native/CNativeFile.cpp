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
	SPTR_core = core;
	Grab(SPTR_core);
	this->writable = writable;
	buffer = NULL;
	name = "CNativeFile";

	this->path.append(path.c_str());

	if(writable)
	{
		pFile = fopen(path.c_str(),"rb+");
	} else {
		pFile = fopen(path.c_str(), "rb");
	}

	if(pFile)
	{
		fseek(pFile, 0, SEEK_END); // seek to end of file
		size = ftell(pFile); // get current file pointer
		fseek(pFile, 0, SEEK_SET);
		buffer = core->getMemoryManager()->createMemoryBuffer(size);
		if(buffer)
		{
			void *  buff = buffer->getPointer(0);
			fread(buff, 1, buffer->getSize(), pFile);
			SPTR_core->Debug("NativeFIle","Open file: %s File size: %i ",path.c_str(),size);

		} else {
			Free(buffer);
			size=0;
			this->writable = false;
			SPTR_core->Debug("NativeFIle","Can`t create buffer");
		}
	} else {
		Free(buffer);

		this->writable = false;
		SPTR_core->Debug("NativeFIle","Cant open file `%s` ",path.c_str());
	}


}

CNativeFile::~CNativeFile() {
	 writable = false;
	 if(pFile) fclose(pFile); pFile = NULL;
	 Free(buffer);
	 Free(SPTR_core);

}

Saphire::Core::Types::size CNativeFile::getSize() { if(!buffer) return 0; return buffer->getSize(); }

/**
 * Reads a byte
 */
Saphire::Core::Types::u8 CNativeFile::get(Saphire::Core::Types::size pos){
	 if(!buffer) return 0;
	return  buffer->get(pos);
}

/**
 * Write a byte
 */
bool CNativeFile::put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char){
	if(!buffer) return false;
	return  buffer->put(pos,_char);
}

 const Saphire::Core::Types::String  CNativeFile::getName() {
	return path;
}

 const Saphire::Core::Types::String CNativeFile::getDebugName() {
 	return name;
 }

void * CNativeFile::getPointer(Saphire::Core::Types::size pos)
{
	if(!buffer) return NULL;
	return  buffer->getPointer(pos);
}

Saphire::Core::Types::String CNativeFile::getAsString()
{
	Saphire::Core::Types::String  data = "";
	if(buffer) data.append((const char *)buffer->getPointer(),buffer->getSize());
	return data;
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
