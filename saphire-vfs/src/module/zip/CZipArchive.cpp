/*
 * CNativeArchive.cpp
 *
 *  Created on: 14 mar 2015
 *      Author: rast
 */

#include "CZipArchive.h"

namespace Saphire {
namespace Core {
namespace Files {

CZipArchive::CZipArchive(Saphire::Core::Types::String name,Saphire::Module::ICoreModule * core) {
	SPTR_core = core;
	Grab(SPTR_core);
	path = name;
	SPTR_core->Debug(getName(),"Archive open %s ",path.c_str());
	//Is open as normal file
	zipFile = SPTR_core->getVFS()->openFile(path,true);



	Saphire::Core::Types::size  size = (zipFile->get(zipFile->getSize()-3) << 24) | (zipFile->get(zipFile->getSize()-2) << 16) + (zipFile->get(zipFile->getSize()-1) << 8) + zipFile->get(zipFile->getSize());


	SZIP_FILE_HEADER * fileHeader = NULL;
	SZIP_FILE_DATA * dataHeader;

	Saphire::Core::Types::String text;
	Saphire::Core::Types::String fname;

	 char * text_p;
	 void  * data_p;
	 void * extra_p;
	 Saphire::Core::Files::CZipFile * vzipFile;

	 for(int i=0; i<zipFile->getSize();i++)
	 {
		 fileHeader = (SZIP_FILE_HEADER *)zipFile->getPointer(i);
		 if(fileHeader->signature == 0X4034B50) {

		/*
		 SPTR_core->Debug(getName(),"file header SIGNATURE %#4lX ",fileHeader->signature);
		 SPTR_core->Debug(getName(),"VERSION %#2X ",fileHeader->version);
		 SPTR_core->Debug(getName(),"GPB %#2X ",fileHeader->generalPurposeBitFlag);
		 SPTR_core->Debug(getName(),"Compresed method %#2X ",fileHeader->compressionMethod);
		 SPTR_core->Debug(getName(),"TIME %#2X ",fileHeader->modTime);
		 SPTR_core->Debug(getName(),"DATE %#2X ",fileHeader->modDate);
		 SPTR_core->Debug(getName(),"CRC %#4lX ",fileHeader->CRC);

		 SPTR_core->Debug(getName(),"Compresed size %llu bytes %#4lX",fileHeader->compressedSize,fileHeader->compressedSize);
		 SPTR_core->Debug(getName(),"Uncompresed size %llu bytes %#4lX",fileHeader->uncompressedSize,fileHeader->uncompressedSize);

		 SPTR_core->Debug(getName(),"FILE NAME SIZE %lu %#4lX",fileHeader->fileNameSize,fileHeader->fileNameSize);
		 SPTR_core->Debug(getName(),"EXTRA SIZE %lu %#4lX",fileHeader->ExtraFieldName,fileHeader->ExtraFieldName);
*/
		 text_p = (char *)zipFile->getPointer(i+30);
		 extra_p = (char *)zipFile->getPointer(i+30+fileHeader->fileNameSize);
		 dataHeader = (SZIP_FILE_DATA *)zipFile->getPointer(i+30+fileHeader->fileNameSize+fileHeader->ExtraFieldName);

		 fname = "";
		 fname.append(text_p,fileHeader->fileNameSize);
		 fname = fname.substr(fname.find_first_of("/")+1);

		 text = "/";
		 text.append(fname);


		 vzipFile = new Saphire::Core::Files::CZipFile(SPTR_core,text,false,this,fileHeader->compressionMethod,zipFile->getPointer(i+30+fileHeader->fileNameSize+fileHeader->ExtraFieldName),fileHeader->compressedSize,fileHeader->uncompressedSize);

		 files.push_back(vzipFile);
		 i = i+30+fileHeader->fileNameSize+fileHeader->ExtraFieldName+fileHeader->compressedSize-1;
		 text.clear();



		 } else {
			 //SPTR_core->Debug(getName(),"Central directory file header SIGNATURE %#4lX ignore now",fileHeader->signature);
			 break;
		 }
	 }


	 text_p = NULL;
	// SPTR_core->Debug(getName(),"FREE MEMORY HERE");
	// SPTR_core->Debug(getName(),"HERE %i",zipFile->getRefCount());
	 Free(zipFile);

}

CZipArchive::~CZipArchive() {

	Free(SPTR_core);
}

void * CZipArchive::getPointer(Saphire::Core::Types::size pos)
{
	return NULL;
}

const Saphire::Core::Types::String CZipArchive::getName() {
	return path;
}

const Saphire::Core::Types::String CZipArchive::getDebugName() {
	return "CZipArchive";
}

Saphire::Core::Types::size CZipArchive::getSize()
{
	return 0;
}


bool  CZipArchive::isFileExists(const Saphire::Core::Types::String & name)
{
	SPTR_core->Debug(getName(),"isFileExists  %s ",name.c_str());
	 for (std::list<Saphire::Core::Files::CZipFile *>::iterator it=files.begin(); it != files.end(); ++it)
	{

			if((*it)->getName()==name)  { return true; }
	}

	 SPTR_core->Error(getName(),"Not Found in zip file [%s] ",name.c_str());
	return false;
}

bool  CZipArchive::isDirExists(const Saphire::Core::Types::String & name)
		{
	SPTR_core->Debug(getName(),"isDirExists  %s NOT FINISH YET ",name.c_str());
	return false;
		}

Saphire::Core::Files::IFile * CZipArchive::openFile(Saphire::Core::Types::String path,bool writable)
{

	for (std::list<Saphire::Core::Files::CZipFile *>::iterator it=files.begin(); it != files.end(); ++it)
	{

			if((*it)->getName()==path) { (*it)->grab(); return (*it); }
	}

	return NULL;
}

} /* namespace Files */
} /* namespace Core */
} /* namespace Saphire */
