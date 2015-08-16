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
    bool debug=false;

	for (int i = 0; i < argc; ++i) {
		//printf("Starting: %s\n\r",argv[i]);
		if(strcmp(argv[i],"debug")==0) {
			debug = true;
		}
    };

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
    program = "";

    if(debug)
    {
    	program = "gdb  --nx -ex=r ";
    }

	program += baseDir;


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

	int ret = 0;
	struct stat info;

	if( stat( program.c_str(), &info ) != 0 || ( info.st_mode & S_IFDIR )) {
			ret = -1;
		  printf("Saphire Engine Exit With Error: Can`t found %s \n\r", program.c_str());
		  return ret;
	}






	ret = system(program.c_str());
	if(ret!=0)
	{
		printf("Saphire Engine Exit With Error ID: %i\n\r",ret);
	}

	return ret;
}

	}
}
