/*
 * CNativeFile.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CMEMORYFILE_H_
#define CMEMORYFILE_H_
#include "../include/inc.h"

namespace Saphire {
namespace Core {
namespace Files {

class CMemoryFile : public Saphire::Core::Files::IFile {
public:
	CMemoryFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable);
	virtual ~CMemoryFile();

	Saphire::Core::Types::size getSize();
	/**
	 * Reads a byte
	 */
	Saphire::Core::Types::u8 get(Saphire::Core::Types::size pos);

	/**
	 * Write a byte
	 */
	bool put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char);
private:
	Saphire::Module::ICoreModule * SPTR_core;
	FILE * pFile;
	bool writable;
	Saphire::Core::Types::IMemoryBuffer * buffer;
	Saphire::Core::Types::size size;
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CMEMORYFILE_H_ */
