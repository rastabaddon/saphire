/*
 * ModuleManager.cpp
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */


#include "CSaphireDebug.h"


namespace Saphire {
namespace Module {

		CSaphireDebug::CSaphireDebug(Saphire::Module::ICoreModule  * core)
		{

		}

		CSaphireDebug::~CSaphireDebug()
		{

		}

		const Saphire::Core::Types::String CSaphireDebug::getDebugName()
		{
			return "saphire-debug";
		}


		const Saphire::Core::Types::String CSaphireDebug::getModuleName()
		{
			return "saphire-debug";
		}

		Saphire::Core::Types::String CSaphireDebug::toStringColor(int attr,int fg,int bg)
		{
			char buffer[256];
		//	if(bg<8) {
				snprintf (buffer,255,"%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
			//} else {
			//	snprintf (buffer,255,"%c[%d;%d", 0x1B, attr, fg + 30);
			//}
			return 	Saphire::Core::Types::String(buffer);
		}

		 void CSaphireDebug::Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )
		 {

				Saphire::Core::Types::String output;
				Saphire::Core::Types::String info;

				memset(buffer,0,1024);
				va_list args;
				va_start (args, format);
					vsnprintf (buffer,1020,format.c_str(), args );
				va_end (args);
				output.append(buffer,1024);


				 info = toStringColor(RESET ,GREEN);
				 info += "[";
				 info += where;
				 info += "]";

				 Saphire::Core::Types::String color = toStringColor(RESET ,WHITE);
				 info += color;
				 info += " ";

				printf ("%s%s \n",info.c_str(),output.c_str());

		 }

		 void CSaphireDebug::Error(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )
		 {

				Saphire::Core::Types::String output;
				Saphire::Core::Types::String info;

				memset(buffer,0,1024);
				va_list args;
				va_start (args, format);
					vsnprintf (buffer,1020,format.c_str(), args );
				va_end (args);
				output.append(buffer,1024);



				 info = toStringColor(RESET ,RED);
				 info += "[";
				 info += where;
				 info += "]";

				 Saphire::Core::Types::String color = toStringColor(RESET ,CYAN);
				 info += color;
				 info += " ";

				printf ("%s%s \n",info.c_str(),output.c_str());

		 }

} /* namespace Manager */
} /* namespace Saphire */
