/*
 * CNativeFile.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CNATIVEFILE_H_
#define CNATIVEFILE_H_
#include "../include/inc.h"

namespace Saphire {
namespace Core {
namespace Files {

class CNativeFile : public Saphire::Core::Files::IFile {
public:
	CNativeFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable);
	virtual ~CNativeFile();

	Saphire::Core::Types::size getSize();
	/**
	 * Reads a byte
	 */
	Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos);

	/**
	 * Write a byte
	 */
	bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char);

	void * getPointer(Saphire::Core::Types::size pos=0);
	const Saphire::Core::Types::String  getName();
	const Saphire::Core::Types::String  getFileName();

private:
	Saphire::Module::ICoreModule * SPTR_core;
	FILE * pFile;
	bool writable;
	Saphire::Core::Types::IMemoryBuffer * buffer;
	Saphire::Core::Types::size size;
	Saphire::Core::Types::String path;
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CNATIVEFILE_H_ */
