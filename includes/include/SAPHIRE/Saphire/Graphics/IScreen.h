/*
 * IScreen.h
 *
 *  Created on: 19 sie 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_GRAPHICS_ISCREEN_H_
#define INCLUDE_SAPHIRE_SAPHIRE_GRAPHICS_ISCREEN_H_


namespace Saphire {

	namespace Core {

		namespace Graphics {

			typedef enum {
				TE_SOFTWARE,
				TE_OPENGL,
			} TE_SAPHIRE_DRIVER;

			class IScreen  : public Saphire::IBaseObject {
				public:

			};


		}
	}
}

#endif /* INCLUDE_SAPHIRE_SAPHIRE_GRAPHICS_ISCREEN_H_ */
