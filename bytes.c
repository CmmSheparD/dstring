#include "bytes.h"

#include <stdlib.h>

#include "generic/generic.h"

DGENDEF(char,byte)

byte_str_t *byte_createFromRaw(const char *src)
{
        if (!src)
                return NULL;
        byte_str_t *n = malloc(sizeof(*n));
        n->len = 0;
        n->size = 1;
        _byte_reserve(n, strlen(src));
        strcpy(n->string, src);
        n->string[n->len] = '\0';
        return n;
}


int byte_appendRaw(byte_str_t *str, const char *s)
{
        if (!s)
                return -1;
        return byte_appendNRaw(str, s, strlen(s));
}

int byte_copyRaw(byte_str_t *str, const char *s)
{
        if (!s)
                return -1;
        return byte_copyNRaw(str, s, strlen(s));
}


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
