/*!
\file file.h "server\desktop\src\common\file.h"
\authors Alexandr Barulev, Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 0.1
\date 28 February 2017
*/

#pragma once
#include <string>

#ifdef _WIN32
#include "../cross/windows/winfile.h"
typedef WinFile OSFile;
#elif _unix_
typedef UnixFile OSFile;
#include "../cross/unix/unixfile.h"
#endif

using namespace std;

/*!
\class File file.h "server\desktop\src\common\file.h"
\brief  The file interface.
Provides an interface for a common file structure and its actions.
The factory(?) for the unix/bsd/windows structure of the file.
*/
class File
{
	/// \todo File(const File &file); operator = (); GetInfo();

public:
	/*!
	Initialises cache buffers and the OS-dependent file structure.
	*/
	File();

	/*!
	Initialises cache buffers and the OS-dependent file structure.
	\param[in] fileName The name of the file to be used.
	\param[in] bufferSize The maximum size of a cache buffer.
	*/
	File(const char* fileName, size_lt bufferSize = FILE_BUFFER_SIZE);

	/*!
	Deallocates memory of the cache buffers and the OS-dependent file structure.
	*/
	~File();

	/*!
	Opens a file in the predetermined mode.
	\param[in] fileName The name of the file to be used.
	\param[in] mode The mode to open the file with (the list of the possible modes is defined in ifile.h).
	*/
	void Open(const char *fileName, FileOpenMode mode);

	/*!
	Opens a file in the predetermined mode.
	\param[in] mode	The mode to open the file with (the list of the possible modes is defined in ifile.h).
	*/
	void Open(FileOpenMode mode);

	/*!
	Flushes bytes from the cache buffer to write into the file.
	Closes the file descriptor.
	*/
	void Close();

	/*!
	Sets a new file name.
	\param[in] newFileName The name to be associated with the current file.
	*/
	void Rename(const char *newFileName);

	/*!
	Sets a new file name. Static.
	\param[in] fileName The current name of the file to be replaced.
	\param[in] newFileName The name to be associated with the current file.
	*/
	static void Rename(const char *fileName, const char *newFileName);

	/*!
	Checks if the file exists.
	\return TRUE if the file exists, FALSE otherwise.
	*/
	bool Exist();

	/*!
	Checks if the file exists. Static.
	\param[in] fileName The name of the file to be checked.
	\return TRUE if the file exists, FALSE otherwise.
	*/
	static bool Exist(const char *fileName);

	/*!
	Gets the file info.
	\return Info about the file.
	*/
	FileMeta GetInfo();

	/*!
	\TODO
	Gets the file info. Static.
	\param[in] string fileName The name of the file to be read.
	\return Info about the file.
	*/
	static FileMeta GetInfo(const char *fileName);

	/*!
	Deletes the file.
	*/
	void Delete();

	/*!
	Deletes the file. Static.
	\param[in] fileName The name of the file to be deleted.
	*/
	static void Delete(const char *fileName);

	/*!
	Checks if all the data from the buffer is already read and fills it with new data.
	\return TRUE if the cache (buffer?) is filled with the new data, FALSE otherwise (ex. EOF).
	*/
	inline bool CheckCache();

	/*!
	Reads one byte from the file.
	\return The value of the read byte or -1 if it can't be read (ex. EOF).
	*/
	int ReadByte();

	/*!
	Reads a block from the file.
	\param[out] block The array of bytes from the file.
	\param[in] sizeBlock The number of bytes to be read.
	\return A number of the bytes read.
	*/
	size_lt ReadBlock(byte *block, size_lt sizeBlock);

	/*!
	Saves one byte in the cache.
	Will be written into the file after the cache fills up or after the Flush method is called.
	Clears the cache of the read bytes.
	\param[in] b The byte to be saved.
	*/
	void WriteByte(byte b);

	/*!
	Writes a block into the file.
	Clears the cache of the read bytes.
	\param[in] block An array of bytes to be written.
	\param[in] blockSize The number of bytes to be written.
	*/
	void WriteBlock(byte *block, size_lt sizeBlock);

	/*!
	Writes into the file cache of the written bytes.(?)
	Clears the cache of the read bytes.
	*/
	void Flush();

