/*
 * start.h
 *
 *  Created on: 23-03-2013
 *      Author: rast
 */

#ifndef START_H_
#define START_H_

#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <unistd.h>

#ifdef _WIN32
	#include <windows.h>
#endif

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

// Check GCC
#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

using namespace std;
namespace Saphire {
	namespace Boot {
		class BootClass {
		public:
			BootClass();
			virtual ~BootClass();

			int execute(std::string baseDir,std::string programName,std::string image,int argc, char *argv[]);

		};
	}
}
#endif /* START_H_ */
