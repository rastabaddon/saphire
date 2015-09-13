/*
 * IDirEntry.h
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#ifndef IDIRENTRY_H_
#define IDIRENTRY_H_



namespace Saphire {

	namespace Core {

		namespace Files {

				 typedef enum
				{
					TFILE = 0,
					TDIR = 1,
				}  TDIR_ENTRY;

				class IDirEntry : public Saphire::IBaseObject
				{
					public:
					IDirEntry(Saphire::Core::Types::String _name="",Saphire::Core::Types::String _path="",Saphire::Core::Files::TDIR_ENTRY _type=Saphire::Core::Files::TDIR_ENTRY::TFILE)
					{
						name = _name;
						path = _path;
						type = _type;
					}

					~IDirEntry() {}
					virtual Saphire::Core::Types::String getName(){ return name; };
					virtual Saphire::Core::Types::String getPath(){ return path; };
					virtual Saphire::Core::Files::TDIR_ENTRY getType(){ return type; };

					private:
						Saphire::Core::Types::String name;
						Saphire::Core::Types::String path;
						Saphire::Core::Files::TDIR_ENTRY type;
				};


		}
	}
}




#endif /* IDIRENTRY_H_ */
