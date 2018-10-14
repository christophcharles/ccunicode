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

    /// \brief Possible error codes returned by the various ccunicode functions
    enum TCCUnicode_ErrorCode
    {
        CCUNICODE_NO_ERROR                  =  0,   ///< No error (positive values also indicate no error)
        CCUNICODE_NULL_POINTER              = -1,   ///< A NULL-pointer was given either as source or destination
        CCUNICODE_INVALID_UTF8_CHARACTER    = -2,   ///< Conversion had to stop: invalid UTF8 character found
        CCUNICODE_INVALID_UTF16_CHARACTER   = -3,   ///< Conversion had to stop: invalid UTF16 character found
        CCUNICODE_STRING_ENDED_IN_CHARACTER = -4,   ///< Conversion had to stop: the string ends in a multiple codeunits character
        CCUNICODE_INVALID_CODEPOINT         = -5,   ///< Conversion had to stop: invalid codepoint
        CCUNICODE_SURROGATE_PAIR_INVERSION  = -6,   ///< Conversion had to stop: a second codeunit from a surrogate pair was found without the first one
        CCUNICODE_INVALID_ALLOCATOR         = -7,   ///< The pointer to malloc or free is invalid
        CCUNICODE_NULL_ALLOCATOR            = -8,   ///< NULL pointer given for Allocator but ccunicode is compiled without standard alloc support
        CCUNICODE_BAD_ALLOCATION            = -9,   ///< Error while allocating memory
        CCUNICODE_OVERFLOW                  = -10,  ///< Integer overflow
        CCUNICODE_INVALID_PARAMETER         = -11,  ///< Invalid parameter (usually negative sizes)
        CCUNICODE_BUFFER_TOO_SMALL          = -12   ///< Temporary or destination buffer too small to hold the result
    };

    /// \brief Allocator structure to hold pointers to user-defined malloc and free
    typedef struct
    {
        void *(*malloc_func)(size_t); ///< Pointer to a user-defined malloc function
        void (*free_func)(void*);     ///< Pointer to a user-defined free function
    } TCCUnicode_MallocPtr;

    /// \brief Utility function: counts the number of bytes in a UTF8 string until the terminal '\0'
    ///
    /// This functions works similarly to strlen. It is here to avoid using the standard library.
    ///
    /// \param Utf8Str pointer to a UTF-8 encoded string
    /// \return the number of bytes (codeunits not characters) in the string, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetUtf8StrLen(const uint8_t *Utf8Str);

    /// \brief Utility function: counts the number of shorts in a UTF16 string until the terminal '\0'
    ///
    /// This functions works similarly to strlen. It is here to avoid using the standard library.
    ///
    /// \param Utf16Str pointer to a UTF-16 encoded string
    /// \return the number of shorts (codeunits not characters) in the string, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetUtf16StrLen(const uint16_t *Utf16Str);

    /// \brief Utility function: counts the number of codepoints in null-terminated list of codepoints.
    ///
    /// This functions works similarly to strlen. It is here to avoid using the standard library.
    ///
    /// \param Codepoints pointer to a null-terminated array of codepoints
    /// \return the number of codepoints in the array, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetCodepointCount(const uint32_t *Codepoints);

    /// \brief Utility function: counts the number of codepoints in a null-terminated UTF8 string
    ///
    /// This version stops at the final null byte.
    ///
    /// \param Utf8Str pointer to a null-terminated utf8 string
    /// \return the number of codepoints in the string, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_CountCodepointsInUtf8(const uint8_t *Utf8Str);

    /// \brief Utility function: counts the number of codepoints in a null-terminated UTF8 string
    ///
    /// This version stops either at the final null byte or if Utf8Size is reached.
    ///
    /// \param Utf8Str pointer to a null-terminated utf8 string
    /// \param Utf8Size maximum number of bytes to explore
    /// \return the number of codepoints in the string, excluding the final '\0' if reached. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_CountCodepointsInUtf8_n(const uint8_t *Utf8Str, int Utf8Size);

    /// \brief Utility function: counts the number of codepoints in a null-terminated UTF16 string
    ///
    /// This version stops at the final null byte.
    ///
    /// \param Utf16Str pointer to a null-terminated utf16 string
    /// \return the number of codepoints in the string, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_CountCodepointsInUtf16(const uint16_t *Utf16Str);

    /// \brief Utility function: counts the number of codepoints in a null-terminated UTF16 string
    ///
    /// This version stops either at the final null byte or if Utf16Size is reached.
    ///
    /// \param Utf16Str pointer to a null-terminated utf16 string
    /// \param Utf16Size maximum number of shorts to explore
    /// \return the number of codepoints in the string, excluding the final '\0' if reached. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_CountCodepointsInUtf16_n(const uint16_t *Utf16Str, int Utf16Size);

    /// \brief Utility function: compute the number of bytes needed (excluding final '\0') to store an array of codepoints as UTF8
    ///
    /// This version stops at the final null codepoint.
    ///
    /// \param Codepoints pointer to a null-terminated array of codepoints.
    /// \return the number of bytes needed to encode as UTF8, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetUtf8SizeFromCodepoints(const uint32_t *Codepoints);

    /// \brief Utility function: compute the number of bytes needed (excluding final '\0') to store an array of codepoints as UTF8
    ///
    /// This version stops either at the final null codepoint or if CodepointCount codepoints havec been processed.
    ///
    /// \param Codepoints pointer to a null-terminated array of codepoints.
    /// \param CodepointCount Maximum number of codepoint to consider.
    /// \return the number of bytes needed to encode as UTF8, excluding the final '\0' if reached. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetUtf8SizeFromCodepoints_n(const uint32_t *Codepoints, int CodepointCount);

    /// \brief Utility function: compute the number of shorts needed (excluding final '\0') to store an array of codepoints as UTF16
    ///
    /// This version stops at the final null codepoint.
    ///
    /// \param Codepoints pointer to a null-terminated array of codepoints.
    /// \return the number of shorts needed to encode as UTF16, excluding the final '\0'. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetUtf16SizeFromCodepoints(const uint32_t *Codepoints);

    /// \brief Utility function: compute the number of shorts needed (excluding final '\0') to store an array of codepoints as UTF16
    ///
    /// This version stops either at the final null codepoint or if CodepointCount codepoints havec been processed.
    ///
    /// \param Codepoints pointer to a null-terminated array of codepoints.
    /// \param CodepointCount Maximum number of codepoint to consider.
    /// \return the number of shorts needed to encode as UTF16, excluding the final '\0' if reached. The empty string returns 0 for instance.
    ///         On error, return a negative number corresponding to a TCCUnicode_ErrorCode
    int ccunicode_GetUtf16SizeFromCodepoints_n(const uint32_t *Codepoints, int CodepointCount);

