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

#include "../../include/ccunicode.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int TestEmptyString(void)
{
    const uint16_t EmptyStr[] = {0};
    const uint32_t EmptyCodepoints[] = {0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf16ToCodepoints(EmptyStr, &Codepoints);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf16ToCodepoints", Count);
        return -1;
    }
    if (Count+1 != sizeof(EmptyCodepoints)/sizeof(*EmptyCodepoints))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(EmptyCodepoints)/sizeof(*EmptyCodepoints)), Count+1);
        free(Codepoints);
        return -1;
    }
    if (memcmp(EmptyCodepoints, Codepoints, (Count+1)*sizeof(*Codepoints)))
    {
        fprintf(stderr, "Empty string code point does not give a single 0 codepoint");
        free(Codepoints);
        return -1;
    }

    free(Codepoints);
    return 0;
}

int TestHelloWorldString(void)
{
    const uint16_t HelloWorldStr[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};
    const uint32_t HelloWorldCodepoints[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf16ToCodepoints(HelloWorldStr, &Codepoints);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf16ToCodepoints", Count);
        return -1;
    }
    if (Count+1 != sizeof(HelloWorldCodepoints)/sizeof(*HelloWorldCodepoints))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(HelloWorldCodepoints)/sizeof(*HelloWorldCodepoints)), Count+1);
        free(Codepoints);
        return -1;
    }
    if (memcmp(HelloWorldCodepoints, Codepoints, (Count+1)*sizeof(*Codepoints)))
    {
        fprintf(stderr, "Mismatch for codepoints for Hello World string");
        free(Codepoints);
        return -1;
    }

    free(Codepoints);
    return 0;
}

int TestTrueUtf16String(void)
{
    const uint16_t TrueUtf16Str[] = {0xC9, 0x800, 0xD800, 0xDC00, 0};
    const uint32_t TrueUtf16Codepoints[] = {0xC9, 0x800, 0x10000, 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf16ToCodepoints(TrueUtf16Str, &Codepoints);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf16ToCodepoints", Count);
        return -1;
    }
    if (Count+1 != sizeof(TrueUtf16Codepoints)/sizeof(*TrueUtf16Codepoints))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(TrueUtf16Codepoints)/sizeof(*TrueUtf16Codepoints)), Count+1);
        free(Codepoints);
        return -1;
    }
    if (memcmp(TrueUtf16Codepoints, Codepoints, (Count+1)*sizeof(*Codepoints)))
    {
        fprintf(stderr, "Mismatch for codepoints for True Utf16 string");
        free(Codepoints);
        return -1;
    }

    free(Codepoints);
    return 0;
}

int TestBadUtf16String1(void)
{
    const uint16_t BadUtf16Str1[] = {0xDC00, 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf16ToCodepoints(BadUtf16Str1, &Codepoints);
    if (Count != CCUNICODE_SURROGATE_PAIR_INVERSION)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF16 1. Returned %d", Count);
        if (Count >= 0)
            free(Codepoints);
        return -1;
    }

    return 0;
}

int TestBadUtf16String2(void)
{
    const uint16_t BadUtf16Str2[] = {0xD800, 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf16ToCodepoints(BadUtf16Str2, &Codepoints);
    if (Count != CCUNICODE_STRING_ENDED_IN_CHARACTER)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF16 2. Returned %d", Count);
        if (Count >= 0)
            free(Codepoints);
        return -1;
    }

    return 0;
}

int TestBadUtf16String3(void)
{
    const uint16_t BadUtf16Str3[] = {0xD800, 0x10, 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf16ToCodepoints(BadUtf16Str3, &Codepoints);
    if (Count != CCUNICODE_INVALID_UTF16_CHARACTER)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF16 3. Returned %d", Count);
        if (Count >= 0)
            free(Codepoints);
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int Res = 0;

#define TEST(t) \
    Res = t(); \
    if (Res) \
        return Res;

    TEST(TestEmptyString)
    TEST(TestHelloWorldString)
    TEST(TestTrueUtf16String)
    TEST(TestBadUtf16String1)
    TEST(TestBadUtf16String2)
    TEST(TestBadUtf16String3)

    return 0;
}
