#pragma once
/*
 * Stores macross for creating custom dynamic string structures and funtions
 * to work with them.
 * DGENDECL(type,prefix) - generates definition for the struct and functions'
 * declarations.
 * DGENDEF(type,prefix) - generates declarations for the functions. Use only
 * in source files.
 */
#ifndef D_GENERIC_GENERIC_H
#define D_GENERIC_GENERIC_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define DGENDECL(type,prefix)                                                   \
typedef struct prefix##string {                                                 \
	type *string;                                                           \
	size_t len;                                                             \
	size_t size;                                                            \
} prefix##_str_t;                                                               \
                                                                                \
prefix##_str_t *prefix##_create();                                              \
void prefix##_free(prefix##_str_t *str);                                        \
                                                                                \
bool prefix##_isEmpty(const prefix##_str_t *str);                               \
                                                                                \
int prefix##_appendChar(prefix##_str_t *str, const type c);                     \
int prefix##_appendRaw(prefix##_str_t *str, const type *s, const size_t n);     \
int prefix##_copyRaw(prefix##_str_t *str, const type *s, const size_t n);       \
                                                                                \
int prefix##_appendStr(prefix##_str_t *dest, const prefix##_str_t *src);        \
int prefix##_copyStr(prefix##_str_t *dest, const prefix##_str_t *src);


#define DGENDEF(type,prefix)                                                    \
const size_t _##prefix##_CHUNK_SIZE = 128;                                      \
                                                                                \
size_t _##prefix##_spaceAvailable(const prefix##_str_t *str)                    \
{                                                                               \
        return str->size - str->len - 1;                                        \
}                                                                               \
                                                                                \
void _##prefix##_reserve(prefix##_str_t *str, const size_t n)                   \
{                                                                               \
        double ll = log2(str->len + n + 1);                                     \
        if (ll > log2(str->size)) {                                             \
                str->size = ceil(ll);                                           \
                str->string = realloc(str->string, str->size);                  \
        }                                                                       \
}                                                                               \
                                                                                \
void _##prefix##_trunc(prefix##_str_t *str)                                     \
{                                                                               \
        double lld = log2(str->size) - log2(str->len + 1);                      \
        if (lld >= 1) {                                                         \
                str->size = str->size / exp2(floor(lld));                       \
                str->string = realloc(str->string, str->size);                  \
        }                                                                       \
}                                                                               \
                                                                                \
                                                                                \
prefix##_str_t *##prefix##_create()                                             \
{                                                                               \
        prefix##_str_t *n = malloc(sizeof(*n));                                 \
        n->size = _##prefix##_CHUNK_SIZE;                                       \
        n->len = 0;                                                             \
        n->string = malloc(n->size * sizeof(*n->string));                       \
        n->string[0] = (type)0;                                                 \
        return n;                                                               \
}                                                                               \
                                                                                \
void prefix##_free(prefix##_str_t *str)                                         \
{                                                                               \
        if (str) {                                                              \
                if (str->string)                                                \
                        free(str->string);                                      \
                free(str);                                                      \
        }                                                                       \
}                                                                               \
                                                                                \
                                                                                \
bool prefix##_isValid(const prefix##_str_t *str)                                \
{                                                                               \
        return (str                                                             \
                && str->string                                                  \
                && str->len < str->size);                                       \
}                                                                               \
                                                                                \
bool prefix##_isEmpty(const prefix##_str_t *str)                                \
{                                                                               \
        if (prefix##_isValid(str))                                              \
                return str->len == 0;                                           \
        return true;                                                            \
}                                                                               \
                                                                                \
                                                                                \
int prefix##_appendChar(prefix##_str_t *str, const type c)                      \
{                                                                               \
        if (!prefix##_isValid(str))                                             \
                return -1;                                                      \
        if (_##prefix##_spaceAvailable(str) < 1)                                \
                _##prefix##_reserve(str, 1);                                    \
        str->string[str->len] = c;                                              \
        str->string[++str->len] = (type)0;                                      \
        return 0;                                                               \
}                                                                               \
                                                                                \
int prefix##_appendRaw(prefix##_str_t *str, const type *s, const size_t n)      \
{                                                                               \
        if (!prefix##_isValid(str))                                             \
                return -1;                                                      \
        if (_##prefix##_spaceAvailable(str) < n)                                \
                _##prefix##_reserve(str, n);                                    \
        memmove(&str->string[str->len], s, sizeof(*s) * n);                     \
        str->len += n;                                                          \
        str->string[str->len] = (type)0;                                        \
        return 0;                                                               \
}                                                                               \
                                                                                \
int prefix##_copyRaw(prefix##_str_t *str, const type *s, const size_t n)        \
{                                                                               \
        if (!prefix##_isValid(str))                                             \
                return -1;                                                      \
        if (str->size - 1 < n)                                                  \
                _##prefix##_reserve(str, n - str->size + 1);                    \
        memmove(str->string, s, sizeof(*s) * n);                                \
        str->len = n;                                                           \
        str->string[str->len] = (type)0;                                        \
        return 0;                                                               \
}                                                                               \
                                                                                \
                                                                                \
int prefix##_appendStr(prefix##_str_t *dest, const prefix##_str_t *src)         \
{                                                                               \
        if (!prefix##_isValid(dest) && !prefix##_isValid(src))                  \
                return -1;                                                      \
        if (_##prefix##_spaceAvailable(dest) < src->len)                        \
                _##prefix##_reserve(dest, src->len);                            \
        memmove(&dest->string[dest->len], src->string, sizeof(type) * src->len);\
        dest->len += src->len;                                                  \
        dest->string[dest->len] = (type)0;                                      \
        return 0;                                                               \
}                                                                               \
                                                                                \
int prefix##_copyStr(prefix##_str_t *dest, const prefix##_str_t *src)           \
{                                                                               \
        if (!prefix##_isValid(dest) && !prefix##_isValid(src))                  \
                return -1;                                                      \
        if (dest->size - 1 < src->len)                                          \
                _##prefix##_reserve(dest, src->len - dest->size + 1);           \
        memmove(dest->string, src->string, sizeof(type) * src->len);            \
        dest->len = src->len;                                                   \
        dest->string[dest->len] = (type)0;                                      \
        return 0;                                                               \
}

#endif	// D_GENERIC_GENERIC_H
