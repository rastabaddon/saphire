/*
 * String.h
 *
 *  Created on: 22 sty 2015
 *      Author: rast
 */

#ifndef STRING_H_
#define STRING_H_

namespace Saphire {
	namespace Core
	{
		namespace Types
		{

			typedef enum {
				WCHAR,
				CCHAR,
			} TextCode;

			template <typename _T>
		    class Basic_String :public Saphire::IBaseObject
		    {
		    	public:

//ALL TYPES
					Basic_String() {
						 _string_buffer = NULL;
						_size=0;
						type = WCHAR;

					}


					~Basic_String() {

					}

					 bool compare(const Basic_String<_T>  & _string) { return false; }
					 bool operator==(const Basic_String<_T>  & _string) { return false; }
					 Basic_String<_T>  &operator=(const Basic_String<_T>  & _string) { Basic_String<_T>  _this = (*this); return _this; }
					 Basic_String<_T>  & operator++() {  return *this; }
					 Basic_String<_T>  operator++(int) { Basic_String<_T>  _this = (*this); return _this; }

					 Basic_String<_T> &append(const _T * _stringc,Saphire::Core::Types::size size) {

						 	 	 Saphire::Core::Types::size rel = _realocate(_size+size);


						 	 	 _copy(_stringc,_string_buffer,size,rel);

								return * this;
						}

						Basic_String<_T> &append(const _T * _stringT) {

							return this->append(_stringT,_strlen(_stringT));
						}

						Basic_String<_T> &append(_T  & _stringT) { return this->append(&_stringT); }

					Basic_String<_T> &append(Basic_String<_T> & _stringT) {

							if(this == &_stringT) return * this;

							return this->append(_stringT.c_str());
						}


						Basic_String<_T> &operator+=(const _T * _stringT) {

							return this->append(_stringT);
						}

						Basic_String<_T> &operator+=(_T & _stringT) {

							return this->append(&_stringT,_strlen(&_stringT));
						}

						Basic_String<_T>  & operator+=(const _T & _stringT)
						{

							return this->append(&_stringT,_strlen(&_stringT));
						}

						Basic_String<_T> &operator+=(Basic_String<_T> & _stringT) {

							if(this == &_stringT) return * this;

							return this->append(_stringT);
						}


//WILD CHAR
					Basic_String( const wchar_t * _stringw) {
							Basic_String(); type = WCHAR;
							append((_T *)_stringw);

					}

//CHAR
					Basic_String( const char * _stringc) {
						Basic_String(); type = CCHAR;
						append((_T *)_stringc);

					}

					template <typename _T1>
					Basic_String<_T1> str() { return Basic_String<_T1>(_string_buffer); }

					Basic_String<char> c_string() { return Basic_String<char>(_string_buffer); }
					Basic_String<wchar_t> w_string() { return Basic_String<wchar_t>(_string_buffer); }

					const _T * c_str() { return _string_buffer; }

//other

					Saphire::Core::Types::size  length() const { return _size; }
					Saphire::Core::Types::size length() { return _size; }

					Saphire::Core::Types::TextCode getType()
					{
						return type;
					}

		    	private:


					Saphire::Core::Types::size _strlen(const _T * text)
					{
						return strlen(text);

					}


					//CHaracters
					Saphire::Core::Types::size _copy(const _T * from,const _T * to,Saphire::Core::Types::size cpySize,Saphire::Core::Types::size rel=0)
					{
						  if(!cpySize) return 0;

						  if(rel+cpySize>_size) {
							  cpySize = _size - rel;
						  }



						  if(from&&to) {


							  memcpy((void *)(to+rel),(void *)from,cpySize*sizeof(_T));

						  }


						  return cpySize;
					}

					Saphire::Core::Types::size _realocate(Saphire::Core::Types::size newSize)
					{
						//Size is in characters
						//  printf("_realocate A %u > %u  \n",_size,newSize);

						Saphire::Core::Types::size old_size = _size;
						Saphire::Core::Types::size cpySize = old_size;
						_T * buffer = new _T[newSize+10];
						if(newSize<old_size) { cpySize=newSize; }
						memset((void *)buffer,0,size_t((newSize+2)*sizeof(_T)));
						if(cpySize) _copy(_string_buffer,buffer,cpySize);
						if(old_size&&_string_buffer) delete _string_buffer;


						_string_buffer = buffer;
						_size = newSize;

						//printf("_realocate B (%p) %u \n",_string_buffer,_size);

						return old_size; //Return in bytes
					}

					Saphire::Core::Types::TextCode type = WCHAR;
					_T * _string_buffer=NULL;
					Saphire::Core::Types::size _size=0;
			};

			typedef Basic_String<wchar_t> WString;
			typedef Basic_String<char> CString;
			typedef std::string String;

		}
	}
}

#endif /* STRING_H_ */
