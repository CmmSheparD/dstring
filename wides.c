#include "wides.h"

DGENDEF(wchar_t,wide)

size_t wide_byteLength(const wide_str_t *str)
{
	if (!wide_isValid(str))
		return 0;
	return wcstombs(NULL, str->string, 0) + 1;
}


size_t wide_toByte(const wide_str_t *str, char *dest, const size_t n)
{
	if (!wide_isValid(str) || !dest)
		return 0;
	return wcstombs(dest, str->string, n);
}
