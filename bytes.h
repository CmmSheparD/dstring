#pragma once
/*
 * Concrete realization of generic string type.
 * byte_str_t - narrow charcter string type.
 */
#ifndef D_BYTES_H
#define D_BYTES_H

#include <wchar.h>

#include "generic/generic.h"

DGENDECL(char,byte)

/*
 * Get a size of a wide character string to store converted to wide character
 * dynamic string including a terminating null character.
 */
size_t byte_wideLength(const byte_str_t *str);

size_t byte_toWide(const byte_str_t *str, wchar_t *dest, const size_t n);

#endif  // D_BYTES_H
