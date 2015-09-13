/*
 * IAny.h
 *
 *  Created on: 20 sie 2015
 *      Author: rast
 */

#ifndef INCLUDE_SAPHIRE_SAPHIRE_CORE_TYPES_IANY_H_
#define INCLUDE_SAPHIRE_SAPHIRE_CORE_TYPES_IANY_H_

/*********************************************************************************8
 *  Examples
 *
 *    Saphire::Core::Types::s32  testuS32 = -255;
 *	   dane.set("test",testuF32);
 *	   testuS32 = dane.get("test",testuF32);
 *	   Debug(getDebugName(),"TEST f32 %f ",testuF32);
 *
 *	    Saphire::Core::Types::String testSTRING = "TEST TEST";
 *	    dane.set("test",testSTRING);
 *	    testSTRING = dane.get("test",testSTRING);
 *	    Debug(getDebugName(),"TEST STRING 4");
 *
 *		  dane.set("test",(Saphire::IBaseObject *)this);
 *		  pp = dane.get("test",pp);
 *
 */

namespace Saphire {
	namespace Core
	{
		namespace Objects {

			 class ICallbackFunction;
			template<class T>
			 class ICallbackMethod;
		}

		namespace Types
		{



			typedef enum {
					T_NULL = 0,
					T_NORMAL = 1,
					T_STRING = 2,
					T_BASE_OBJECT = 3,
					T_BOOLEAN = 4,
					T_CALLBACK = 5,

			} T_TYPES;

			class IAnyVar : public Saphire::IBaseObject
			{
				public:
						IAnyVar()
						{
							__type=T_NULL;
							any_data = 0;
						}

						~IAnyVar() {
							if(__type!=T_NULL)__clear<Saphire::Core::Types::u64>();
						}

						template <class T>
						void __clear()
						{
							    if(__type==T_NULL) return;


								T * _data = NULL;
								Saphire::IBaseObject * p;

								switch(__type)
								{
									case Saphire::Core::Types::T_TYPES::T_STRING :
										__type = T_NULL;

										memcpy(&_data,&any_data,sizeof(T));
										if(_data) delete _data;
										_data = NULL;
									break;
									case T_BASE_OBJECT:
										__type = T_NULL;

										memcpy(&_data,&any_data,sizeof(T));

										p = (Saphire::IBaseObject *)_data;

										memset(&_data,0,sizeof(Saphire::Core::Types::u64));




										Free(p);
										_data = NULL;
									break;

									default:
										__type = T_NULL;

										_data = 0;
									break;
								}

								memset(&any_data,0,sizeof(Saphire::Core::Types::u64));
								__type = T_NULL;
						}

						bool set(Saphire::Core::Types::String  value){



								if(__type!=T_NULL) __clear<Saphire::Core::Types::String>();


								Saphire::Core::Types::String * data = new Saphire::Core::Types::String();
								(* data) = value;
								memcpy(&any_data,&data,sizeof(Saphire::Core::Types::String *));
								__type =  Saphire::Core::Types::T_TYPES::T_STRING;



								return true;
						};

						bool set(bool value){
								if(__type!=T_NULL)  __clear<Saphire::Core::Types::String>();


								memcpy(&any_data,&value,sizeof(bool));
								__type =  Saphire::Core::Types::T_TYPES::T_BOOLEAN;

								return true;
						};

						bool set(Saphire::IBaseObject * value){
  							    if(__type!=T_NULL)  __clear<Saphire::IBaseObject *>();
								Grab(value);

								memcpy(&any_data,&value,sizeof(Saphire::IBaseObject *));
								__type =  Saphire::Core::Types::T_TYPES::T_BASE_OBJECT;

								return true;
						};

						bool setFunction(Saphire::IBaseObject * value){
								if(__type!=T_NULL)  __clear<Saphire::IBaseObject *>();
								Grab(value);

								memcpy(&any_data,&value,sizeof(Saphire::IBaseObject *));
								__type =  Saphire::Core::Types::T_TYPES::T_CALLBACK;

								return true;
						};


						template <class T>
						bool set(T  value){
							if(__type!=T_NULL) __clear<T>();

							memcpy(&any_data,&value,sizeof(T));
							__type = Saphire::Core::Types:: T_TYPES::T_NORMAL;
							return true;
						};

						template <class T>
						T get(T _forget=0){
							if(__type==T_NULL) return 0;
							T data;
							T * _data = NULL;
							switch(__type)
							{
									case Saphire::Core::Types::T_TYPES::T_STRING :

										memcpy(&_data,&any_data,sizeof(T));
										return (*_data);
									break;
									case Saphire::Core::Types::T_TYPES::T_BASE_OBJECT :

											memcpy(&data,&any_data,sizeof(T));
											return data;
									break;
									default:

										memcpy(&data,&any_data,sizeof(T));
										return data;
									break;
							}

						};

