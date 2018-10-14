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

    uint16_t *WStr;
    int Count = ccunicode_Utf8ToUtf16(EmptyStr, &WStr);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf8ToUtf16", Count);
        return -1;
    }
    if (Count+1 != sizeof(EmptyWStr)/sizeof(*EmptyWStr))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(EmptyWStr)/sizeof(*EmptyWStr)), Count+1);
        free(WStr);
        return -1;
    }
    if (memcmp(EmptyWStr, WStr, (Count+1)*sizeof(*WStr)))
    {
        fprintf(stderr, "Empty string code point does not give single 0 codepoint");
        free(WStr);
        return -1;
    }

    free(WStr);
    return 0;
}

int TestHelloWorldString(void)
{
    const char HelloWorldStr[] = "Hello World !";
    const uint16_t HelloWorldWStr[] = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', ' ', '!', 0};

    uint16_t *WStr;
    int Count = ccunicode_Utf8ToUtf16(HelloWorldStr, &WStr);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf8ToUtf16", Count);
        return -1;
    }
    if (Count+1 != sizeof(HelloWorldWStr)/sizeof(*HelloWorldWStr))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(HelloWorldWStr)/sizeof(*HelloWorldWStr)), Count+1);
        free(WStr);
        return -1;
    }
    if (memcmp(HelloWorldWStr, WStr, (Count+1)*sizeof(*WStr)))
    {
        fprintf(stderr, "Mismatch for wide chars for Hello World string");
        free(WStr);
        return -1;
    }

    free(WStr);
    return 0;
}

int TestTrueUtf8String(void)
{
    const char TrueUtf8Str[] = "\u00C9\u0800\U00010000";
    const uint16_t TrueUtf8WStr[] = {0xC9, 0x800, 0xD800, 0xDC00, 0};

    uint16_t *WStr;
    int Count = ccunicode_Utf8ToUtf16(TrueUtf8Str, &WStr);
    if (Count < 0)
    {
        fprintf(stderr, "Error %d in ccunicode_Utf8ToUtf16", Count);
        return -1;
    }
    if (Count+1 != sizeof(TrueUtf8WStr)/sizeof(*TrueUtf8WStr))
    {
        fprintf(stderr, "Mismatch between expected output size (%d) and effective output size (%d).", (int)(sizeof(TrueUtf8WStr)/sizeof(*TrueUtf8WStr)), Count+1);
        free(WStr);
        return -1;
    }
    if (memcmp(TrueUtf8WStr, WStr, (Count+1)*sizeof(*WStr)))
    {
        fprintf(stderr, "Mismatch for codepoints for True Utf8 string");
        free(WStr);
        return -1;
    }

    free(WStr);
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

    return 0;
}
