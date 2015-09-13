/*
 * ICallbackFunction.H
 *
 *  Created on: 26 sie 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_OBJECTS_ICALLBACKFUNCTION_H_
#define INCLUDE_SAPHIRE_SAPHIRE_OBJECTS_ICALLBACKFUNCTION_H_

namespace Saphire {

	namespace Core {

		namespace Objects {

				class ICallbackFunction : public Saphire::IBaseObject {
						public:
							// Constructor, copy constructor and destructor
							ICallbackFunction(){ callback=NULL; }
							virtual Saphire::Core::Types::IAnyType execute(  Saphire::Core::Types::IAnyType param  ) const{ if(callback) { return callback(param); } Saphire::Core::Types::IAnyType ret; return ret; };
							virtual Saphire::Core::Types::IAnyType operator()( Saphire::Core::Types::IAnyType param    ) const{ if(callback) { return callback(param);  } Saphire::Core::Types::IAnyType ret; return ret;  };

							virtual Saphire::Core::Types::String getObjectType() { return "ICallbackFunction"; };


						protected:
							Saphire::Core::Types::IAnyType ( *callback)(  Saphire::Core::Types::IAnyType );
				};

		}
	}
}


#endif /* INCLUDE_SAPHIRE_SAPHIRE_OBJECTS_ICALLBACKFUNCTION_H_ */
