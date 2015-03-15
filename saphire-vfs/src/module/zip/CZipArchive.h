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

namespace Saphire {
namespace Core {
namespace Files {

class CZipArchive : public Saphire::Core::Files::IArchive {
public:
	CZipArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core);
	virtual ~CZipArchive();

	const Saphire::Core::Types::String getName();

	Saphire::Core::Files::IFile * openFile(Saphire::Core::Types::String path,bool writable);
	Saphire::Core::Types::size getSize();

private:
	Saphire::Core::Types::String path;
	Saphire::Module::ICoreModule * SPTR_core;
	Saphire::Core::Files::IFile * zipFile;
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CZIPARCHIVE_H_ */
