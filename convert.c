#include "convert.h"

#include <stdlib.h>

void _byte_reserve(byte_str_t *str, const size_t n);
void _wide_reserve(wide_str_t *str, const size_t n);


int byte_toWideStr(const byte_str_t *byte, wide_str_t *wide)
{
	if (!byte_isValid(byte) || !wide_isValid(wide))
		return -1;
        _wide_reserve(wide, byte->len - wide->len + 1);
	wide->len = byte_wideLength(byte) - 1;
	mbstowcs(wide->string, byte->string, wide->len);
	wide->string[wide->len] = L'\0';
	return 0;
}

int wide_toByteStr(const wide_str_t *wide, byte_str_t *byte)
{
	if (!wide_isValid(wide) || !byte_isValid(byte))
		return -1;
	_byte_reserve(byte, wide->len - byte->len + 1);
	byte->len = wide_byteLength(wide) - 1;
	wcstombs(byte->string, wide->string, byte->len);
	byte->string[byte->len] = '\0';
	return 0;
}
