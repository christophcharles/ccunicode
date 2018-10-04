// MIT License
//
// Copyright (c) 2018 Christoph Charles
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __CCUNICODE_HEADER__
#define __CCUNICODE_HEADER__

#ifdef __cplusplus
#   include <cstddef>
#   include <cstdint>
#else
#   include <stddef.h>
#   include <stdint.h>
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        void *(*malloc_func)(size_t);
        void (*free_func)(void*);
    } TCCUnicode_MallocPtr;

    int ccunicode_Utf8ToCodepoints(const uint8_t *Utf8Str, uint32_t **Codepoints);
    int ccunicode_Utf8ToCodepoints_n(const uint8_t *Utf8Str, size_t Utf8Size, uint32_t **Codepoints);
    int ccunicode_Utf8ToCodepoints_m(const uint8_t *Utf8Str, uint32_t *Codepoints, size_t MaxCodepointsCount);
    int ccunicode_Utf8ToCodepoints_nm(const uint8_t *Utf8Str, size_t Utf8Size, uint32_t *Codepoints, size_t MaxCodepointsCount);

    int ccunicode_Utf8ToCodepoints_a(const uint8_t *Utf8Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToCodepoints_na(const uint8_t *Utf8Str, size_t Utf8Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToCodepoints_ma(const uint8_t *Utf8Str, uint32_t *Codepoints, size_t MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToCodepoints_nma(const uint8_t *Utf8Str, size_t Utf8Size, uint32_t *Codepoints, size_t MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);

#   ifdef __CCUNICODE_IMPL__
#   include "ccunicode_impl.h"
#   endif

#ifdef __cplusplus
}
#endif

#endif // __CCUNICODE_HEADER__