	/*!
	Moves the file pointer of the specified file.
	\param[in] offset The offset of a new pointer position.
	\param[in] move The position used as a reference for the offset.
	\return A new pointer position.
	*/
	size_lt Seek(size_lt offset, SeekReference move);

	/*!
	Returns the size of the file.
	\return The size of the file.
	*/
	size_lt FileSize();

	/*!
	Returns the size of the file. Static.
	\return The size of the file.
	*/
	static size_lt FileSize(const char *fileName);



	/////////////////////////////////////////////////////////////////////////////
	////////////////////           STATIC METHODS            ////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/*!
	Reads the full file. Static.
	\param[in] fileName The name of the file to be read.
	\param[out] byteArr The data read from the file.
	\return A number of the bytes read.
	*/
	static size_lt ReadAllBytes(const char *fileName, byte **byteArr);

	/*!
	Reads the full file and parses it into strings. Static.
	\param[in] fileName The name of the file to be read.
	\param[out] byteArr The data to be read from the file.
	\return A number of the strings read.
	*/
	static size_lt ReadAllCharStrings(const char *fileName, char*** charStrings);

	/*!
	Reads the full file and parses it into strings. Static.
	\param[in] fileName The name of the file to be read.
	\param[out] byteArr The data to be read from the file.
	\return A number of the strings read.
	*/
	static size_lt ReadAllStrings(const char *fileName, string** stringArray);

	/*!
	Reads the buffer and parses it into strings. Static.
	\param[out] string The string array from the buffer.
	\param[in] buf The buffer to be read.
	\param[in] startPos The position in the buffer from which the reading starts.
	\param[in] sizeBuf The size of the buffer.
	\return A number of the strings read.
	*/
	static size_lt ReadStringFromBuffer(char **string, byte *buf, size_lt *startPos, size_lt sizeBuf);

	/*!
	Opens the file and writes all the data into it. Static.
	\param[in] fileName The name of the file to be read.
	\param[in] data The data to be written into the file.
	\param[in] size The size of the data buffer.
	\param[in] mode Opens the file mode.
	*/
	static void WriteAllBytes(const char *fileName, byte* data, size_lt size, FileOpenMode mode = WRITENEWFILE);

	/*!
	Opens the file and writes all the data (char string format) into it. Static.
	\param[in] string fileName The name of the file to be read.
	\param[in] charStrings The strings to be written into the file.
	\param[in] countStrings The number of the strings to be written into the file.
	\param[in] mode Opens the file mode.
	*/
	static void WriteAllCharStrings(const char *fileName, char** charStrings, size_lt countStrings, FileOpenMode mode = WRITENEWFILE);

	/*!
	Opens the file and writes all the data (string format) into it. Static.
	\param[in] string fileName The name of the file to be read.
	\param[in] charStrings The strings to be written into the file.
	\param[in] countStrings The number of the strings to be written into the file.
	\param[in] mode Opens the file mode.
	*/
	static void WriteAllStrings(const char *fileName, string *strings, size_lt countStrings, FileOpenMode mode = WRITENEWFILE);
	
	/*!
	\TODO
	Gets the last modified file. Static.
	\param[in] string fileName The name of the file to be read.
	\return Info about the latest file modified.
	*/
	static FileMeta LastModified(const char *fileName);

private:
	IFile *_file;					///< the OS-dependent file structure 

	char *_fileName;				///< The path to a file (including its name)
	bool _opened;					///< The descriptor opening status

	size_lt _bufferSize;			///< The Determined size of the cache buffer

	/*read-read-read, please rewrite the variables accordingly*/ byte *_cacheReaded;				///< The cache of the bytes read from the file    
	size_lt _posInCacheReaded;		///< The pointer to a position in the cache of the read bytes
	size_lt _bytesInCacheReaded;	///< The number of the bytes left in the cache of the read bytes

	byte *_cacheToWrite;			///< The cache of the bytes ready to be written into the file
	size_lt _posInCacheToWrite;		///< The pointer to a position in the cache of bytes written into the file
	size_lt _bytesInCacheToWrite;	///< The number of the bytes left in the cache of bytes written into the file

};