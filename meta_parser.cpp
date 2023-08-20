#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

enum Token_Type {
    Token_Unknown,

    Token_OpenParen,
    Token_CloseParen,
    Token_Asterisk,
    Token_Colon,
    Token_Semicolon,
    Token_OpenBracket,
    Token_CloseBracket,
    Token_OpenBrace,
    Token_CloseBrace,

    Token_String,
    Token_Identifier,

    Token_EndOfStream,
};

struct Token {
    Token_Type type;

    char *text;
    size_t text_length; 
};

struct Memory_Arena {
    char *start;
    char *current;
    char *end;
};

Memory_Arena InitArena(size_t size) {
    Memory_Arena result;
    result.start   = (char *)malloc(size);
    result.current = result.start;
    result.end     = result.current + size;

    return result;
}

void *ArenaAlloc(Memory_Arena *arena, size_t size) {
    void *result = NULL;

    if (arena->current + size <= arena->end) {
        result          = arena->current;
        arena->current += size;
    } else {
        printf("There's no room in the arena");
    }

    return result;
}

char *ReadEntireFileIntoMemoryAndNullTerminate(Memory_Arena *arena, char *filename) {
    char *result = NULL;
    FILE *file   = fopen(filename, "r");

    if (file) {
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        result = (char *)ArenaAlloc(arena, file_size);
        fread(result, file_size, 1, file);
        result[file_size] = 0;

        fclose(file);
    }

    return result;
}

int main()
{
};
