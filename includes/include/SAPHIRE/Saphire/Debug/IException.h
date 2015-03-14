/*
 * xException.h
 *
 *  Created on: 01-01-2013
 *      Author: rast
 */





#ifndef XEXCEPTION_H_
#define XEXCEPTION_H_

namespace xEngine {
		namespace Core {
			namespace Debug {


	#define THROW_ERROR(TEXT) throw xDebug::xException(TEXT,__FILE__,__LINE__)

	class IException : public std::exception
	{
		public:

		IException() throw ()
			{
						getCStack();

				  	  	whatText = NULL;
					    whereFile = NULL;
					    execFileName = NULL;
					    whereLine = 0;

						setExeName(XAPPLICATION_NAME);
						setWhat ("xException");
						setWhere("xException",0);
			}

			 ~IException() throw ()
			 {

			 }

			 IException(const char * File,unsigned int Line) throw ()
			{
				 	 getCStack();

			  	  	whatText = NULL;
				    whereFile = NULL;
				    execFileName = NULL;
				    whereLine = 0;

						setExeName(XAPPLICATION_NAME);
						setWhat ("xException");
						setWhere(File,Line);
			}



			 IException(const char * Text) throw ()
			{
				 	 getCStack();

			  	  	whatText = NULL;
				    whereFile = NULL;
				    execFileName = NULL;
				    whereLine = 0;

					setExeName(XAPPLICATION_NAME);
					setWhat (Text);
					setWhere("Unknow",0);
			}

			 IException(const char * Text,const char * File,unsigned int Line,...) throw ()
			{
				 getCStack();

			  	  	whatText = NULL;
				    whereFile = NULL;
				    execFileName = NULL;
				    whereLine = 0;

						setExeName(XAPPLICATION_NAME);

						setWhere(File,Line);

						int size = strlen(Text)*2;
						char buffer[size];
						memset((void*)buffer,0,size);

						va_list arg;
						va_start(arg, Line);
						#ifdef xANDROID

						#else
							vsnprintf(buffer, size,Text, arg);
						#endif
						va_end(arg);
						setWhat (buffer);

			}

			 IException(const char * App,const char * Text,const char * File,unsigned int Line,...) throw ()
			{
				 	 getCStack();

			  	  	whatText = NULL;
				    whereFile = NULL;
				    execFileName = NULL;
				    whereLine = 0;

						setExeName(App);

						setWhere(File,Line);

						int size = strlen(Text)*2;
						char buffer[size];
						memset((void*)buffer,0,size);

						va_list arg;
						va_start(arg, Text);
						#ifdef xANDROID

						#else
						vsnprintf(buffer, size,Text, arg);
						#endif
						va_end(arg);
						setWhat (buffer);

			}
			  virtual const char * what () const throw ()
			  {
						  return whatText;
			  }

			  virtual const char * file () const throw ()
			  {
						  return whereFile;
			  }

			  virtual unsigned int line () const throw ()
			  {
						  return whereLine;
			  }

			  virtual  const char * exeName () const throw ()
			{
					  return execFileName;
			}

			  virtual void dumpException() const throw ()
			{
				  //WYjatek w xcore
					printf ("=====================================\n\r");
					printf("%s: %s \n\r","Unsupported exception in module",exeName());
					printf("Error: %s \n\r",what());
					printf(" in file %s:%i\n\r",file(),line());
					printf("%s\n\r","Immediate Exit !!!");
					printf("=====================================\n\r");
					dumpCallStack(false,"Unknow exception");
			}


			  //const std::array<EStack > & getStack()
			  //{
				//	 return stack;
			//  }

		private:

			  void setWhat (const char * Text)
			  {
				  	 printf("Exception: %s \n\r",Text);

				  	  if(whatText) { delete whatText; }
				  	  int size = strlen(Text);

				  	  whatText = new char[size+1];
				  	  memset((void*)whatText,0,size+1);
				  	  memcpy((void*)whatText,(void*)Text,size);

			  }


			  void setWhere (const char * File,unsigned int Line)
			  {
				  //Where

			  	  if(whereFile) { delete whereFile; }
				  int size = strlen(File);

				  whereFile = new char[size+1];
				  memset((void*)whereFile,0,size+1);
				  memcpy((void*)whereFile,(void*)File,size);

				  //Line
				  	  whereLine = Line;

			  }

			  void setExeName (const char * execName)
			  {

		  	 	  if(execFileName) { delete execFileName; }
		  	  	  int size = strlen(execName);

		  	  	  execFileName = new char[size+1];

		  	  	  memset((void*)execFileName,0,size+1);
		  	  	  memcpy((void*)execFileName,(void*)execName,size);


			  }


			  void getCStack()
			  {
				 // stack = getCallStack();
			  }

			   char * whatText;
			   char * whereFile;
			   char * execFileName;

			   unsigned int whereLine;

			// std::array<EStack > stack;
	};

}}}

#endif /* XEXCEPTION_H_ */