						Saphire::Core::Types::T_TYPES getType()
						{
							return __type;
						}

				private:
						Saphire::Core::Types::T_TYPES  __type;
						Saphire::Core::Types::u64 any_data;

			};

			typedef struct {
				Saphire::Core::Types::String name;
				Saphire::Core::Types::IAnyVar value;
			} TAnyVar;

			class IAnyType : public Saphire::IBaseObject
			{
			public:
					IAnyType()
					{

					}

					~IAnyType() {

					}

						template <class T>
						void __clear()
						{

						}

						bool set(Saphire::Core::Types::String name,Saphire::Core::Types::String  value){
							for( Saphire::Core::Types::List<TAnyVar*>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if((*iter)->name==name) {

									(*iter)->value.set(value); return true;
								}
							}


							TAnyVar * _var = new TAnyVar();
							_var->name = name;
							_var->value.set(value);
							__attributes.push_back(_var);


							return true;
						};



						bool set(Saphire::Core::Types::String name, Saphire::IBaseObject * value){

							for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
								{
									if((*iter)->name==name) {

										(*iter)->value.set(value);
										Free(value);
										return true;
									}
								}


								//TO powqinno byc NEW zeby nie usuwalo sie
								TAnyVar * _var = new TAnyVar();
								_var->name = name;

								_var->value.set(value);

								__attributes.push_back(_var);


								return true;
						};


						bool unset(Saphire::Core::Types::String name){
							for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if((*iter)->name==name) {
									__attributes.remove((*iter));
									return true;
								}
							}




							return true;
						};

						template <class T>
						bool set(Saphire::Core::Types::String name,T  value){
							for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if((*iter)->name==name) {

									(*iter)->value.set<T>(value); return true;
								}
							}
							TAnyVar * _var = new TAnyVar();
							_var->name = name;
							_var->value.set<T>(value);
							__attributes.push_back(_var);
							return true;
						};

						template <class T>
						T get(Saphire::Core::Types::String name,T _forget=0){
							for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if((*iter)->name==name) {
									return (T)(*iter)->value.get<T>((T)_forget);
								}
							}

							return 0;
						};

						template <class T>
						T get(Saphire::Core::Types::s32 index,T _forget=0){

							Saphire::Core::Types::s32 i=0;

							for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if(i==index) {
									return (T)(*iter)->value.get<T>((T)_forget);
								}
							}

							return 0;
						};

						Saphire::Core::Types::T_TYPES getType(Saphire::Core::Types::String name){
						for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if((*iter)->name==name) {
									return (*iter)->value.getType();
								}
							}

							return Saphire::Core::Types::T_TYPES::T_NULL;
						}

						bool is(Saphire::Core::Types::String name){
						for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
							{
								if((*iter)->name==name) {
									return true;
								}
							}

							return false;
						};

						Saphire::Core::Types::List<TAnyVar *> getAll()
						{
							return __attributes;
						}

						Saphire::Core::Types::s32 size()
						{
							return __attributes.size();
						}

						bool  addFuntion(Saphire::Core::Types::String name,Saphire::Core::Objects::ICallbackFunction * callback) {

							for( Saphire::Core::Types::List<TAnyVar *>::iterator iter=__attributes.begin(); iter != __attributes.end(); iter++ )
								{
									if((*iter)->name==name) {

										(*iter)->value.setFunction((Saphire::IBaseObject * )callback);

										return true;
									}
								}


								//TO powqinno byc NEW zeby nie usuwalo sie
								TAnyVar * _var = new TAnyVar();
								_var->name = name;

								_var->value.setFunction(( Saphire::IBaseObject * )callback);

								__attributes.push_back(_var);


								return true;


						}

						// Object initialization (constructor)
						template<class T>
						bool addFuntion( Saphire::Core::Types::String name,T *object, int(T::*callback)(void * param)) {
							Saphire::Core::Objects::ICallbackFunction * mcalback = new Saphire::Core::Objects::ICallbackMethod<T>( object, T::callback);
							return this->addFuntion(name,callback);
						}

						bool isFuntion(Saphire::Core::Types::String name) {
								if(getType(name)!=Saphire::Core::Types::T_TYPES::T_CALLBACK) return false;
								return true;
						}

						Saphire::Core::Objects::ICallbackFunction *  getFuntion(Saphire::Core::Types::String name) {
							if(!isFuntion(name)) return NULL;
							Saphire::Core::Objects::ICallbackFunction * pp=NULL;
							pp = this->get(name,pp);
							return pp;
						}

				private:
						Saphire::Core::Types::List<TAnyVar *> __attributes;

			};
		}
	}
}



#endif /* INCLUDE_SAPHIRE_SAPHIRE_CORE_TYPES_IANY_H_ */