#ifndef __CCUNICODE_NOSTDALLOC__
    /// \brief Converts an UTF8 string to a null-terminated array of codepoints
    ///
    /// This version has no suffix. This means memory is allocated dynamically using the standard library,
    /// and the UTF8-string must be null-terminated.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf8Str Pointer to a null-terminated UTF8 string to convert
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf8ToCodepoints(const uint8_t *Utf8Str, uint32_t **Codepoints);

    /// \brief Converts an UTF8 string to a null-terminated array of codepoints
    ///
    /// This version has an n suffix. This means memory is allocated dynamically using the standard library,
    /// but a maximum length is given for the UTF8-string. Conversion is persued as long as this length
    /// is not reached or a null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf8Str Pointer to a null-terminated UTF8 string to convert
    /// \param Utf8Size Maximum size to explore in the previous UTF8 string in bytes.
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf8ToCodepoints_n(const uint8_t *Utf8Str, int Utf8Size, uint32_t **Codepoints);
#endif
    /// \brief Converts an UTF8 string to a null-terminated array of codepoints
    ///
    /// This version has an a suffix. This means memory is allocated dynamically using user defined functions,
    /// but no maximum length is given for the UTF8-string. Conversion is persued as long as no null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf8Str Pointer to a null-terminated UTF8 string to convert
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \param AllocPtr Pointer to a TCCUnicode_MallocPtr struct or NULL to use the standard library (if __CCUNICODE_NOSTDALLOC__ is not defined)
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf8ToCodepoints_a(const uint8_t *Utf8Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);

    /// \brief Converts an UTF8 string to a null-terminated array of codepoints
    ///
    /// This version has an na suffix. This means memory is allocated dynamically using user defined functions,
    /// and a maximum length is given for the UTF8-string. Conversion is persued as long as this length
    /// is not reached or a null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf8Str Pointer to a null-terminated UTF8 string to convert
    /// \param Utf8Size Maximum size to explore in the previous UTF8 string in bytes.
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \param AllocPtr Pointer to a TCCUnicode_MallocPtr struct or NULL to use the standard library (if __CCUNICODE_NOSTDALLOC__ is not defined)
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf8ToCodepoints_na(const uint8_t *Utf8Str, int Utf8Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);

    /// \brief Converts an UTF8 string to a null-terminated array of codepoints
    ///
    /// This version has an m suffix. This means the output is sent into a preallocated buffer,
    /// And no maximum length is given for the UTF8-string. Conversion is persued no null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf8Str Pointer to a null-terminated UTF8 string to convert
    /// \param Codepoints Pointer to a buffer that will hold the codepoints
    /// \param MaxCodepointsCount Maximum number of codepoints the previous buffer can hold not counting the final null codepoint.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf8ToCodepoints_m(const uint8_t *Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount);

    /// \brief Converts an UTF8 string to a null-terminated array of codepoints
    ///
    /// This version has an nm suffix. This means the output is sent into a preallocated buffer,
    /// and a maximum length is given for the UTF8-string. Conversion is persued until either a null character is encountered,
    /// or the maximum length has been reached.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf8Str Pointer to a null-terminated UTF8 string to convert
    /// \param Utf8Size Maximum number of bytes to read from the Utf8 string.
    /// \param Codepoints Pointer to a buffer that will hold the codepoints
    /// \param MaxCodepointsCount Maximum number of codepoints the previous buffer can hold not counting the final null codepoint.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf8ToCodepoints_nm(const uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount);

#ifndef __CCUNICODE_NOSTDALLOC__
    /// \brief Converts an UTF16 string to a null-terminated array of codepoints
    ///
    /// This version has no suffix. This means memory is allocated dynamically using the standard library,
    /// and the UTF16-string must be null-terminated.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf16Str Pointer to a null-terminated UTF16 string to convert
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf16ToCodepoints(const uint16_t *Utf16Str, uint32_t **Codepoints);

    /// \brief Converts an UTF16 string to a null-terminated array of codepoints
    ///
    /// This version has an n suffix. This means memory is allocated dynamically using the standard library,
    /// but a maximum length is given for the UTF16-string. Conversion is persued as long as this length
    /// is not reached or a null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf16Str Pointer to a null-terminated UTF16 string to convert
    /// \param Utf16Size Maximum size to explore in the previous UTF16 string in shorts.
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf16ToCodepoints_n(const uint16_t *Utf16Str, int Utf16Size, uint32_t **Codepoints);
#endif
    /// \brief Converts an UTF16 string to a null-terminated array of codepoints
    ///
    /// This version has an a suffix. This means memory is allocated dynamically using user defined functions,
    /// but no maximum length is given for the UTF16-string. Conversion is persued as long as no null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf16Str Pointer to a null-terminated UTF16 string to convert
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \param AllocPtr Pointer to a TCCUnicode_MallocPtr struct or NULL to use the standard library (if __CCUNICODE_NOSTDALLOC__ is not defined)
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf16ToCodepoints_a(const uint16_t *Utf16Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);

    /// \brief Converts an UTF16 string to a null-terminated array of codepoints
    ///
    /// This version has an na suffix. This means memory is allocated dynamically using user defined functions,
    /// and a maximum length is given for the UTF16-string. Conversion is persued as long as this length
    /// is not reached or a null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf16Str Pointer to a null-terminated UTF16 string to convert
    /// \param Utf16Size Maximum size to explore in the previous UTF16 string in shorts.
    /// \param Codepoints Pointer to a pointer that will hold the address of the resulting array. The user is responsible for freeing the memory.
    /// \param AllocPtr Pointer to a TCCUnicode_MallocPtr struct or NULL to use the standard library (if __CCUNICODE_NOSTDALLOC__ is not defined)
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf16ToCodepoints_na(const uint16_t *Utf16Str, int Utf16Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr);

    /// \brief Converts an UTF16 string to a null-terminated array of codepoints
    ///
    /// This version has an m suffix. This means the output is sent into a preallocated buffer,
    /// And no maximum length is given for the UTF16-string. Conversion is persued no null character is encountered.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf16Str Pointer to a null-terminated UTF16 string to convert
    /// \param Codepoints Pointer to a buffer that will hold the codepoints
    /// \param MaxCodepointsCount Maximum number of codepoints the previous buffer can hold not counting the final null codepoint.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
    int ccunicode_Utf16ToCodepoints_m(const uint16_t *Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount);

    /// \brief Converts an UTF16 string to a null-terminated array of codepoints
    ///
    /// This version has an nm suffix. This means the output is sent into a preallocated buffer,
    /// and a maximum length is given for the UTF16-string. Conversion is persued until either a null character is encountered,
    /// or the maximum length has been reached.
    ///
    /// Generally the following suffixes are possible:
    /// n: a maximum length for the source string is given
    /// m: a maximum length for the output buffer is given
    /// l: a temporary buffer and its size are given to avoid internal allocation (when applicable)
    /// a: a TCCUnicode_MallocPtr struct is provided to enable user-defined allocation strategies.
    /// Lengths never include the final null character and so buffer should have 1 more byte, short or int available.
    ///
    /// \param Utf16Str Pointer to a null-terminated UTF16 string to convert
    /// \param Utf16Size Maximum number of shorts to read from the Utf16 string.
    /// \param Codepoints Pointer to a buffer that will hold the codepoints
    /// \param MaxCodepointsCount Maximum number of codepoints the previous buffer can hold not counting the final null codepoint.
    /// \return The number of codepoints outputed (except for the final 0) or a negative number on error.
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
#include <limits.h>

