#pragma once
/*
 * Concrete realization of generic string type.
 * wide_str_t - wide character string type.
 */
#ifndef D_WIDES_H
#define D_WIDES_H

#include <wchar.h>

#include "generic/generic.h"

DGENDECL(wchar_t,wide)

wide_str_t *wide_createFromRaw(const wchar_t *src);

int wide_appendRaw(wide_str_t *str, const wchar_t *s);
int wide_copyRaw(wide_str_t *str, const wchar_t *s);

/*
 * Get a size of a character string to store converted to multibyte
 * dynamic string including a terminating null character.
 */
size_t wide_byteLength(const wide_str_t *str);

size_t wide_toByte(const wide_str_t *str, char *dest, const size_t n);

#endif  // D_WIDES_H
