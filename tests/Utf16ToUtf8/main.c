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
    const uint16_t EmptyWStr[] = {0};

    uint8_t *Str;
    int Count = ccunicode_Utf16ToUtf8(EmptyWStr, &Str);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf16ToUtf8", Count);
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
        fprintf(stderr, "Empty string code point does not give single 0 codepoint");
        free(Str);
        return -1;
    }

    free(Str);
    return 0;
}

int TestHelloWorldString(void)
{
    const char HelloWorldStr[] = "Hello World !";
    const uint16_t HelloWorldWStr[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};

    uint8_t *Str;
    int Count = ccunicode_Utf16ToUtf8(HelloWorldWStr, &Str);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf16ToUtf8", Count);
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
        fprintf(stderr, "Mismatch for wide chars for Hello World string");
        free(Str);
        return -1;
    }

    free(Str);
    return 0;
}

int TestTrueUtf16String(void)
{
    const char TrueUtf16Str[] = "\u00C9\u0800\U00010000";
    const uint16_t TrueUtf16WStr[] = {0xC9, 0x800, 0xD800, 0xDC00, 0};

    uint8_t *Str;
    int Count = ccunicode_Utf16ToUtf8(TrueUtf16WStr, &Str);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf16ToUtf8", Count);
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
        fprintf(stderr, "Mismatch for codepoints for True Utf8 string");
        free(Str);
        return -1;
    }

    free(Str);
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

    return 0;
}
