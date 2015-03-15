/*
 * CNativeFile.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CZIPFILE_H_
#define CZIPFILE_H_
#include "../include/inc.h"

namespace Saphire {
namespace Core {
namespace Files {

class CZipFile : public Saphire::Core::Files::IFile {
public:
	CZipFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable);
	virtual ~CZipFile();

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
	Saphire::Core::Files::IFile * file;
	bool writable;
	Saphire::Core::Types::IMemoryBuffer * buffer;
	Saphire::Core::Types::size size;

};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CZIPFILE_H_ */
