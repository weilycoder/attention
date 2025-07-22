// filename:    bigint_header.h
// author:      baobaobear
// create date: 2021-02-19
// https://github.com/Baobaobear/MiniBigInteger

/*
MIT License

Copyright (c) 2021 Baobaobear

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BIGINT_HEADER_HPP
#define BIGINT_HEADER_HPP

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#if __cplusplus >= 201103L || _MSC_VER >= 1600

#include <cstdint>
#include <utility>
#define BIGINT_STD_MOVE std::move

#else
#ifdef _MSC_VER
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
#else
typedef unsigned long long uint64_t;
#if !defined(__linux__)
typedef long long int64_t;
#endif
#endif
typedef unsigned int uint32_t;
typedef int int32_t;
typedef unsigned short uint16_t;
typedef short int16_t;
#if !defined(__APPLE__)
typedef uint64_t uintmax_t;
typedef int64_t intmax_t;
#endif
#define BIGINT_STD_MOVE
#endif

#if defined(_WIN64) || defined(_M_X64)
#define BIGINT_X64 1
#else
#define BIGINT_X64 0
#endif

#if !defined(BIGINT_LARGE_BASE) && BIGINT_X64
#define BIGINT_LARGE_BASE 1 // only work with BigIntBase & BigIntDec
#endif

#define LESS_THAN_AND_EQUAL_COMPARABLE(T)                                                                    \
  bool operator>(const T &b) const { return b < *this; }                                                     \
  bool operator<=(const T &b) const { return !(b < *this); }                                                 \
  bool operator>=(const T &b) const { return !(*this < b); }                                                 \
  bool operator!=(const T &b) const { return !(*this == b); }

#endif // BIGINT_HEADER_HPP
