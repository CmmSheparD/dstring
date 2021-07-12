#pragma once
/*
 * Functions to convert byte_str_t to wide_str_t and vico versa.
 */
#ifndef D_CONVERT_H
#define D_CONVERT_H

#include "bytes.h"
#include "wides.h"

int byte_toWideStr(const byte_str_t *byte, wide_str_t *wide);

int wide_toByteStr(const wide_str_t *wide, byte_str_t *byte);

#endif // D_CONVERT_H
