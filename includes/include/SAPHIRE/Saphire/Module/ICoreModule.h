/*
 * ICoreModule.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */



#ifndef ICOREMODUL_H_
#define ICOREMODUL_H_

namespace Saphire {

	//! Core thing`s namespace
	namespace Module {

		class ICoreModule : public Saphire::Module::IModule
		{
			public:
				virtual void Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )=0;
				virtual void Error(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )=0;

				virtual Saphire::Module::IVFSModule * getVFS()=0;
				virtual Saphire::Module::IPlatformModule * getPlatform()=0;
				virtual Saphire::Module::IMemoryModule * getMemoryManager()=0;
				virtual Saphire::Module::IScriptsModule  * getScriptManager()=0;
				virtual Saphire::Module::IModuleManager  * getModuleManager()=0;

		};


	}
}



#endif /* ICOREMODUL_H_ */

