/*!
\file winfile.h "server\desktop\src\cross\windows\winfile.h"
\authors Alexandr Barulev, Dmitry Zaitsev
\copyright © MSiYB 2017
\license GPL license
\version 0.1
\date 07 March 2017
*/

#pragma once

#include "../ifile.h"
#include "windows.h"

using namespace std;

/*!
\class WinFile winfile.h "server\desktop\src\cross\windows\winfile.h"
\brief  The Windows dependent structure of the file.
Provides the Windows-specified access to the file methods.
*/
class WinFile : public IFile
{
public:
	/*!
	Initializes a filename with null values.
	*/
	WinFile();
	
	/*!
	Sets a fileName with  the determined value.
	\param[in] fileName The name of the file.
	*/
	WinFile(const char *fileName);

	/*!
	Deallocates memory and closes the file description.
	*/
	~WinFile();
	
	/*!
	Opens the file in the predetermined mode.
	\param[in] mode The mode to open the file in (the list of the possible modes is defined in ifile.h).
	*/
	virtual void Open(FileOpenMode mode) override;

	/*!
	Opens the file.
	\param[in] fileName The name of the file to be opened.
	\param[in] mode Depends mode in which file will be opened.
	*/
	virtual void Open(const char *fileName, FileOpenMode mode) override;

	/*!
	Opens the file. Static. For TCHAR.
	\param[in] fileName The name of the file to be opened.
	\param[in] mode Determines(?) the mode in which the file will be opened.
	\return The handle of the file.
	*/
	static HANDLE tOpen(const TCHAR *fileName, FileOpenMode mode);

	/*!
	Closes the file descriptor.
	*/
	virtual void Close() override;

	/*!
	Closes the file. Static.
	\param[in] hFile The handle of the opened file.
	*/
	static void Close(HANDLE hFile);

	/*!
	Sets a new file name.
	\param[in] newFileName The name to be associated with the current file.
	*/
	virtual void Rename(const char *newFileName) override;

	/*!
	Sets a new file name. Static.
	\param[in] fileName The current name of the file.
	\param[in] newFileName The name to be associated with the current file.
	*/
	static void Rename(const char *fileName, const char *newFileName);

	/*!
	Checks if the file exists.
	\return TRUE if the file exists, FALSE otherwise.
	*/
	virtual bool Exist() override;

	/*!
	Checks if the file exists. Static.
	\param[in] fileName The name of the file.
	\return TRUE if the file exists, FALSE otherwise.
	*/
	static bool Exist(const char *fileName);

	/*!
	Checks if the file exists. Static. For TCHAR.
	\param[in] wFileName The name of the file.
	\return TRUE if the file exists, FALSE otherwise.
	*/
	static bool tExist(const TCHAR *tFileName);

	/*!
	Deletes the file.
	*/
	virtual void Delete() override;

	/*!
	Deletes the file. Static.
	\param[in] fileName The name of the file.
	*/
	static void Delete(const char *fileName);

	/*!
	Deletes the file. Static. For TCHAR.
	\param[in] fileName The name of the file.
	*/
	static void tDelete(const TCHAR *tFileName);

	/*!
	Returns the size of the file.
	\return The size of the file.
	*/
	virtual size_lt FileSize() override;

	/*!
	Returns the size of the file. Static.
	\param[in] hFile The handle of the opened file.
	\return The size of the file.
	*/
	static size_lt FileSize(HANDLE hFile);

	/*!
	Returns the size of the file. Static.
	\param[in] fileName The name of the file.
	\return The size of the file.
	*/
	static size_lt FileSize(const char *fileName);

	/*!
	Moves the file pointer of the specified file.
	\param[in] offset The offset of a new pointer position.
	\param[in] move The position used as a reference for the offset.
	\return A new pointer position.
	*/
	virtual size_lt Seek(size_lt offset, SeekReference move) override;

	/*!
	Reads one byte from the file.
	\return The value of the read byte or -1 if it can't be read (ex. EOF).
	*/
	virtual int ReadByte() override;

	/*!
	Reads a block from the file.
	\param[out] block The array of bytes from the file.
	\param[in] sizeBlock The number of bytes to be read.
	\return The number of the bytes read from the file.
	*/
	virtual size_lt ReadBlock(byte *block, size_lt blockSize = MIN_BUFFER_SIZE) override;

	/*!
	Reads a block from the file. Static.
	\param[in] hFile The handle of the opened file.
	\param[out] block The array of bytes from the file.
	\param[in] sizeBlock The number of bytes to be read.
	\return The number of the bytes read from the file.
	*/
	static size_lt ReadBlock(HANDLE hFile, byte *block, size_lt blockSize = MIN_BUFFER_SIZE);

	/*!
	Writes one byte into the file.
	\param[in] b The byte to be saved.
	*/
	virtual void WriteByte(byte b) override;

	/*!
	Writes a block into the file.
	\param[in] block The array of bytes to be written.
	\param[in] blockSize The number of bytes to be written.
	*/
	virtual void WriteBlock(byte *block, size_lt sizeBlock) override;

	/*!
	Writes a block into the file. Static.
	\param[in] hFile The handle of the opened file.
	\param[in] block The array of bytes to be written.
	\param[in] blockSize The number of bytes to be written.
	*/
	static void WriteBlock(HANDLE hFile, byte *block, size_lt sizeBlock);

	/////////////////////////////////////////////////////////////////////////////
	////////////////////           STATIC METHODS            ////////////////////
	/////////////////////////////////////////////////////////////////////////////

	/*!
	Reads the full file. Static.
	\param[in] fileName The name of the file to be read.
	\param[out] byteArr Data read from the file.
	\return The number of the bytes read.
	*/
	static size_lt ReadAllBytes(const char *fileName, byte **block);

	/*!
	Opens the file and writes all data into it. Static.
	\param[in] fileName The name of the file to be read.
	\param[in] data The data to be written into the file.
	\param[in] size The size of the data buffer.
	\param[in] mode Opens the file mode.
	*/
	static void WriteAllBytes(const char *fileName, byte* data, size_lt size, FileOpenMode mode = WRITENEWFILE);

	/*!
	\TODO
	Gets the latest file modified. Static.
	\param[in] string fileName The name of the file to be read.
	\return Info about the latest file modified.
	*/
	static FileMeta LastModified(const char *fileName);

private:
	HANDLE _hFile;			///< The handle of the opened file
	char *_fileName;		///< The name of the file
	WCHAR *_tFileName;		///< The name of the file in the unicode charset
	bool _opened;			///< Determines if the file is opened
};