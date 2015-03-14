/*
 * aplatformdepended_inc.h
 *
 *  Created on: 18 sty 2015
 *      Author: rast
 */

#ifndef APLATFORMDEPENDED_INC_H_
#define APLATFORMDEPENDED_INC_H_

	#include "Platforms/platforms_inc.h"


	#define Delete(d) if(d) { d->drop(); } d=NULL
	#define Free(d) if(d) { d->drop(); } d=NULL
	#define Grab(d) if(d) { d->grab(); }

#endif /* APLATFORMDEPENDED_INC_H_ */
