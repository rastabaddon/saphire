/*
 * CNativeFile.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CMemoryFile.h"

namespace Saphire {
namespace Core {
namespace Files {

CMemoryFile::CMemoryFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable) {
	SPTR_core = core;
	Grab(SPTR_core);
	this->writable = writable;
	buffer = NULL;

	this->path.append(path.c_str());

}

CMemoryFile::~CMemoryFile() {
	 writable = false;

	 Free(buffer);
	 Free(SPTR_core);

}

 const Saphire::Core::Types::String  CMemoryFile::getName() {
	return path;
}

 const Saphire::Core::Types::String CMemoryFile::getDebugName() {
 	return "CMemoryFile";
 }

void * CMemoryFile::getPointer(Saphire::Core::Types::size pos)
{
	return buffer->getPointer(pos);
}

Saphire::Core::Types::size CMemoryFile::getSize() { return buffer->getSize(); }

/**
 * Reads a byte
 */
Saphire::Core::Types::u8 CMemoryFile::get(Saphire::Core::Types::size pos){

	return  buffer->get(pos);
}

/**
 * Write a byte
 */
bool CMemoryFile::put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char){
	return  buffer->put(pos,_char);
}


} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
