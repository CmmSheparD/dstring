#include "bytes.h"

DGENDEF(char,byte)

size_t byte_wideLength(const byte_str_t *str)
{
	if (!byte_isValid(str))
		return 0;
	return mbstowcs(NULL, str->string, 0) + 1;
}


size_t byte_toWide(const byte_str_t *str, wchar_t *dest, const size_t n)
{
	if (!byte_isValid(str) || !dest)
		return 0;
	return mbstowcs(dest, str->string, n);
}
