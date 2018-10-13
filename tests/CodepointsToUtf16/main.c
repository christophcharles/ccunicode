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

    uint16_t *Str;
    int Count = ccunicode_CodepointsToUtf16(EmptyCodepoints, &Str);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_CodepointsToUtf16", Count);
        return -1;
    }
    if (Count+1 != sizeof(EmptyStr)/sizeof(*EmptyStr))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(EmptyStr)/sizeof(*EmptyStr)), Count+1);
        free(Str);
        return -1;
    }
    if (memcmp(EmptyStr, Str, (Count+1)*sizeof(*Str)))
    {
        fprintf(stderr, "Empty string does not give single 0");
        free(Str);
        return -1;
    }

    free(Str);
    return 0;
}

int TestHelloWorldString(void)
{
    const uint16_t HelloWorldStr[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};
    const uint32_t HelloWorldCodepoints[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};

    uint16_t *Str;
    int Count = ccunicode_CodepointsToUtf16(HelloWorldCodepoints, &Str);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_CodepointsToUtf16", Count);
        return -1;
    }
    if (Count+1 != sizeof(HelloWorldStr)/sizeof(*HelloWorldStr))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(HelloWorldStr)/sizeof(*HelloWorldStr)), Count+1);
        free(Str);
        return -1;
    }
    if (memcmp(HelloWorldStr, Str, (Count+1)*sizeof(*Str)))
    {
        fprintf(stderr, "Mismatch for codepoints for Hello World string");
        free(Str);
        return -1;
    }

    free(Str);
    return 0;
}

int TestTrueUtf16String(void)
{
    const uint16_t TrueUtf16Str[] = {0xC9, 0x800, 0xD800, 0xDC00, 0};
    const uint32_t TrueUtf16Codepoints[] = {0xC9, 0x800, 0x10000, 0};

    uint16_t *Str;
    int Count = ccunicode_CodepointsToUtf16(TrueUtf16Codepoints, &Str);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_CodepointsToUtf16", Count);
        return -1;
    }
    if (Count+1 != sizeof(TrueUtf16Str)/sizeof(*TrueUtf16Str))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(TrueUtf16Str)/sizeof(*TrueUtf16Str)), Count+1);
        free(Str);
        return -1;
    }
    if (memcmp(TrueUtf16Str, Str, (Count+1)*sizeof(*Str)))
    {
        fprintf(stderr, "Mismatch for codepoints for True Utf16 string");
        free(Str);
        return -1;
    }

    free(Str);
    return 0;
}

int TestBadCodepoint1(void)
{
    const uint32_t BadCodepoint1[] = {0xD800, 0};

    uint16_t *Str;
    int Count = ccunicode_CodepointsToUtf16(BadCodepoint1, &Str);
    if (Count != CCUNICODE_INVALID_CODEPOINT)
    {
        fprintf(stderr, "Expected error not encountered on Bad Codepoint 1. Returned %d", Count);
        if (Count >= 0)
            free(Str);
        return -1;
    }

    return 0;
}

int TestBadCodepoint2(void)
{
    const uint32_t BadCodepoint2[] = {0xDFFF, 0};

    uint16_t *Str;
    int Count = ccunicode_CodepointsToUtf16(BadCodepoint2, &Str);
    if (Count != CCUNICODE_INVALID_CODEPOINT)
    {
        fprintf(stderr, "Expected error not encountered on Bad Codepoint 3. Returned %d", Count);
        if (Count >= 0)
            free(Str);
        return -1;
    }

    return 0;
}

int TestBadCodepoint3(void)
{
    const uint32_t BadCodepoint3[] = {0x110000, 0};

    uint16_t *Str;
    int Count = ccunicode_CodepointsToUtf16(BadCodepoint3, &Str);
    if (Count != CCUNICODE_INVALID_CODEPOINT)
    {
        fprintf(stderr, "Expected error not encountered on Bad Codepoint 3. Returned %d", Count);
        if (Count >= 0)
            free(Str);
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
    TEST(TestBadCodepoint1)
    TEST(TestBadCodepoint2)
    TEST(TestBadCodepoint3)

    return 0;
}
