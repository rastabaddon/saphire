/*
 * SimpleTypes.h
 *
 *  Created on: 4 wrz 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_CORE_TYPES_SIMPLETYPES_H_
#define INCLUDE_SAPHIRE_SAPHIRE_CORE_TYPES_SIMPLETYPES_H_

namespace Saphire {
namespace Core
{
	namespace Types
	{

					typedef  float f32;
					typedef  double f64;
					typedef  long double f80;

					typedef int  c32;//GLsizei



					typedef  unsigned char u8;
					typedef  unsigned short u16;
					typedef  unsigned int u32;						//GLuint
					typedef  unsigned long long u64;
					typedef  std::size_t size;
					typedef  signed char s8;
					typedef  signed short s16;
					typedef  signed int s32;
					typedef  long long s64;
					typedef  char c8;

					typedef u8 * pointer;

	}
}
}



#endif /* INCLUDE_SAPHIRE_SAPHIRE_CORE_TYPES_SIMPLETYPES_H_ */
