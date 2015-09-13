/*
 * ICallbackMethod.h
 *
 *  Created on: 26 sie 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_OBJECTS_ICALLBACKMETHOD_H_
#define INCLUDE_SAPHIRE_SAPHIRE_OBJECTS_ICALLBACKMETHOD_H_



namespace Saphire {

	namespace Core {

		namespace Objects {




#ifndef NULL
#define NULL 0
#endif
					template<class T>
					class ICallbackMethod : public ICallbackFunction {
						public:
						// Object initialization (constructor)

							ICallbackMethod( T *object, Saphire::Core::Types::IAnyType (T::*callback)(  Saphire::Core::Types::IAnyType param)):Saphire::Core::Objects::ICallbackFunction(),object(object),method(callback){}


							// Responsible for executing

							Saphire::Core::Types::IAnyType execute( Saphire::Core::Types::IAnyType param) const {
								return (object->*method)(param);
							}

							Saphire::Core::Types::IAnyType operator()(Saphire::Core::Types::IAnyType param) const {
								return (object->*method)( param);
							}

						protected:
							T *object;
							Saphire::Core::Types::IAnyType(T::*method)(Saphire::Core::Types::IAnyType param);
					};


		}
	}
}


#endif /* INCLUDE_SAPHIRE_SAPHIRE_OBJECTS_ICALLBACKMETHOD_H_ */
