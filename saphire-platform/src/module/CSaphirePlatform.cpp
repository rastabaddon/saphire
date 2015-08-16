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
			platformDirectory += "\\bin\\windows";
			#else
			platformDirectory += "bin/linux";
			#endif

			#ifndef _WIN32
					platformDirectory += "/";
			#else
					platformDirectory += "\\";
			#endif

			#ifdef ENVIRONMENT32
				platformDirectory += "32";
			#else
				platformDirectory += "64";
			#endif


		 #ifndef _WIN32
				platformDirectory += "/";
		 #else
				platformDirectory += "\\";
		 #endif


		}

		CSaphirePlatform::~CSaphirePlatform() {
			Free(signal);
		}

		 Saphire::Core::ILibrary * CSaphirePlatform::openLibrary(Saphire::Core::Types::String name)
		 {
			 	 return NULL;
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
