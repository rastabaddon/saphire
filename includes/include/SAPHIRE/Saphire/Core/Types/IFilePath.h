/*
 * IFilePath.h
 *
 *  Created on: 1 lut 2015
 *      Author: rast
 */

#ifndef IFILEPATH_H_
#define IFILEPATH_H_

namespace Saphire {
	namespace Core {

		namespace Types {

	   class IFilePath :public Saphire::Core::Types::String
	    {
	    public:
	    	IFilePath(Saphire::Core::Types::String string);
	    	IFilePath(const char * _stringc);
	    	virtual ~IFilePath(){};


	    };

		}
	}
}




#endif /* IFILEPATH_H_ */
