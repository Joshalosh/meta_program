#include <stdlib.h>
#include <stdio.h>
#include <stdint>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float  f32;
typedef double f64;
typedef int32_t b32;

enum Token_Type
{
    Token_Unknown,

    Token_OpenParen,
    Token_CloseParen,
    Token_OpenBracket,
    Token_CloseBracket,
    Token_Colon,
    Token_SemiColon,
    Token_Asterisk,

    Token_String,
    Token_Identifier,

    Token_EndOfStream,
};

struct Token {
    Token_Type type;

    size_t text_length;
    char *text;
};
