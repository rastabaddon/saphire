/*
 * xTypes.h
 *
 *  Created on: 01-01-2013
 *      Author: rast
 */

#ifndef XTYPES_H_
#define XTYPES_H_

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

					typedef void * pointer;
					typedef  char c8;



	}
}
}

	#include "List.h"
	#include "String.h"
	#include "IFilePath.h"

#endif /* XTYPES_H_ */
