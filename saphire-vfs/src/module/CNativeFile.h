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
	CNativeFile(Saphire::Core::Types::String path,bool writable);
	virtual ~CNativeFile();
};

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */

#endif /* CNATIVEFILE_H_ */
