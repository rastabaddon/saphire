/*
 * IModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef IMODULE_H_
#define IMODULE_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IModule : public Saphire::IBaseObject
		{
			public:
				IModule(){};
				virtual ~IModule(){};
				virtual Saphire::Core::Types::String getName()=0;
				virtual const Saphire::Core::Types::String getModuleDescription(){ return "No description"; };
				virtual bool init() { return false; };
				virtual bool loop() { return false; };
				virtual bool shutdown(){ return false; };

		};



		extern "C" {
			typedef Saphire::Module::IModule * SAPHIRE_MOD_Create(Saphire::Module::IModule * core);
		}

	}





}

#endif /* IMODULE_H_ */
