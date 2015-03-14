/*
 * vapass.h
 *
 *  Created on: 2012-06-30
 *      Author: rast
 */

#ifndef VAPASS_H_
#define VAPASS_H_


		#ifndef ANDROID

			/**
			 * Orginal va_pass
			 */
			/*** va_pass() (passing of ... variable length arguments ***/
			template<unsigned char count>
			struct SVaPassNext{
				SVaPassNext<count-1> big;
				unsigned long dw;
			};
			template<> struct SVaPassNext<0>{};
			//SVaPassNext - is generator of structure of any size at compile time.

			class CVaPassNext{
			public:
				SVaPassNext<50> svapassnext;
				CVaPassNext(va_list & args){

						try{//to avoid access violation

							memcpy(&svapassnext,  args, sizeof(svapassnext));

						} catch (...) {}

				}
			};

			#define va_pass(valist) CVaPassNext(valist).svapassnext
			/*** va_pass() (passing of ... variable length arguments ***/
		#else

			/**
			 * @TODO find better solution
			 * Fixing fucking Android - va_pass
			 */

			inline va_list __android_copy_valist(va_list &from)
			{
				va_list tmpva;
				va_copy(from,tmpva);
				return tmpva;
			}


			#define va_pass(valist) __android_copy_valist(valist)
		#endif


#endif /* VAPASS_H_ */
