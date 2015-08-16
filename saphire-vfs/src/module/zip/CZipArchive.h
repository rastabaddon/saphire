/*
 * CNativeArchive.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef CZIPARCHIVE_H_
#define CZIPARCHIVE_H_
#include "../include/inc.h"
#include "CZipFile.h"
#include "../../thirdpart/zip/zlib.h"
#include "../../thirdpart/minizip/zip.h"

namespace Saphire {
namespace Core {
namespace Files {

#pragma pack(push)
#pragma pack(1)
typedef struct {
	Saphire::Core::Types::u32  signature;
	Saphire::Core::Types::u16  version;
	Saphire::Core::Types::u16  generalPurposeBitFlag;
	Saphire::Core::Types::u16 compressionMethod;
	Saphire::Core::Types::u16 modTime;
	Saphire::Core::Types::u16 modDate;
	Saphire::Core::Types::u32 CRC;
	Saphire::Core::Types::u32 compressedSize;
	Saphire::Core::Types::u32 uncompressedSize;
	Saphire::Core::Types::u16 fileNameSize;
	Saphire::Core::Types::u16 ExtraFieldName;
	void * data;
}  SZIP_FILE_HEADER;
#pragma pack(pop)

#pragma pack(push)
#pragma pack(1)
typedef struct {
	Saphire::Core::Types::u32  signature;
	Saphire::Core::Types::u32 CRC;
	Saphire::Core::Types::u32 compressedSize;
	Saphire::Core::Types::u32 uncompressedSize;
	void * data;
}  SZIP_FILE_DATA;

#pragma pack(pop)


class CZipArchive : public Saphire::Core::Files::IArchive {
public:
	CZipArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core);
	virtual ~CZipArchive();

	const Saphire::Core::Types::String getName();
	const Saphire::Core::Types::String getDebugName();

	Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable);
	Saphire::Core::Types::size getSize();

	bool  isFileExists(const Saphire::Core::Types::String & name);
	bool  isDirExists(const Saphire::Core::Types::String & name);

	void * getPointer(Saphire::Core::Types::size pos=0);

private:
	Saphire::Core::Types::String path;
	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::Files::IFile * zipFile;
	Saphire::Core::Types::List<Saphire::Core::Files::CZipFile *> files;
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CZIPARCHIVE_H_ */
