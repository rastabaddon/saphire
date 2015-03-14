/*
 * IFile.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef IFILE_H_
#define IFILE_H_

namespace Saphire {
	namespace Core {

		namespace Files {


				class IFile : public Saphire::IBaseObject
				{
					public:
					virtual Saphire::Core::Types::size getSize()=0;

				};


		}
	}
}




#endif /* IFILE_H_ */
