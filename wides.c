#include "wides.h"

#include <stdlib.h>

#include "generic/generic.h"

DGENDEF(wchar_t,wide)

wide_str_t *wide_createFromRaw(const wchar_t *src)
{
        if (!src)
                return NULL;
        wide_str_t *n = malloc(sizeof(*n));
        n->len = 0;
        n->size = 1;
        _wide_reserve(n, wcslen(src));
        wcscpy(n->string, src);
        n->string[n->len] = '\0';
        return n;
}


int wide_appendRaw(wide_str_t *str, const wchar_t *s)
{
        if (!s)
                return -1;
        return wide_appendNRaw(str, s, wcslen(s));
}

int wide_copyRaw(wide_str_t *str, const wchar_t *s)
{
        if (!s)
                return -1;
        return wide_copyNRaw(str, s, wcslen(s));
}

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
