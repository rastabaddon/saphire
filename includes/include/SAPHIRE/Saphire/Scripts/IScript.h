/*
 * IScript.h
 *
 *  Created on: 22 sie 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_SCRIPTS_ISCRIPT_H_
#define INCLUDE_SAPHIRE_SAPHIRE_SCRIPTS_ISCRIPT_H_

namespace Saphire {

	namespace Core {

		namespace Scripts {

			class IScript : public Saphire::IBaseObject {

				public:
					Saphire::Core::Types::String code;
					Saphire::Core::Types::String path;
					Saphire::Core::Types::String file;
			};

		}
	}
}




#endif /* INCLUDE_SAPHIRE_SAPHIRE_SCRIPTS_ISCRIPT_H_ */
