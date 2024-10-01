#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 100
#define MAX_WORD_NUMS 40
#define MAX_TEXT_LENGTH 200
#define SPACE ' '

int main(int argc, char const* argv[])
{
    if (argc < 3)
    {
        puts("error: have to use file name and line length as command line arguments");
        exit(1);
    }

    const int line_length = atoi(argv[1]);
    const char* file_name = argv[2];

    if (!line_length)
    {
        puts("Bad line length");
        exit(1);
    }

    FILE* fp;

    char words[MAX_WORD_NUMS][MAX_WORD_LENGTH];

    char* formatted_file;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        puts("Bad file name");
        exit(1);
    }
    return 0;
}
