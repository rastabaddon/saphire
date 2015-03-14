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

		Saphire::Core::Types::String CSaphireDebug::getName()
		{
			return Saphire::Core::Types::String("saphire-debug");
		}

		Saphire::Core::Types::String CSaphireDebug::toStringColor(int attr,int fg,int bg)
		{
			char buffer[256];
			snprintf (buffer,255,"%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
			return 	Saphire::Core::Types::String(buffer);
		}

		 void CSaphireDebug::Debug(Saphire::Core::Types::String where,Saphire::Core::Types::String format, ... )
		 {

				Saphire::Core::Types::String output;
				Saphire::Core::Types::String info;
				char buffer[256];
				memset(buffer,0,256);
				va_list args;
				va_start (args, format);
					vsnprintf (buffer,255,format.c_str(), args );
				va_end (args);
				output.append(buffer,256);


				 info = toStringColor(RESET ,GREEN,BBLACK);
						 info += "[";
						 info += where;
						 info += "]";
						 Saphire::Core::Types::String color = toStringColor(RESET ,WHITE,BBLACK);
						 info += color;
						 info += " ";

						printf ("%s%s \n",info.c_str(),output.c_str());

				return;
/*
			 	Saphire::Core::Types::String output;
			 	Saphire::Core::Types::String info;

				char buffer[256];
				memset(buffer,0,256);
				va_list args;
				va_start (args, format);
				vsnprintf (buffer,255,format.c_str(), args );
				va_end (args);
				output.append(buffer,256);

				 info = toStringColor(RESET ,GREEN,BBLACK);
				 info += "[";
				 info += where;
				 info += "]";
				 Saphire::Core::Types::String color = toStringColor(RESET ,WHITE,BBLACK);
				 info += color;
				 info += " ";

				printf ("%s%s \n",info.c_str(),output.c_str());
				fflush(stdout);




			 	 /*
		 	 	 Saphire::Core::Types::String output;
			 	 Saphire::Core::Types::String info;

			 	 info = "["; info += where; where = info; info = "";
				 where += DEBUG_WHERE; where = where.substr(0,strlen(DEBUG_WHERE));
				 where.erase(where.size()); where += "]";

				 info = toStringColor(RESET ,GREEN,BBLACK);
				 info += where;
				 info += toStringColor(RESET ,WHITE,BBLACK);

				char buffer[256];
				memset(buffer,0,256);
				va_list args;
				va_start (args, format);
				vsnprintf (buffer,255,format.c_str(), args );
				va_end (args);
				output.append(buffer,256);

							//output.remove('\r');
				 		 	//output.remove('\t');

				Saphire::Core::Types::s32 c;
				Saphire::Core::Types::s32  max = 80-strlen(DEBUG_WHERE);
					if(output.size()<Saphire::Core::Types::u32(max))
					{
						output.append(DEBUG_CLEAR); output = output.substr(0,max);
						printf ("%s%s",info.c_str(),output.c_str());
					} else {
						Saphire::Core::Types::String  line = "";
						while(output.size())
						{

								c = output.find_first_of('\n');
								if(!(c>-1 && c<max)) { c = max; }
								line = output.substr(0,c);
								//line.remove('\n');
								//line.remove('\r');
								//line.remove('\t');
								line.append(DEBUG_CLEAR);
								line = line.substr(0,max);
								printf ("%s%s",info.c_str(),line.c_str());
								output = output.substr(u32(c+1),s32(output.size()));
						}
				}

				fflush(stdout);
				*/
		 }


} /* namespace Manager */
} /* namespace Saphire */
