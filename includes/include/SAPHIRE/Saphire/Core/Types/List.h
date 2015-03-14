/*
 * List.h
 *
 *  Created on: 22 sty 2015
 *      Author: rast
 */

#ifndef LIST_H_
#define LIST_H_

namespace Saphire {
	namespace Core
	{
		namespace Types
		{

			template<typename _T>
			class List : public std::list<_T>
			{
				public:
					/** LOCK FOR CURRENT THREAD **/
					bool lock() {b_Lock = true; return true;};
					/** UNLOCK FOR CURRENT THREAD **/
					bool unlock() { b_Lock = false; return true; };
					/** IS LOCK? **/
					bool islock() { return b_Lock; };
					/** IS LOCK BY CURRENT THREAD **/
					bool ismylock() { return true; };

				private:
					bool b_Lock;
			};
		}
	}
}

#endif /* LIST_H_ */
