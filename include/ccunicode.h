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

    enum TCCUnicode_ErrorCode
    {
        CCUNICODE_NO_ERROR                  =  0,
        CCUNICODE_NULL_POINTER              = -1,
        CCUNICODE_INVALID_UTF8_CHARACTER    = -2,
        CCUNICODE_INVALID_UTF16_CHARACTER   = -3,
        CCUNICODE_STRING_ENDED_IN_CHARACTER = -4,
        CCUNICODE_INVALID_CODEPOINT         = -5,
        CCUNICODE_SURROGATE_PAIR_INVERSION  = -6,
        CCUNICODE_INVALID_ALLOCATOR         = -7,
        CCUNICODE_NULL_ALLOCATOR            = -8,
        CCUNICODE_BAD_ALLOCATION            = -9,
        CCUNICODE_OVERFLOW                  = -10,
        CCUNICODE_INVALID_PARAMETER         = -11,
        CCUNICODE_BUFFER_TOO_SMALL          = -12
    };

    typedef struct
    {
        void *(*malloc_func)(size_t);
        void (*free_func)(void*);
    } TCCUnicode_MallocPtr;

    int ccunicode_GetUtf8StrLen(const uint8_t *Utf8Str);
    int ccunicode_GetUtf16StrLen(const uint16_t *Utf16Str);
    int ccunicode_GetCodepointCount(const uint32_t *Codepoints);

    int ccunicode_CountCodepointsInUtf8(const uint8_t *Utf8Str);
    int ccunicode_CountCodepointsInUtf8_n(const uint8_t *Utf8Str, int Utf8Size);

    int ccunicode_CountCodepointsInUtf16(const uint16_t *Utf16Str);
    int ccunicode_CountCodepointsInUtf16_n(const uint16_t *Utf16Str, int Utf16Size);

    int ccunicode_GetUtf8SizeFromCodepoints(const uint32_t *Codepoints);
    int ccunicode_GetUtf8SizeFromCodepoints_n(const uint32_t *Codepoints, int CodepointCount);

    int ccunicode_GetUtf16SizeFromCodepoints(const uint32_t *Codepoints);
    int ccunicode_GetUtf16SizeFromCodepoints_n(const uint32_t *Codepoints, int CodepointCount);

#ifndef __CCUNICODE_NOSTDALLOC__
    int ccunicode_Utf8ToCodepoints(const uint8_t *Utf8Str, uint32_t **Codepoints);
    int ccunicode_Utf8ToCodepoints_n(const uint8_t *Utf8Str, int Utf8Size, uint32_t **Codepoints);
