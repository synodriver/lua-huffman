#include <stdlib.h>
#include "lua.h"
#include "lauxlib.h"

#include "huffman.h"

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#elif
#define DLLEXPORT
#endif /* _WIN32 */


#define NULL_TO_RAISE(x, reason) \
if (x==NULL) \
{ \
 return luaL_error(L, reason); \
} \



static int
lencode_file(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must set an input file and output file");
    }
    size_t input_file_name_len;
    const char *input_file_name = luaL_checklstring(L, 1, &input_file_name_len);
    size_t output_file_name_len;
    const char *output_file_name = luaL_checklstring(L, 2, &output_file_name_len);

    FILE *input_file = fopen(input_file_name, "rb");
    NULL_TO_RAISE(input_file, "can't open input file")

    FILE *output_file = fopen(output_file_name, "wb");
    NULL_TO_RAISE(output_file, "can't open output file")


    if (huffman_encode_file(input_file, output_file) == 1)
    {
        return luaL_error(L, "encode error");
    }
    return 0;
}

static int
ldecode_file(lua_State *L)
{
    if (lua_gettop(L) != 2)
    {
        return luaL_error(L, "must set an input file and output file");
    }
    size_t input_file_name_len;
    const char *input_file_name = luaL_checklstring(L, 1, &input_file_name_len);
    size_t output_file_name_len;
    const char *output_file_name = luaL_checklstring(L, 2, &output_file_name_len);

    FILE *input_file = fopen(input_file_name, "rb");
    NULL_TO_RAISE(input_file, "can't open input file")

    FILE *output_file = fopen(output_file_name, "wb");
    NULL_TO_RAISE(output_file, "can't open output file")


    if (huffman_decode_file(input_file, output_file) == 1)
    {
        return luaL_error(L, "decode error");
    }
    return 0;
}

static int
lencode_mem(lua_State* L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must hava only one argument");
    }
    size_t input_len;
    const char *input = luaL_checklstring(L, 1, &input_len);
    unsigned char* output = NULL;
    unsigned int outlen;
    if(huffman_encode_memory((const unsigned char*)input, (unsigned int)input_len, &output, &outlen) ==1)
    {
        free(output);
        return luaL_error(L, "encode error");
    }
    lua_pushlstring(L, (const char*)output, (size_t)outlen);
    return 1;
}

static int
ldecode_mem(lua_State* L)
{
    if (lua_gettop(L) != 1)
    {
        return luaL_error(L, "must hava only one argument");
    }
    size_t input_len;
    const char *input = luaL_checklstring(L, 1, &input_len);
    unsigned char* output = NULL;
    unsigned int outlen;
    if(huffman_decode_memory((const unsigned char*)input, (unsigned int)input_len, &output, &outlen) ==1)
    {
        free(output);
        return luaL_error(L, "decode error");
    }
    lua_pushlstring(L, (const char*)output, (size_t)outlen);
    return 1;
}

static luaL_Reg lua_funcs[] = {
        {"encode_file", &lencode_file},
        {"decode_file", &ldecode_file},
        {"encode",     &lencode_mem},
        {"decode",     &ldecode_mem},
        {NULL, NULL}
};

DLLEXPORT int luaopen_hfm(lua_State *L)
{
    luaL_newlib(L, lua_funcs);
    return 1;
}