#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define Assert(expression) if(!(expression)) {*(int *)0 = 0;}

enum Token_Type {
    Token_Unknown,

    Token_OpenParen,
    Token_CloseParen,
    Token_Asterisk,
    Token_Colon,
    Token_Semicolon,
    Token_OpenBracket,
    Token_CloseBracker,
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

Memory_Arena ArenaInit(size_t size) {
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
        printf("There is not enough room  in the arena");
        //Assert(1 == 0);
    }

    return result;
}

#define ZeroStruct(instance) ZeroSize(&instance, sizeof(instance))
void ZeroSize(void *ptr, size_t size) {
    char *byte = (char *)ptr;

    while (size--) {
        *byte++ = 0;
    }
}

void ArenaFree(Memory_Arena *arena) {
    free(arena->start);
}

char *ReadEntireFileIntoMemoryAndNullTerminate(Memory_Arena *arena, char *filename) {
    char *result = NULL;
    FILE *file = fopen(filename, "r");

    if (file) {
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);

        result = (char *)ArenaAlloc(arena, file_size + 1);
        fread(result, file_size, 1, file);
        result[file_size] = 0; // Don't forget to null terminate you doofus!

        fclose(file);
    }

    return result;
}



int main()
{
};