#define CCUNICODE_INTERNAL_TEST(t) \
    { \
        int Res = t; \
        if (Res) \
            return Res; \
    }

#ifndef __CCUNICODE_NOSTDALLOC__

#include <stdlib.h>

static const TCCUnicode_MallocPtr ccunicode_DefaultAllocator =
{
    &malloc,
    &free
};

#endif // __CCUNICODE_NOSTDALLOC__

static int ccunicode_CheckAllocator(const TCCUnicode_MallocPtr **AllocPtr)
{
    if (!(*AllocPtr))
    {
#ifndef __CCUNICODE_NOSTDALLOC__
        *AllocPtr = &ccunicode_DefaultAllocator;
#else
        return CCUNICODE_NULL_ALLOCATOR;
#endif
    }

    if (!(*AllocPtr)->malloc_func || !(*AllocPtr)->free_func)
        return CCUNICODE_INVALID_ALLOCATOR;

    return CCUNICODE_NO_ERROR;
}

int ccunicode_GetUtf8StrLen(const uint8_t *Utf8Str)
{
    if (!Utf8Str)
        return CCUNICODE_NULL_POINTER;

    int Len = 0;
    while (Utf8Str[Len] != 0)
    {
        if (Len == INT_MAX)
            return CCUNICODE_OVERFLOW;
        ++Len;
    }
    return Len;
}

int ccunicode_GetUtf16StrLen(const uint16_t *Utf16Str)
{
    if (!Utf16Str)
        return CCUNICODE_NULL_POINTER;

    int Len = 0;
    while (Utf16Str[Len] != 0)
    {
        if (Len == INT_MAX)
            return CCUNICODE_OVERFLOW;
        ++Len;
    }
    return Len;
}

int ccunicode_GetCodepointCount(const uint32_t *Codepoints)
{
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;

    int Len = 0;
    while (Codepoints[Len] != 0)
    {
        if (Len == INT_MAX)
            return CCUNICODE_OVERFLOW;
        ++Len;
    }
    return Len;
}

int ccunicode_CountCodepointsInUtf8(const uint8_t *Utf8Str)
{
    int Res = ccunicode_GetUtf8StrLen(Utf8Str);
    if (Res < 0)
        return Res;

    return ccunicode_CountCodepointsInUtf8_n(Utf8Str, Res);
}

