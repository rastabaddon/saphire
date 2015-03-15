/*
 * CNativeFile.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CZipFile.h"

namespace Saphire {
namespace Core {
namespace Files {

CZipFile::CZipFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable) {
	SPTR_core = core;
	Grab(SPTR_core);
	this->writable = writable;
	buffer = NULL;


}

CZipFile::~CZipFile() {
	 writable = false;
	 Free(buffer);
	 Free(SPTR_core);
}

Saphire::Core::Types::size CZipFile::getSize() { return buffer->getSize(); }

/**
 * Reads a byte
 */
Saphire::Core::Types::u8 CZipFile::get(Saphire::Core::Types::size pos){
	return  0;
}

/**
 * Write a byte
 */
bool CZipFile::put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char){
	return  false;
}


} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
