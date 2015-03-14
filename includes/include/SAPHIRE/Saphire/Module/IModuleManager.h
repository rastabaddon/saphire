/*
 * IModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#ifndef IMODULEMANAGER_H_
#define IMODULEMANAGER_H_


namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class IModuleManager : public Saphire::Module::IModule
		{
			public:
				IModuleManager(){};
				virtual ~IModuleManager(){};
				virtual Saphire::Module::IModule * load (Saphire::Core::Types::String  name)=0;
				virtual Saphire::Module::IModule *  getModule (Saphire::Core::Types::String  name)=0;

		};

	}
}



#endif /* IMODULEMANAGER_H_ */

