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

CZipFile::CZipFile(Saphire::Module::ICoreModule * core,Saphire::Core::Types::String path,bool writable,Saphire::Core::Files::CZipArchive * archive,Saphire::Core::Types::u16 compresion,void * copyFrom,Saphire::Core::Types::u32 size,Saphire::Core::Types::u32 sizeOut) {
	SPTR_core = core;
	Grab(SPTR_core);
	this->writable = writable;
	int ret  = Z_OK;
	name = "CZipFile";

	compressedBuffer = core->getMemoryManager()->createMemoryBuffer(size);
	buffer = core->getMemoryManager()->createMemoryBuffer(sizeOut);

	this->path.append(path.c_str());
	memcpy((void *)compressedBuffer->getPointer(),(void *)copyFrom,size);


	 ret  = Z_OK;

	switch(compresion)
	{
		case 0X8:

		//	SPTR_core->Debug(getName(),"Decompresion: Deflate Method   ",compresion);

			z_stream strm;
			strm.zalloc = Z_NULL;
			strm.zfree = Z_NULL;
			strm.opaque = Z_NULL;
			strm.avail_in = 0;
			strm.next_in = Z_NULL;
			ret = inflateInit2(&strm, -MAX_WBITS);

			strm.avail_in = compressedBuffer->getSize()-1; //iSourceLen;
			strm.next_in = (Bytef *)compressedBuffer->getPointer();
			strm.avail_out = buffer->getSize();
			strm.next_out = (Bytef *)buffer->getPointer();
			ret = inflate(&strm, Z_NO_FLUSH);
			(void)inflateEnd(&strm);

			//SPTR_core->Debug(getName(),"Found in archive [%s] (DEFLATE, %llu bytes,%llu bytes)",path.c_str(),compressedBuffer->getSize(),buffer->getSize());

		break;
		case 0:
		//	SPTR_core->Debug(getName(),"Decompresion: Method Storage ");
			memcpy((void *)buffer->getPointer(),(void *)compressedBuffer->getPointer(),compressedBuffer->getSize());
			//SPTR_core->Debug(getName(),"Found in archive [%s] (STORAGE, %llu bytes,%llu bytes)",path.c_str(),compressedBuffer->getSize(),buffer->getSize());
		break;

		//default:

			//SPTR_core->Debug(getName(),"Found in archive [%s] (Unknown Method %#2X, %llu bytes,%llu bytes)",compresion,path.c_str(),compressedBuffer->getSize(),buffer->getSize());
	}

	switch(ret)
	 {
		case Z_OK: { } break;
		case Z_MEM_ERROR: { SPTR_core->Debug(getName(),"not enough memory"); }  break;
		case Z_BUF_ERROR: { SPTR_core->Debug(getName(),"Buffer error"); }  break;
		case Z_STREAM_END: { SPTR_core->Debug(getName(),"Stream end error"); }  break;
		case Z_NEED_DICT : { SPTR_core->Debug(getName(),"Dictionary error"); }  break;
		case Z_ERRNO : { SPTR_core->Debug(getName(),"Err no error"); }  break;
		case Z_STREAM_ERROR: { SPTR_core->Debug(getName(),"Stream error"); }  break;
		case Z_DATA_ERROR : { SPTR_core->Debug(getName(),"Data error"); }  break;
		case Z_VERSION_ERROR : { SPTR_core->Debug(getName(),"Version error"); }  break;

		default: { SPTR_core->Debug(getName(),"Unknown error %i ",ret); }  break;
	 }

	status = ret;
	 Free(compressedBuffer);
}

CZipFile::~CZipFile() {
	 writable = false;
	 Free(buffer);
	 Free(SPTR_core);
}

Saphire::Core::Types::s8 CZipFile::getStatus()
{
	return status;
}

const Saphire::Core::Types::String CZipFile::getDebugName() {
	return "CZipFile";
}

const Saphire::Core::Types::String  CZipFile::getName() {
	return path;
}

void * CZipFile::getPointer(Saphire::Core::Types::size pos)
{
	if(buffer) return buffer->getPointer(pos);
	return NULL;
}

Saphire::Core::Types::size CZipFile::getSize() { if(buffer) return buffer->getSize();  return 0; }

/**
 * Reads a byte
 */
Saphire::Core::Types::u8 CZipFile::get(Saphire::Core::Types::size pos){
	if(buffer) return  buffer->get(pos);
	return 0;
}

/**
 * Write a byte
 */
bool CZipFile::put(Saphire::Core::Types::size pos,Saphire::Core::Types::u8 _char){
	if(buffer) return  buffer->put(pos,_char);
	return false;
}

Saphire::Core::Types::String CZipFile::getAsString()
{
	Saphire::Core::Types::String  data;
	data.append((const char *)buffer->getPointer(),buffer->getSize());
	return data;
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