int ccunicode_CountCodepointsInUtf8_n(const uint8_t *Utf8Str, int Utf8Size)
{
    if (!Utf8Str)
        return CCUNICODE_NULL_POINTER;
    if (Utf8Size < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (!Utf8Size)
        return 0;

    int Count = 0;
    int RemainingBytes = 0;
    for (int Pos = 0; Pos < Utf8Size; ++Pos)
    {
        uint8_t CurrentByte = Utf8Str[Pos];

        // If the code is 0 then we have reached the end of the string
        if (CurrentByte == 0x00)
            return Count;

        // The first byte encoding a code point must either be ASCII (< 0x80)
        // or it must carry the correct starting bitmask for the length info.
        // In practice, the following range are forbidden:
        // 0x80-0xBF
        // 0xF8-0xFF
        if (CurrentByte >= 0x80 && CurrentByte <= 0xBF)
            return CCUNICODE_INVALID_UTF8_CHARACTER;
        if (CurrentByte >= 0xF8 /* && CurrentByte <= 0xFF */)
            return CCUNICODE_INVALID_UTF8_CHARACTER;

        if (Count == INT_MAX)
            return CCUNICODE_OVERFLOW;
        ++Count;

        if (CurrentByte >= 0x01 && CurrentByte <= 0x7F)
        {
            RemainingBytes = 0;
        }

        if (CurrentByte >= 0xC0 && CurrentByte <= 0xDF)
        {
            RemainingBytes = 1;
        }

        if (CurrentByte >= 0xE0 && CurrentByte <= 0xEF)
        {
            RemainingBytes = 2;
        }

        if (CurrentByte >= 0xF0 && CurrentByte <= 0xF7)
        {
            RemainingBytes = 3;
        }

        // We check we are allowed that many bytes for the codepoint
        if (Pos + RemainingBytes >= Utf8Size)
            return CCUNICODE_STRING_ENDED_IN_CHARACTER;

        // Now collect remaining part of the codepoint (if any)
        for (size_t j = 0; j < RemainingBytes; ++j)
        {
            CurrentByte = Utf8Str[++Pos];

            if (CurrentByte == 0)
                return CCUNICODE_STRING_ENDED_IN_CHARACTER;
            // The only valid range is 0x80-0xDF for an extension
            if (CurrentByte < 0x80 || CurrentByte > 0xDF)
                return CCUNICODE_INVALID_UTF8_CHARACTER;
        }
    }

    return Count;
}

int ccunicode_CountCodepointsInUtf16(const uint16_t *Utf16Str)
{
    int Res = ccunicode_GetUtf16StrLen(Utf16Str);
    if (Res < 0)
        return Res;

    return ccunicode_CountCodepointsInUtf16_n(Utf16Str, Res);
}

int ccunicode_CountCodepointsInUtf16_n(const uint16_t *Utf16Str, int Utf16Size)
{
    if (!Utf16Str)
        return CCUNICODE_NULL_POINTER;
    if (Utf16Size < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (!Utf16Size)
        return 0;

    int Count = 0;
    int RemainingBytes = 0;
    for (int Pos = 0; Pos < Utf16Size; ++Pos)
    {
        uint16_t CurrentCodeUnit = Utf16Str[Pos];

        // We must distinguish between surrogate pairs and single units
        if (CurrentCodeUnit >= 0xD800 && CurrentCodeUnit <= 0xDFFF)
        {
            if (CurrentCodeUnit >= 0xDC00)
                return CCUNICODE_SURROGATE_PAIR_INVERSION;

            if (Pos == Utf16Size-1)
                return CCUNICODE_STRING_ENDED_IN_CHARACTER;

            CurrentCodeUnit = Utf16Str[++Pos];
            if (CurrentCodeUnit == 0)
                return CCUNICODE_STRING_ENDED_IN_CHARACTER;
            if (CurrentCodeUnit < 0xDC00 || CurrentCodeUnit > 0xDFFF)
                return CCUNICODE_INVALID_UTF16_CHARACTER;

            if (Count == INT_MAX)
                return CCUNICODE_OVERFLOW;
            ++Count;
        }
        else
        {
            if (CurrentCodeUnit == 0)
                return Count;

            if (Count == INT_MAX)
                return CCUNICODE_OVERFLOW;
            ++Count;
        }
    }

    return Count;
}

int ccunicode_GetUtf8SizeFromCodepoints(const uint32_t *Codepoints)
{
    int Res = ccunicode_GetCodepointCount(Codepoints);
    if (Res < 0)
        return Res;

    return ccunicode_GetUtf8SizeFromCodepoints_n(Codepoints, Res);
}

int ccunicode_GetUtf8SizeFromCodepoints_n(const uint32_t *Codepoints, int CodepointCount)
{
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;
    if (CodepointCount < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (!CodepointCount)
        return 0;

    int Utf8Size = 0;
    for (int Pos = 0; Pos < CodepointCount; ++Pos)
    {
        uint32_t CurrentCodepoint = Codepoints[Pos];

        if (CurrentCodepoint > 0x10FFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint >= 0xD800 && CurrentCodepoint <= 0xDFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint == 0)
            return Utf8Size;

        if (CurrentCodepoint >= 1 && CurrentCodepoint <= 0x7F)
        {
            if (Utf8Size == INT_MAX)
                return CCUNICODE_OVERFLOW;
            Utf8Size += 1;
        }
        if (CurrentCodepoint >= 0x80 && CurrentCodepoint <= 0x7FF)
        {
            if (Utf8Size > INT_MAX-2)
                return CCUNICODE_OVERFLOW;
            Utf8Size += 2;
        }
        if (CurrentCodepoint >= 0x800 && CurrentCodepoint <= 0xFFFF)
        {
            if (Utf8Size > INT_MAX-3)
                return CCUNICODE_OVERFLOW;
            Utf8Size += 3;
        }
        if (CurrentCodepoint >= 0x1000 && CurrentCodepoint <= 0x10FFFF)
        {
            if (Utf8Size > INT_MAX-4)
                return CCUNICODE_OVERFLOW;
            Utf8Size += 4;
        }
    }

    return Utf8Size;
}

int ccunicode_GetUtf16SizeFromCodepoints(const uint32_t *Codepoints)
{
    int Res = ccunicode_GetCodepointCount(Codepoints);
    if (Res < 0)
        return Res;

    return ccunicode_GetUtf16SizeFromCodepoints_n(Codepoints, Res);
}

int ccunicode_GetUtf16SizeFromCodepoints_n(const uint32_t *Codepoints, int CodepointCount)
{
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;
    if (CodepointCount < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (!CodepointCount)
        return 0;

    int Utf16Size = 0;
    for (int Pos = 0; Pos < CodepointCount; ++Pos)
    {
        uint32_t CurrentCodepoint = Codepoints[Pos];

        if (CurrentCodepoint > 0x10FFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint >= 0xD800 && CurrentCodepoint <= 0xDFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint == 0)
            return Utf16Size;

        if (CurrentCodepoint >= 1 && CurrentCodepoint <= 0xD7FF)
        {
            if (Utf16Size == INT_MAX)
                return CCUNICODE_OVERFLOW;
            Utf16Size += 1;
        }
        if (CurrentCodepoint >= 0xE000 && CurrentCodepoint <= 0xFFFF)
        {
            if (Utf16Size == INT_MAX)
                return CCUNICODE_OVERFLOW;
            Utf16Size += 1;
        }

        if (CurrentCodepoint >= 0x10000 && CurrentCodepoint <= 0x10FFFF)
        {
            if (Utf16Size > INT_MAX-2)
                return CCUNICODE_OVERFLOW;
            Utf16Size += 2;
        }
    }

    return Utf16Size;
}

#ifndef __CCUNICODE_NOSTDALLOC__
int ccunicode_Utf8ToCodepoints(const uint8_t *Utf8Str, uint32_t **Codepoints)
{
    return ccunicode_Utf8ToCodepoints_a(Utf8Str, Codepoints, NULL);
}

int ccunicode_Utf8ToCodepoints_n(const uint8_t *Utf8Str, int Utf8Size, uint32_t **Codepoints)
{
    return ccunicode_Utf8ToCodepoints_na(Utf8Str, Utf8Size, Codepoints, NULL);
}
#endif

int ccunicode_Utf8ToCodepoints_a(const uint8_t *Utf8Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Utf8Size = ccunicode_GetUtf8StrLen(Utf8Str);
    if (Utf8Size < 0)
        return Utf8Size;

    return ccunicode_Utf8ToCodepoints_na(Utf8Str, Utf8Size, Codepoints, AllocPtr);
}

int ccunicode_Utf8ToCodepoints_na(const uint8_t *Utf8Str, int Utf8Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;

    int CodepointCount = ccunicode_CountCodepointsInUtf8_n(Utf8Str, Utf8Size);
    if (CodepointCount < 0)
        return CodepointCount;
    if (CodepointCount == INT_MAX)
        return CCUNICODE_OVERFLOW;

    if (CodepointCount+1 > INT_MAX/sizeof(**Codepoints))
        return CCUNICODE_OVERFLOW;
    *Codepoints = AllocPtr->malloc_func((CodepointCount+1)*sizeof(**Codepoints));
    if (!(*Codepoints))
        return CCUNICODE_BAD_ALLOCATION;

    int Result = ccunicode_Utf8ToCodepoints_nm(Utf8Str, Utf8Size, *Codepoints, CodepointCount);
    if (Result < 0)
    {
        AllocPtr->free_func(*Codepoints);
        *Codepoints = NULL;
    }
    return Result;
}

int ccunicode_Utf8ToCodepoints_m(const uint8_t *Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount)
{
    int Utf8Size = ccunicode_GetUtf8StrLen(Utf8Str);
    if (Utf8Size < 0)
        return Utf8Size;

    return ccunicode_Utf8ToCodepoints_nm(Utf8Str, Utf8Size, Codepoints, MaxCodepointsCount);
}

int ccunicode_Utf8ToCodepoints_nm(const uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount)
{
    if (!Utf8Str)
        return CCUNICODE_NULL_POINTER;
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;
    if (Utf8Size < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (MaxCodepointsCount < 0)
        return CCUNICODE_INVALID_PARAMETER;

    int WritePos = 0;
    int ReadPos = 0;
    while ((ReadPos < Utf8Size) && (WritePos < MaxCodepointsCount))
    {
        uint32_t CodePoint = 0;

        int RemainingBytes = 0;
        if (ReadPos == INT_MAX)
            return CCUNICODE_OVERFLOW;
        uint8_t CurrentByte = Utf8Str[ReadPos++];

        // If it is the final character let's stop there
        if (CurrentByte == 0)
        {
            Codepoints[WritePos] = 0;
            return WritePos;
        }

        // If we have an illegal character, we stop
        if (CurrentByte >= 0x80 && CurrentByte <= 0xBF)
            return CCUNICODE_INVALID_UTF8_CHARACTER;
        if (CurrentByte >= 0xF8 /* && CurrentByte <= 0xFF */)
            return CCUNICODE_INVALID_UTF8_CHARACTER;

        if (CurrentByte >= 0x01 && CurrentByte <= 0x7F)
        {
            CodePoint = CurrentByte;
            RemainingBytes = 0;
        }

        if (CurrentByte >= 0xC0 && CurrentByte <= 0xDF)
        {
            CodePoint = (uint32_t)(CurrentByte & 0x1F);
            RemainingBytes = 1;
        }

        if (CurrentByte >= 0xE0 && CurrentByte <= 0xEF)
        {
            CodePoint = (uint32_t)(CurrentByte & 0xF);
            RemainingBytes = 2;
        }

        if (CurrentByte >= 0xF0 && CurrentByte <= 0xF7)
        {
            CodePoint = (uint32_t)(CurrentByte & 0x7);
            RemainingBytes = 3;
        }

        // We check we are allowed that many bytes for the codepoint
        if (ReadPos + RemainingBytes > Utf8Size)
            return CCUNICODE_STRING_ENDED_IN_CHARACTER;

        // Now collect remaining part of the codepoint (if any)
        for (size_t j = 0; j < RemainingBytes; ++j)
        {
            CodePoint <<= 6;
            CurrentByte = Utf8Str[ReadPos++];

            // The only valid range is 0x80-0xDF for an extension
            if (CurrentByte < 0x80 || CurrentByte > 0xDF)
                return CCUNICODE_INVALID_UTF8_CHARACTER;

            CodePoint += (uint32_t)(CurrentByte & 0x3F);
        }

        if (WritePos == INT_MAX)
            return CCUNICODE_OVERFLOW;
        Codepoints[WritePos++] = CodePoint;
    }

    if (ReadPos != Utf8Size)
        return CCUNICODE_BUFFER_TOO_SMALL;

    Codepoints[WritePos] = 0;
    return WritePos;
}

#ifndef __CCUNICODE_NOSTDALLOC__
int ccunicode_Utf16ToCodepoints(const uint16_t *Utf16Str, uint32_t **Codepoints)
{
    return ccunicode_Utf16ToCodepoints_a(Utf16Str, Codepoints, NULL);
}

int ccunicode_Utf16ToCodepoints_n(const uint16_t *Utf16Str, int Utf16Size, uint32_t **Codepoints)
{
    return ccunicode_Utf16ToCodepoints_na(Utf16Str, Utf16Size, Codepoints, NULL);
}
#endif

int ccunicode_Utf16ToCodepoints_a(const uint16_t *Utf16Str, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Utf16Size = ccunicode_GetUtf16StrLen(Utf16Str);
    if (Utf16Size < 0)
        return Utf16Size;

    return ccunicode_Utf16ToCodepoints_na(Utf16Str, Utf16Size, Codepoints, AllocPtr);
}

int ccunicode_Utf16ToCodepoints_na(const uint16_t *Utf16Str, int Utf16Size, uint32_t **Codepoints, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;

    int CodepointCount = ccunicode_CountCodepointsInUtf16_n(Utf16Str, Utf16Size);
    if (CodepointCount < 0)
        return CodepointCount;
    if (CodepointCount == INT_MAX)
        return CCUNICODE_OVERFLOW;

    if (CodepointCount+1 > INT_MAX/sizeof(**Codepoints))
        return CCUNICODE_OVERFLOW;
    *Codepoints = AllocPtr->malloc_func((CodepointCount+1)*sizeof(**Codepoints));
    if (!(*Codepoints))
        return CCUNICODE_BAD_ALLOCATION;

    int Result = ccunicode_Utf16ToCodepoints_nm(Utf16Str, Utf16Size, *Codepoints, CodepointCount);
    if (Result < 0)
    {
        AllocPtr->free_func(*Codepoints);
        *Codepoints = NULL;
    }
    return Result;
}

int ccunicode_Utf16ToCodepoints_m(const uint16_t *Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount)
{
    int Utf16Size = ccunicode_GetUtf16StrLen(Utf16Str);
    if (Utf16Size < 0)
        return Utf16Size;

    return ccunicode_Utf16ToCodepoints_nm(Utf16Str, Utf16Size, Codepoints, MaxCodepointsCount);
}

int ccunicode_Utf16ToCodepoints_nm(const uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount)
{
    if (!Utf16Str)
        return CCUNICODE_NULL_POINTER;
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;
    if (Utf16Size < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (MaxCodepointsCount < 0)
        return CCUNICODE_INVALID_PARAMETER;

    int WritePos = 0;
    int ReadPos = 0;
    while ((ReadPos < Utf16Size) && (WritePos < MaxCodepointsCount))
    {
        uint32_t CodePoint = 0;

        int RemainingBytes = 0;
        if (ReadPos == INT_MAX)
            return CCUNICODE_OVERFLOW;
        uint16_t CurrentCodeUnit = Utf16Str[ReadPos++];

        // We must distinguish between surrogate pairs and single units
        if (CurrentCodeUnit >= 0xD800 && CurrentCodeUnit <= 0xDFFF)
        {
            if (CurrentCodeUnit >= 0xDC00)
                return CCUNICODE_SURROGATE_PAIR_INVERSION;

            if (ReadPos == Utf16Size)
                return CCUNICODE_STRING_ENDED_IN_CHARACTER;

            uint16_t HighBits = CurrentCodeUnit - 0xD800;

            CurrentCodeUnit = Utf16Str[ReadPos++];
            if (CurrentCodeUnit == 0)
                return CCUNICODE_STRING_ENDED_IN_CHARACTER;
            if (CurrentCodeUnit < 0xDC00 || CurrentCodeUnit > 0xDFFF)
                return CCUNICODE_INVALID_UTF16_CHARACTER;

            uint16_t LowBits = CurrentCodeUnit - 0xDC00;

            CodePoint = ((uint32_t)(HighBits) << 10) + (uint32_t)(LowBits) + 0x10000;
        }
        else
        {
            if (CurrentCodeUnit == 0)
            {
                Codepoints[WritePos] = 0;
                return WritePos;
            }

            CodePoint = (uint32_t)CurrentCodeUnit;
        }

        if (WritePos == INT_MAX)
            return CCUNICODE_OVERFLOW;
        Codepoints[WritePos++] = CodePoint;
    }

    if (ReadPos != Utf16Size)
        return CCUNICODE_BUFFER_TOO_SMALL;
    Codepoints[WritePos] = 0;
    return WritePos;
}

#ifndef __CCUNICODE_NOSTDALLOC__
int ccunicode_CodepointsToUtf8(const uint32_t *Codepoints, uint8_t **Utf8Str)
{
    return ccunicode_CodepointsToUtf8_a(Codepoints, Utf8Str, NULL);
}

int ccunicode_CodepointsToUtf8_n(const uint32_t *Codepoints, int CodepointCount, uint8_t **Utf8Str)
{
    return ccunicode_CodepointsToUtf8_na(Codepoints, CodepointCount, Utf8Str, NULL);
}
#endif

int ccunicode_CodepointsToUtf8_a(const uint32_t *Codepoints, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    int CodepointCount = ccunicode_GetCodepointCount(Codepoints);
    if (CodepointCount < 0)
        return CodepointCount;

    return ccunicode_CodepointsToUtf8_na(Codepoints, CodepointCount, Utf8Str, AllocPtr);
}

int ccunicode_CodepointsToUtf8_na(const uint32_t *Codepoints, int CodepointCount, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    if (!Utf8Str)
        return CCUNICODE_NULL_POINTER;

    int Utf8Size = ccunicode_GetUtf8SizeFromCodepoints_n(Codepoints, CodepointCount);
    if (Utf8Size < 0)
        return Utf8Size;
    if (Utf8Size == INT_MAX)
        return CCUNICODE_OVERFLOW;

    *Utf8Str = AllocPtr->malloc_func(Utf8Size+1);
    if (!(*Utf8Str))
        return CCUNICODE_BAD_ALLOCATION;

    int Result = ccunicode_CodepointsToUtf8_nm(Codepoints, CodepointCount, *Utf8Str, Utf8Size);
    if (Result < 0)
    {
        AllocPtr->free_func(*Utf8Str);
        *Utf8Str = NULL;
    }
    return Result;
}

int ccunicode_CodepointsToUtf8_m(const uint32_t *Codepoints, uint8_t *Utf8Str, int Utf8Size)
{
    int CodepointCount = ccunicode_GetCodepointCount(Codepoints);
    if (CodepointCount < 0)
        return CodepointCount;

    return ccunicode_CodepointsToUtf8_nm(Codepoints, CodepointCount, Utf8Str, Utf8Size);
}

int ccunicode_CodepointsToUtf8_nm(const uint32_t *Codepoints, int CodepointCount, uint8_t *Utf8Str, int Utf8Size)
{
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;
    if (!Utf8Str)
        return CCUNICODE_NULL_POINTER;
    if (CodepointCount < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (Utf8Size < 0)
        return CCUNICODE_INVALID_PARAMETER;

    int WritePos = 0;
    int ReadPos = 0;
    while ((ReadPos < CodepointCount) && (WritePos < Utf8Size))
    {
        uint32_t CurrentCodepoint = Codepoints[ReadPos++];

        if (CurrentCodepoint > 0x10FFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint >= 0xD800 && CurrentCodepoint <= 0xDFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint == 0)
        {
            Utf8Str[WritePos] = 0;
            return WritePos;
        }

        if (CurrentCodepoint >= 1 && CurrentCodepoint <= 0x7F)
        {
            Utf8Str[WritePos++] = (uint8_t)CurrentCodepoint;
        }
        if (CurrentCodepoint >= 0x80 && CurrentCodepoint <= 0x7FF)
        {
            if (WritePos > Utf8Size-2)
                return CCUNICODE_BUFFER_TOO_SMALL;

            Utf8Str[WritePos++] = 0xC0 + (uint8_t)((CurrentCodepoint >> 6) & 0x1F);
            Utf8Str[WritePos++] = 0x80 + (uint8_t)(CurrentCodepoint & 0x3F);
        }
        if (CurrentCodepoint >= 0x800 && CurrentCodepoint <= 0xFFFF)
        {
            if (WritePos > Utf8Size-3)
                return CCUNICODE_BUFFER_TOO_SMALL;

            Utf8Str[WritePos++] = 0xE0 + (uint8_t)((CurrentCodepoint >> 12) & 0xF);
            Utf8Str[WritePos++] = 0x80 + (uint8_t)((CurrentCodepoint >> 6) & 0x3F);
            Utf8Str[WritePos++] = 0x80 + (uint8_t)((CurrentCodepoint) & 0x3F);
        }
        if (CurrentCodepoint >= 0x1000 && CurrentCodepoint <= 0x10FFFF)
        {
            if (WritePos > Utf8Size-4)
                return CCUNICODE_BUFFER_TOO_SMALL;

            Utf8Str[WritePos++] = 0xF0 + (uint8_t)((CurrentCodepoint >> 18) & 0xF);
            Utf8Str[WritePos++] = 0x80 + (uint8_t)((CurrentCodepoint >> 12) & 0x3F);
            Utf8Str[WritePos++] = 0x80 + (uint8_t)((CurrentCodepoint >> 6) & 0x3F);
            Utf8Str[WritePos++] = 0x80 + (uint8_t)((CurrentCodepoint) & 0x3F);
        }
    }

    if (ReadPos != CodepointCount)
        return CCUNICODE_BUFFER_TOO_SMALL;

    Utf8Str[WritePos] = 0;
    return WritePos;
}

#ifndef __CCUNICODE_NOSTDALLOC__
int ccunicode_CodepointsToUtf16(const uint32_t *Codepoints, uint16_t **Utf16Str)
{
    return ccunicode_CodepointsToUtf16_a(Codepoints, Utf16Str, NULL);
}

int ccunicode_CodepointsToUtf16_n(const uint32_t *Codepoints, int CodepointCount, uint16_t **Utf16Str)
{
    return ccunicode_CodepointsToUtf16_na(Codepoints, CodepointCount, Utf16Str, NULL);
}
#endif

int ccunicode_CodepointsToUtf16_a(const uint32_t *Codepoints, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    int CodepointCount = ccunicode_GetCodepointCount(Codepoints);
    if (CodepointCount < 0)
        return CodepointCount;

    return ccunicode_CodepointsToUtf16_na(Codepoints, CodepointCount, Utf16Str, AllocPtr);
}

int ccunicode_CodepointsToUtf16_na(const uint32_t *Codepoints, int CodepointCount, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    if (!Utf16Str)
        return CCUNICODE_NULL_POINTER;

    int Utf16Size = ccunicode_GetUtf16SizeFromCodepoints_n(Codepoints, CodepointCount);
    if (Utf16Size < 0)
        return Utf16Size;
    if (Utf16Size == INT_MAX)
        return CCUNICODE_OVERFLOW;

    if (Utf16Size+1 > INT_MAX/sizeof(*Utf16Str))
        return CCUNICODE_OVERFLOW;
    *Utf16Str = AllocPtr->malloc_func((Utf16Size+1)*sizeof(*Utf16Str));
    if (!(*Utf16Str))
        return CCUNICODE_BAD_ALLOCATION;

    int Result = ccunicode_CodepointsToUtf16_nm(Codepoints, CodepointCount, *Utf16Str, Utf16Size);
    if (Result < 0)
    {
        AllocPtr->free_func(*Utf16Str);
        *Utf16Str = NULL;
    }
    return Result;
}

int ccunicode_CodepointsToUtf16_m(const uint32_t *Codepoints, uint16_t *Utf16Str, int Utf16Size)
{
    int CodepointCount = ccunicode_GetCodepointCount(Codepoints);
    if (CodepointCount < 0)
        return CodepointCount;

    return ccunicode_CodepointsToUtf16_nm(Codepoints, CodepointCount, Utf16Str, Utf16Size);
}

int ccunicode_CodepointsToUtf16_nm(const uint32_t *Codepoints, int CodepointCount, uint16_t *Utf16Str, int Utf16Size)
{
    if (!Codepoints)
        return CCUNICODE_NULL_POINTER;
    if (!Utf16Str)
        return CCUNICODE_NULL_POINTER;
    if (CodepointCount < 0)
        return CCUNICODE_INVALID_PARAMETER;
    if (Utf16Size < 0)
        return CCUNICODE_INVALID_PARAMETER;

    int WritePos = 0;
    int ReadPos = 0;
    while ((ReadPos < CodepointCount) && (WritePos < Utf16Size))
    {
        uint32_t CurrentCodepoint = Codepoints[ReadPos++];

        if (CurrentCodepoint > 0x10FFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint >= 0xD800 && CurrentCodepoint <= 0xDFFF)
            return CCUNICODE_INVALID_CODEPOINT;
        if (CurrentCodepoint == 0)
        {
            Utf16Str[WritePos] = 0;
            return WritePos;
        }

        if (CurrentCodepoint >= 1 && CurrentCodepoint <= 0xFFFF)
        {
            Utf16Str[WritePos++] = (uint16_t)CurrentCodepoint;
        }

        if (CurrentCodepoint >= 0x10000 && CurrentCodepoint <= 0x10FFFF)
        {
            if (WritePos > Utf16Size-2)
                return CCUNICODE_BUFFER_TOO_SMALL;

            CurrentCodepoint -= 0x10000;
            uint16_t HighBits = (uint16_t)((CurrentCodepoint >> 10) & 0x3FF);
            uint16_t LowBits = (uint16_t)(CurrentCodepoint & 0x3FF);

            Utf16Str[WritePos++] = HighBits + 0xD800;
            Utf16Str[WritePos++] = LowBits + 0xDC00;
        }
    }

    if (ReadPos != CodepointCount)
        return CCUNICODE_BUFFER_TOO_SMALL;

    Utf16Str[WritePos] = 0;
    return WritePos;
}

#ifndef __CCUNICODE_NOSTDALLOC__
int ccunicode_Utf8ToUtf16(const uint8_t *Utf8Str, uint16_t **Utf16Str)
{
    return ccunicode_Utf8ToUtf16_a(Utf8Str, Utf16Str, NULL);
}

int ccunicode_Utf8ToUtf16_n(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str)
{
    return ccunicode_Utf8ToUtf16_na(Utf8Str, Utf8Size, Utf16Str, NULL);
}

int ccunicode_Utf8ToUtf16_m(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size)
{
    return ccunicode_Utf8ToUtf16_ma(Utf8Str, Utf16Str, Utf16Size, NULL);
}

int ccunicode_Utf8ToUtf16_nm(const uint8_t *Utf8Str, int Utf8Size, uint16_t *Utf16Str, int Utf16Size)
{
    return ccunicode_Utf8ToUtf16_nma(Utf8Str, Utf8Size, Utf16Str, Utf16Size, NULL);
}

int ccunicode_Utf8ToUtf16_l(const uint8_t *Utf8Str, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount)
{
    return ccunicode_Utf8ToUtf16_la(Utf8Str, Utf16Str, Codepoints, MaxCodepointsCount, NULL);
}

int ccunicode_Utf8ToUtf16_nl(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount)
{
    return ccunicode_Utf8ToUtf16_nla(Utf8Str, Utf8Size, Utf16Str, Codepoints, MaxCodepointsCount, NULL);
}

int ccunicode_Utf8ToUtf16_ml(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount)
{
    return ccunicode_Utf8ToUtf16_mla(Utf8Str, Utf16Str, Utf16Size, Codepoints, MaxCodepointsCount, NULL);
}
#endif

int ccunicode_Utf8ToUtf16_a(const uint8_t *Utf8Str, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf8ToCodepoints_a(Utf8Str, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf16_na(Codepoints, CodepointCount, Utf16Str, AllocPtr);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf8ToUtf16_na(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf8ToCodepoints_na(Utf8Str, Utf8Size, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf16_na(Codepoints, CodepointCount, Utf16Str, AllocPtr);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf8ToUtf16_ma(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf8ToCodepoints_a(Utf8Str, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf16_nm(Codepoints, CodepointCount, Utf16Str, Utf16Size);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf8ToUtf16_nma(const uint8_t *Utf8Str, int Utf8Size, uint16_t *Utf16Str, int Utf16Size, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf8ToCodepoints_na(Utf8Str, Utf8Size, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf16_nm(Codepoints, CodepointCount, Utf16Str, Utf16Size);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf8ToUtf16_la(const uint8_t *Utf8Str, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Res = ccunicode_Utf8ToCodepoints_m(Utf8Str, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf16_na(Codepoints, MaxCodepointsCount, Utf16Str, AllocPtr);
}

int ccunicode_Utf8ToUtf16_nla(const uint8_t *Utf8Str, int Utf8Size, uint16_t **Utf16Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Res = ccunicode_Utf8ToCodepoints_nm(Utf8Str, Utf8Size, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf16_na(Codepoints, MaxCodepointsCount, Utf16Str, AllocPtr);
}

int ccunicode_Utf8ToUtf16_mla(const uint8_t *Utf8Str, uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Res = ccunicode_Utf8ToCodepoints_m(Utf8Str, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf16_nm(Codepoints, MaxCodepointsCount, Utf16Str, Utf16Size);
}

int ccunicode_Utf8ToUtf16_nml(const uint8_t *Utf8Str, int Utf8Size, uint16_t *Utf16Str, int Utf16Size, uint32_t *Codepoints, int MaxCodepointsCount)
{
    int Res = ccunicode_Utf8ToCodepoints_nm(Utf8Str, Utf8Size, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf16_nm(Codepoints, MaxCodepointsCount, Utf16Str, Utf16Size);
}

#ifndef __CCUNICODE_NOSTDALLOC__
int ccunicode_Utf16ToUtf8(const uint16_t *Utf16Str, uint8_t **Utf8Str)
{
    return ccunicode_Utf16ToUtf8_a(Utf16Str, Utf8Str, NULL);
}

int ccunicode_Utf16ToUtf8_n(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str)
{
    return ccunicode_Utf16ToUtf8_na(Utf16Str, Utf16Size, Utf8Str, NULL);
}

int ccunicode_Utf16ToUtf8_m(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size)
{
    return ccunicode_Utf16ToUtf8_ma(Utf16Str, Utf8Str, Utf8Size, NULL);
}

int ccunicode_Utf16ToUtf8_nm(const uint16_t *Utf16Str, int Utf16Size, uint8_t *Utf8Str, int Utf8Size)
{
    return ccunicode_Utf16ToUtf8_nma(Utf16Str, Utf16Size, Utf8Str, Utf8Size, NULL);
}

int ccunicode_Utf16ToUtf8_l(const uint16_t *Utf16Str, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount)
{
    return ccunicode_Utf16ToUtf8_la(Utf16Str, Utf8Str, Codepoints, MaxCodepointsCount, NULL);
}

int ccunicode_Utf16ToUtf8_nl(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount)
{
    return ccunicode_Utf16ToUtf8_nla(Utf16Str, Utf16Size, Utf8Str, Codepoints, MaxCodepointsCount, NULL);
}

int ccunicode_Utf16ToUtf8_ml(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount)
{
    return ccunicode_Utf16ToUtf8_mla(Utf16Str, Utf8Str, Utf8Size, Codepoints, MaxCodepointsCount, NULL);
}
#endif

int ccunicode_Utf16ToUtf8_a(const uint16_t *Utf16Str, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf16ToCodepoints_a(Utf16Str, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf8_na(Codepoints, CodepointCount, Utf8Str, AllocPtr);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf16ToUtf8_na(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf16ToCodepoints_na(Utf16Str, Utf16Size, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf8_na(Codepoints, CodepointCount, Utf8Str, AllocPtr);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf16ToUtf8_ma(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf16ToCodepoints_a(Utf16Str, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf8_nm(Codepoints, CodepointCount, Utf8Str, Utf8Size);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf16ToUtf8_nma(const uint16_t *Utf16Str, int Utf16Size, uint8_t *Utf8Str, int Utf8Size, const TCCUnicode_MallocPtr *AllocPtr)
{
    CCUNICODE_INTERNAL_TEST(ccunicode_CheckAllocator(&AllocPtr))

    uint32_t *Codepoints = NULL;
    int CodepointCount = ccunicode_Utf16ToCodepoints_na(Utf16Str, Utf16Size, &Codepoints, AllocPtr);
    if (CodepointCount < 0)
        return CodepointCount;

    int Res = ccunicode_CodepointsToUtf8_nm(Codepoints, CodepointCount, Utf8Str, Utf8Size);
    AllocPtr->free_func(Codepoints);
    return Res;
}

int ccunicode_Utf16ToUtf8_la(const uint16_t *Utf16Str, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Res = ccunicode_Utf16ToCodepoints_m(Utf16Str, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf8_na(Codepoints, MaxCodepointsCount, Utf8Str, AllocPtr);
}

int ccunicode_Utf16ToUtf8_nla(const uint16_t *Utf16Str, int Utf16Size, uint8_t **Utf8Str, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Res = ccunicode_Utf16ToCodepoints_nm(Utf16Str, Utf16Size, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf8_na(Codepoints, MaxCodepointsCount, Utf8Str, AllocPtr);
}

int ccunicode_Utf16ToUtf8_mla(const uint16_t *Utf16Str, uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount, const TCCUnicode_MallocPtr *AllocPtr)
{
    int Res = ccunicode_Utf16ToCodepoints_m(Utf16Str, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf8_nm(Codepoints, MaxCodepointsCount, Utf8Str, Utf8Size);
}

int ccunicode_Utf16ToUtf8_nml(const uint16_t *Utf16Str, int Utf16Size, uint8_t *Utf8Str, int Utf8Size, uint32_t *Codepoints, int MaxCodepointsCount)
{
    int Res = ccunicode_Utf16ToCodepoints_nm(Utf16Str, Utf16Size, Codepoints, MaxCodepointsCount);
    if (Res < 0)
        return Res;

    return ccunicode_CodepointsToUtf8_nm(Codepoints, MaxCodepointsCount, Utf8Str, Utf8Size);
}
#   endif

#ifdef __cplusplus
}
#endif

#endif // __CCUNICODE_HEADER__
