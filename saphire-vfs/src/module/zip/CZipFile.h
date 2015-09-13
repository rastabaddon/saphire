/*
 * CNativeFile.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CZIPFILE_H_
#define CZIPFILE_H_
#include "../include/inc.h"
#include "../../thirdpart/zip/zlib.h"
#include "../../thirdpart/minizip/zip.h"
#include "../../thirdpart/minizip/unzip.h"
#include "../../thirdpart/minizip/ioapi.h"
#include "../../thirdpart/minizip/ioapi_mem.h"

namespace Saphire {
namespace Core {
namespace Files {

class CZipArchive;

class CZipFile : public Saphire::Core::Files::IFile {
public:
	CZipFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable=false,Saphire::Core::Files::CZipArchive * archive=NULL,Saphire::Core::Types::u16 compresion=0,void * copyFrom=NULL,Saphire::Core::Types::u32 size=0,Saphire::Core::Types::u32 sizeOut=0);
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
	void * getPointer(Saphire::Core::Types::size pos);

	const Saphire::Core::Types::String getName();
	const Saphire::Core::Types::String getDebugName();

	Saphire::Core::Types::s8 getStatus();
	Saphire::Core::Types::String getAsString();

private:


	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::Files::IFile * file;
	bool writable;
	Saphire::Core::Types::s8 status;
	Saphire::Core::Types::IMemoryBuffer * buffer;
	Saphire::Core::Types::IMemoryBuffer *  compressedBuffer;
	Saphire::Core::Types::size size;
	Saphire::Core::Types::String path;
	Saphire::Core::Types::String name;

};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CZIPFILE_H_ */
