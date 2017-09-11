/*!
\file ifile.h "server\desktop\src\cross\ifile.h"
\authors Alexandr Barulev, Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 0.1
\date 28 February 2017
*/

#pragma once
#include "..\defines.h"
#include "windows\unicodeconverter.h"
#include "..\tools\exceptions\fileexception.h"

/// The file meta data structure
typedef struct
{
	char* filename;			///< The file name with its local path
	char* filepath;			///< The path to the file location (dir)
	char* filetype;			///< The file extention
	time_t creationdate;	///< The file creation date
} FileMeta;

/// The opening file rule
typedef enum
{
	READONLY,		///< Opens the existing file in the READ ONLY mode
	WRITENEWFILE,	///< Creates a new file 
	WRITE,			///< Opens the existing file to write into(or truncate the existing file to write into later)
	READWRITE,		///< Opens the file for both reading and writing (will truncate the existing file)
	WRITEATTHEEND	///< Writes in the end of the existing file or creates a new file
} FileOpenMode;

/// The position used as a reference for the offset
typedef enum 
{ 
	START,			/// The beginning of the file
	CURRENT,		/// The current position of the file pointer
	END				/// The end of the file
} SeekReference;

/*!
\class IFile ifile.h "server\desktop\src\cross\ifile.h"
\brief  The class-interface for the OS-dependent classes.
The defined methods should be realized in the OS-dependent classes.
*/
class IFile
{
public:
	/*!
	Deallocates memory.
	*/
	virtual ~IFile() {};

	/*!
	Opens the file in the predetermined mode.
	\param[in] mode The mode to open the file with (the list of the possible modes is defined in ifile.h).
	*/
	virtual void Open(FileOpenMode mode) = 0;

	/*!
	Opens the file in the predetermined mode. The previously opened file will be closed.
	\param[in] fileName The name of the file to be opened.
	\param[in] mode The mode to open the file with (the list of the possible modes is defined in ifile.h).
	*/
	virtual void Open(const char *fileName, FileOpenMode mode) = 0;

	/*!
	Closes the file descriptor.
	*/
	virtual void Close() = 0;

	/*!
	Sets a new file name.
	\param[in] newFileName The name to be associated with the current file.
	*/
	virtual void Rename(const char *newFileName) = 0;

	/*!
	Checks if the file exists.
	\return TRUE if the file exists, FALSE otherwise.
	*/
	virtual bool Exist() = 0;

	/*!
	Deletes the file.
	*/
	virtual void Delete() = 0;

	/*!
	Returns the size of the file.
	\return The size of the file.
	*/
	virtual size_lt FileSize() = 0;

	/*!
	Moves the file pointer of the specified file.
	\param[in] offset The offset of the new pointer position.
	\param[in] move The position used as a reference for the offset.
	\return A new pointer position.
	*/
	virtual size_lt Seek(size_lt offset, SeekReference move) = 0;

	/*!
	Reads one byte from the file.
	\return The value of the byte read or -1 if it can't be read (ex. EOF).
	*/																	  
	virtual int ReadByte() = 0;

	/*!
	Reads a block from the file.
	\param[out] block The array of bytes from the file.
	\param[in] sizeBlock The number of bytes to be read.
	\return A number of bytes read from the file.
	*/
	virtual size_lt ReadBlock(byte *block, size_lt blockSize) = 0;
			
	/*!
	Writes one byte in the file.
	\param[in] b The byte to be save.
	*/
	virtual void WriteByte(byte b) = 0;
	
	/*!
	Writes a block into the file.
	Clears the cache of the read bytes.
	\param[in] block The array of bytes to be written.
	\param[in] blockSize The number of bytes to be written.
	*/
	virtual void WriteBlock(byte *block, size_lt sizeBlock) = 0;

};
