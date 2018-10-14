cmake_minimum_required(VERSION 2.8.9)

project(ccunicode)

set(INCLUDES
  include/ccunicode.h)
  
set(LIB_SOURCES
  src/ccunicode.c)
  
add_library(ccunicode STATIC ${LIB_SOURCES} ${INCLUDES})

set(TEST_UTF8TOCODEPOINTS_SRC
    tests/Utf8ToCodepoints/main.c)

set(TEST_UTF16TOCODEPOINTS_SRC
    tests/Utf16ToCodepoints/main.c)

set(TEST_CODEPOINTSTOUTF8_SRC
    tests/CodepointsToUtf8/main.c)

set(TEST_CODEPOINTSTOUTF16_SRC
    tests/CodepointsToUtf16/main.c)

set(TEST_UTF8TOUTF16_SRC
    tests/Utf8ToUtf16/main.c)

set(TEST_UTF16TOUTF8_SRC
    tests/Utf16ToUtf8/main.c)

add_executable(test_Utf8ToCodepoints ${TEST_UTF8TOCODEPOINTS_SRC})
target_link_libraries(test_Utf8ToCodepoints ccunicode)

add_executable(test_Utf16ToCodepoints ${TEST_UTF16TOCODEPOINTS_SRC})
target_link_libraries(test_Utf16ToCodepoints ccunicode)

add_executable(test_CodepointsToUtf8 ${TEST_CODEPOINTSTOUTF8_SRC})
target_link_libraries(test_CodepointsToUtf8 ccunicode)

add_executable(test_CodepointsToUtf16 ${TEST_CODEPOINTSTOUTF16_SRC})
target_link_libraries(test_CodepointsToUtf16 ccunicode)

add_executable(test_Utf8ToUtf16 ${TEST_UTF8TOUTF16_SRC})
target_link_libraries(test_Utf8ToUtf16 ccunicode)

add_executable(test_Utf16ToUtf8 ${TEST_UTF16TOUTF8_SRC})
target_link_libraries(test_Utf16ToUtf8 ccunicode)

enable_testing()
add_test(
    NAME Utf8ToCodepoints
    COMMAND test_Utf8ToCodepoints)
add_test(
    NAME Utf16ToCodepoints
    COMMAND test_Utf16ToCodepoints)
add_test(
    NAME CodepointsToUtf8
    COMMAND test_CodepointsToUtf8)
add_test(
    NAME CodepointsToUtf16
    COMMAND test_CodepointsToUtf16)
add_test(
    NAME Utf8ToUtf16
    COMMAND test_Utf8ToUtf16)
add_test(
    NAME Utf16ToUtf8
    COMMAND test_Utf16ToUtf8)
