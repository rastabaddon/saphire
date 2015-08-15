//============================================================================
// Name        : run.cpp
// Author      : Rafal <rast> Klimaszewski
// Version     :
// Copyright   : 2008-2012 (C) Rafal Klimaszewski
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "BootClass.h"


int main(int argc, char *argv[]) {

	Saphire::Boot::BootClass * s = new Saphire::Boot::BootClass();

	int ret = s->execute("./","saphire-core","",argc,argv);
	delete s;

	return ret;
}
