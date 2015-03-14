/*
 * start.cpp
 *
 *  Created on: 23-03-2013
 *      Author: rast
 */

#include "BootClass.h"

namespace Saphire {
	namespace Boot {

	BootClass::BootClass() {
	// TODO Auto-generated constructor stub

}

	BootClass::~BootClass() {
	// TODO Auto-generated destructor stub
}

int BootClass::execute(std::string baseDir,std::string programName,std::string image,int argc, char *argv[])
{
	std::string program;
	std::string bits = "64";
	std::string ext = "";

	#ifdef _WIN32
		baseDir += "\\bin\\windows";
		ext = ".exe";
	#else
		baseDir += "bin/linux";
		ext = ".elf";
	#endif

	#ifdef ENVIRONMENT32
		bits = "32";
	#else
		bits = "64";
	#endif

	baseDir += "/";
	baseDir += bits;
	baseDir += "/";

	//printf("Get in to dir: %s\n\r",baseDir.c_str());

	chdir(baseDir.c_str());
    baseDir = getcwd (NULL,0);

	program = baseDir;


#ifndef _WIN32
	program += "/";
#else
	program += "\\";
#endif

	program += programName;
	program += bits;
	program += ext;

	#ifndef _WIN32
		setenv("LD_LIBRARY_PATH", baseDir.c_str(),0);
	#endif

	//printf("Base dir: %s\n\r",baseDir.c_str());
	//printf("Starting: %s\n\r",program.c_str());


	int ret = system(program.c_str());

	//printf("Return: %i\n\r",ret);

	return ret;
}

	}
}
