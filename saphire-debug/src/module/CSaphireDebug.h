/*
 * CSaphireDebug.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef CSAPHIREDEBUG_H_
#define CSAPHIREDEBUG_H_


#include "SAPHIRE/xSaphire.h"
#include "SAPHIRE/Saphire/Debug/Debug.h"

namespace Saphire {
namespace Module {

	class CSaphireDebug : public Saphire::Module::IDebugModule {
		public:
			CSaphireDebug(Saphire::Module::ICoreModule * core);
			virtual ~CSaphireDebug();

			const Saphire::Core::Types::String getDebugName();
			const Saphire::Core::Types::String getModuleName();

			void Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... );

		private:
			Saphire::Core::Types::String toStringColor(int attr,int fg,int bg=8);

	};


} /* namespace Manager */
} /* namespace Saphire */

#endif /* CSAPHIREDEBUG_H_ */
