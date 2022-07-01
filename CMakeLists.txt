cmake_minimum_required(VERSION 3.20)
project(lua_huffman C)
set(CMAKE_C_STANDARD 11)
include_directories(F:/conda/Library/include ./huffman)
link_directories("F:\\conda\\Library\\lib" F:/conda/Library/bin)

if(MSVC)
    add_definitions (-D_WIN32_WINNT=0x0400)
    add_definitions (-D_SCL_SECURE_NO_WARNINGS=1)
    add_definitions (-D_CRT_SECURE_NO_WARNINGS=1)

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /utf-8")
endif()
if(UNIX)
    set(CMAKE_C_FLAGS "$ENV{CFLAGS} ${CMAKE_C_FLAGS} -Wall -Werror -D_POSIX_C_SOURCE=2")
endif()

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

set(SOURCES huffman/huffman.c)

add_library(hfm SHARED src/lhfm.c ${SOURCES})
target_link_libraries(hfm lua)
if(WIN32)
    target_link_libraries(hfm ws2_32)
endif()

set_target_properties(hfm PROPERTIES OUTPUT_NAME hfm)

