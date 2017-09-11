/*!
\file allocator.h "server\desktop\src\common\allocator.h"
\authors Alexandr Barulev
\copyright © MSiYB 2017
\license GPL license
\version 0.1
\date 07 March 2017
*/

#pragma once
#include "../defines.h"
#include "../tools/exception.h"
#include <string>

using std::string;

/*!
Reallocates memory for a char string array.
\param[out] arrayStrings The allocated block for a string array.
\param[in] oldSize The current array size.
\param[in] rCoeff The new size will be calculated by multiplying rCoef and oldSize.
*/
void ResizeStringArray(char ***arrayStrings, size_lt *oldSize, int rCoeff);

/*!
Reallocates memory for a char string.
\param[out] string The allocated block for a string.
\param[in] oldSize The current string size.
\param[in] rCoeff The new size will be calculated by multiplying rCoef and oldSize.
*/
void ResizeString(char **string, size_lt *oldSize, int rCoeff);

/*!
Reallocates memory for a char string with the constant size.
\param[out] arrayStrings The allocated block for a string.
\param[in] oldSize The current string size.
\param[in] newSize The new string size.
*/
void Resize(char **string, size_lt *oldSize, size_lt newSize);

/*!
Converts a char string array into a byte array.
\param[out] byteArr The array of byte.
\param[in] str The char string array to be converted.
\param[in] cnt The amount of strings in the array.
\return The number of bytes in the byte array.
*/
size_lt ConvertCharStringArrayToByte(byte** byteArr, char **str, size_lt cnt);

/*!
Converts a string array into a byte array.
\param[out] byteArr The byte array.
\param[in] str The string array to be converted.
\param[in] cnt The number of strings in the array.
\return The number of bytes in the byte array.
*/
size_lt ConvertStringArrayToByte(byte** byteArr, string *str, size_lt cnt);