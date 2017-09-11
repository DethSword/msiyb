#pragma once
#include <Windows.h>

/*!
Converts a char string into tchar.
\param[in] cStr The char string.
\param[out] tStr The tchar string.
*/
void ConvertCharToTCHAR(const char *cStr, TCHAR *tStr);

/*!
Converts a tchar string into char.
\param[in] tStr The tchar string.
\param[out] cStr The char string.
*/
void ConvertTCHARToChar(TCHAR *tStr, char *cStr);