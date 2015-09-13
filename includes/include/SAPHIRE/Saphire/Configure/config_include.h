/*
 * config_include.h
 *
 *  Created on: 16-02-2013
 *      Author: rast
 */

#ifndef CONFIG_INCLUDE_H_
#define CONFIG_INCLUDE_H_

		/* get user config */
		#include "xEngineConfig.h"

		/* autoconfig */
		#include "xAutoConfig.h"

		#ifdef WINDOWS
				#define SAPHIRE_EXPORT __declspec(dllexport)
		#else
				#define SAPHIRE_EXPORT
		#endif

		#ifndef DEFAULT_INIT_SCRIPT
			#define DEFAULT_INIT_SCRIPT "xEngine/script/init.lua"
		#endif

#endif /* CONFIG_INCLUDE_H_ */
