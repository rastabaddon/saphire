/*
 * ILibrary.h
 *
 *  Created on: 29 cze 2014
 *      Author: rast
 */

#ifndef ILIBRARY_H_
#define ILIBRARY_H_

	namespace Saphire {
		namespace Core {
			class ILibrary  : public Saphire::IBaseObject {
				public:
					virtual void * getEntrance(Saphire::Core::Types::String symbol)=0;
			};


		}
	}

#endif /** ILIBRARY_H_ */
