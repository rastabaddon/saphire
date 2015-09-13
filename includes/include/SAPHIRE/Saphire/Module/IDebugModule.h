/*
 * ICoreModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IDEBUGMODUL_H_
#define IDEBUGMODUL_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IDebugModule : public Saphire::Module::IModule
		{
			public:
				virtual void Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )=0;
				virtual void Error(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )=0;
		};



	}
}



#endif /* IDEBUGMODUL_H_ */

