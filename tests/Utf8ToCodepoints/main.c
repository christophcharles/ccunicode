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
    const char EmptyStr[] = "";
    const uint32_t EmptyCodepoints[] = {0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(EmptyStr, &Codepoints);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf8ToCodepoints", Count);
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
    const char HelloWorldStr[] = "Hello World !";
    const uint32_t HelloWorldCodepoints[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(HelloWorldStr, &Codepoints);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf8ToCodepoints", Count);
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

int TestTrueUtf8String(void)
{
    const char TrueUtf8Str[] = "\u00C9\u0800\U00010000";
    const uint32_t TrueUtf8Codepoints[] = {0xC9, 0x800, 0x10000, 0};

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(TrueUtf8Str, &Codepoints);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf8ToCodepoints", Count);
        return -1;
    }
    if (Count+1 != sizeof(TrueUtf8Codepoints)/sizeof(*TrueUtf8Codepoints))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(TrueUtf8Codepoints)/sizeof(*TrueUtf8Codepoints)), Count+1);
        free(Codepoints);
        return -1;
    }
    if (memcmp(TrueUtf8Codepoints, Codepoints, (Count+1)*sizeof(*Codepoints)))
    {
        fprintf(stderr, "Mismatch for codepoints for True Utf8 string");
        free(Codepoints);
        return -1;
    }

    free(Codepoints);
    return 0;
}

int TestBadUtf8String1(void)
{
    const char BadUtf8Str1[] = "\xC9";

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(BadUtf8Str1, &Codepoints);
    if (Count != CCUNICODE_STRING_ENDED_IN_CHARACTER)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF8 1. Returned %d", Count);
        if (Count >= 0)
            free(Codepoints);
        return -1;
    }

    return 0;
}

int TestBadUtf8String2(void)
{
    const char BadUtf8Str2[] = "\x80";

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(BadUtf8Str2, &Codepoints);
    if (Count != CCUNICODE_INVALID_UTF8_CHARACTER)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF8 2. Returned %d", Count);
        if (Count >= 0)
            free(Codepoints);
        return -1;
    }

    return 0;
}

int TestBadUtf8String3(void)
{
    const char BadUtf8Str3[] = "\xC0\x10";

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(BadUtf8Str3, &Codepoints);
    if (Count != CCUNICODE_INVALID_UTF8_CHARACTER)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF8 3. Returned %d", Count);
        if (Count >= 0)
            free(Codepoints);
        return -1;
    }

    return 0;
}

int TestBadUtf8String4(void)
{
    const char BadUtf8Str4[] = "\xE0\x80\x10";

    uint32_t *Codepoints;
    int Count = ccunicode_Utf8ToCodepoints(BadUtf8Str4, &Codepoints);
    if (Count != CCUNICODE_INVALID_UTF8_CHARACTER)
    {
        fprintf(stderr, "Expected error not encountered on Bad UTF8 4. Returned %d", Count);
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
    TEST(TestTrueUtf8String)
    TEST(TestBadUtf8String1)
    TEST(TestBadUtf8String2)
    TEST(TestBadUtf8String3)
    TEST(TestBadUtf8String4)

    return 0;
}
