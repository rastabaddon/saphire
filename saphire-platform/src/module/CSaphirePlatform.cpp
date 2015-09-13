/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphirePlatform.h"


namespace Saphire {
namespace Module {

		CSaphirePlatform::CSaphirePlatform(Saphire::Module::ICoreModule * core) {
			SPTR_core = core;

			signal = new Saphire::Core::CSignal(core);


			Saphire::Core::Types::String bits = "64";
			platformDirectory = "/";

			#ifdef _WIN32
			platformDirectory += "bin/windows";
			platformName = "windows";
			#else
			platformDirectory += "bin/linux";
			platformName = "linux";
			#endif

			//#ifndef _WIN32
					platformDirectory += "/";
			//#else
				//	platformDirectory += "\\";
			//#endif

			#ifdef ENVIRONMENT32
				platformDirectory += "32";
				platformName += "/32";
			#else
				platformDirectory += "64";
				platformName += "/64";
			#endif

				platformDirectory += "/";



		}

		CSaphirePlatform::~CSaphirePlatform() {
			Free(signal);
		}

		const Saphire::Core::Types::String  CSaphirePlatform::getPlatformName()
		{
			return platformName;
		}

		 Saphire::Core::ILibrary * CSaphirePlatform::openLibrary(Saphire::Core::Types::String name)
		 {
			 	 const char * error = NULL;
			 	 void * lib = dlopen(name.c_str(), RTLD_LAZY);
				 if (!lib) { SPTR_core->Debug(getDebugName(),"Error can`t open library %s (try  open %s )",name.c_str());
				  if ((error = dlerror())) { SPTR_core->Debug(getDebugName(),"Error %s ",error); }; return NULL; }
				 return (Saphire::Core::ILibrary *)lib;
		 }


		 const Saphire::Core::Types::String CSaphirePlatform::getPlatformDirectory()
		 {
			 	 return platformDirectory;
		 }

		const Saphire::Core::Types::String CSaphirePlatform::getDebugName()
		{
			return"saphire-platform";
		}

		const Saphire::Core::Types::String CSaphirePlatform::getModuleName()
		{
			return"saphire-platform";
		}
} /* namespace Manager */
} /* namespace Saphire */
