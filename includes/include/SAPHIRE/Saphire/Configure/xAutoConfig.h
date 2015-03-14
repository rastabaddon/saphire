/*
 * xAutoConfig.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef XAUTOCONFIG_H_
#define XAUTOCONFIG_H_

#include "xnamespaces.h"

#include  "standard_include.h"

#ifndef NULL
	#define NULL 0
#endif



//** SETUP SYSTEM **/
#ifdef _WIN32
	#define WINDOWS
	// Check windows
	#if _WIN32 || _WIN64
	#if _WIN64
	#define ENVIRONMENT64
	#else
	#define ENVIRONMENT32
	#endif
	#endif
#else
	#define LINUX
	// Check GCC
	#if __GNUC__
	#if __x86_64__ || __ppc64__
	#define ENVIRONMENT64
	#else
	#define ENVIRONMENT32
	#endif
	#endif
#endif

#ifndef ___CORE___
	#define SAPHIRE_XLIB
#else
	#define SAPHIRE_XLIB extern "C"
#endif


#endif /* XAUTOCONFIG_H_ */
