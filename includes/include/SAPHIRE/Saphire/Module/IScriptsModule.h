/*
 * IScriptsModule.h
 *
 *  Created on: 18 sie 2015
 *      Author: rast
 */

#ifndef ISCRIPTSMODULE_H_
#define ISCRIPTSMODULE_H_

namespace Saphire {



	//! Core thing`s namespace
	namespace Module {

		class IScriptsModule : public Saphire::Module::IModule
		{
			public:

			 virtual Saphire::Core::Scripts::IScriptEnv * executeScriptCode(Saphire::Core::Scripts::IScript & code)=0;
			 virtual Saphire::Core::Scripts::IScriptEnv * loadAndExecuteScriptCode(Saphire::Core::Types::String  path)=0;
		};


	}

}

#endif /* ISCRIPTSMODULE_H_ */