#endif
    int ccunicode_Utf8ToCodepoints_a(const uint8_t *Utf8Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToCodepoints_na(const uint8_t *Utf8Str, int Utf8Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf8ToCodepoints_m(const uint8_t *Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount);
    int ccunicode_Utf8ToCodepoints_nm(const uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount);

#ifndef __CCUNICODE_NOSTDALLOC__
    int ccunicode_Utf16ToCodepoints(const uint16_t *Utf16Str, uint32_t **Codepoints);
    int ccunicode_Utf16ToCodepoints_n(const uint16_t *Utf16Str, int Utf16Size, uint32_t **Codepoints);
#endif
    int ccunicode_Utf16ToCodepoints_a(const uint16_t *Utf16Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf16ToCodepoints_na(const uint16_t *Utf16Str, int Utf16Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf16ToCodepoints_m(const uint16_t *Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount);
    int ccunicode_Utf16ToCodepoints_nm(const uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount);

#ifndef __CCUNICODE_NOSTDALLOC__
    int ccunicode_CodepointsToUtf8(const uint32_t *Codepoints, uint8_t **Utf8Str);
    int ccunicode_CodepointsToUtf8_n(const uint32_t *Codepoints, int CodepointCount, uint8_t **Utf8Str);
#endif
    int ccunicode_CodepointsToUtf8_a(const uint32_t *Codepoints, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_CodepointsToUtf8_na(const uint32_t *Codepoints, int CodepointCount, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_CodepointsToUtf8_m(const uint32_t *Codepoints, uint8_t *Utf8Str, int Utf8Size);
    int ccunicode_CodepointsToUtf8_nm(const uint32_t *Codepoints, int CodepointCount, uint8_t *Utf8Str, int Utf8Size);

#ifndef __CCUNICODE_NOSTDALLOC__
    int ccunicode_CodepointsToUtf16(const uint32_t *Codepoints, uint16_t **Utf16Str);
    int ccunicode_CodepointsToUtf16_n(const uint32_t *Codepoints, int CodepointCount, uint16_t **Utf16Str);
#endif
    int ccunicode_CodepointsToUtf16_a(const uint32_t *Codepoints, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_CodepointsToUtf16_na(const uint32_t *Codepoints, int CodepointCount, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_CodepointsToUtf16_m(const uint32_t *Codepoints, uint16_t *Utf16Str, int Utf16Size);
    int ccunicode_CodepointsToUtf16_nm(const uint32_t *Codepoints, int CodepointCount, uint16_t *Utf16Str, int Utf16Size);

#ifndef __CCUNICODE_NOSTDALLOC__
    int ccunicode_Utf8ToUtf16(const uint8_t *Utf8Str, uint16_t **Utf16Str);
    int ccunicode_Utf8ToUtf16_n(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str);

    int ccunicode_Utf8ToUtf16_m(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size);
    int ccunicode_Utf8ToUtf16_nm(const uint8_t *Utf8Str, int Utf8Size, uint16_t *Utf16Str, int Utf16Size);

    int ccunicode_Utf8ToUtf16_l(const uint8_t *Utf8Str, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount);
    int ccunicode_Utf8ToUtf16_nl(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount);

    int ccunicode_Utf8ToUtf16_ml(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount);
#endif
    int ccunicode_Utf8ToUtf16_a(const uint8_t *Utf8Str, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToUtf16_na(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf8ToUtf16_ma(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToUtf16_nma(const uint8_t *Utf8Str, int Utf8Size, uint16_t *Utf16Str, int Utf16Size, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf8ToUtf16_la(const uint8_t *Utf8Str, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToUtf16_nla(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf8ToUtf16_mla(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf8ToUtf16_nml(const uint8_t *Utf8Str, int Utf8Size, uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount);

#ifndef __CCUNICODE_NOSTDALLOC__
    int ccunicode_Utf16ToUtf8(const uint16_t *Utf16Str, uint8_t **Utf8Str);
    int ccunicode_Utf16ToUtf8_n(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str);

    int ccunicode_Utf16ToUtf8_m(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size);
    int ccunicode_Utf16ToUtf8_nm(const uint16_t *Utf16Str, int Utf16Size, uint8_t *Utf8Str, int Utf8Size);

    int ccunicode_Utf16ToUtf8_l(const uint16_t *Utf16Str, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount);
    int ccunicode_Utf16ToUtf8_nl(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount);

    int ccunicode_Utf16ToUtf8_ml(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount);
#endif
    int ccunicode_Utf16ToUtf8_a(const uint16_t *Utf16Str, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf16ToUtf8_na(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf16ToUtf8_ma(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf16ToUtf8_nma(const uint16_t *Utf16Str, int Utf16Size, uint8_t *Utf8Str, int Utf8Size, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf16ToUtf8_la(const uint16_t *Utf16Str, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf16ToUtf8_nla(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);

    int ccunicode_Utf16ToUtf8_mla(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr);
    int ccunicode_Utf16ToUtf8_nml(const uint16_t *Utf16Str, int Utf16Size, uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount);

#   ifdef __CCUNICODE_IMPL__
#   include "ccunicode_impl.h"
#   endif

#ifdef __cplusplus
}
#endif

#endif // __CCUNICODE_HEADER__
