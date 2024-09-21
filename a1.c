#include <stdio.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 100

int main(int argc, char const *argv[])
{
    const int line_length = atoi(argv[1]);
    const char *file_name = argv[2];
    FILE *fp;
    char curr_word[MAX_WORD_LENGTH];

    fp = fopen(argv[2], "r");

    if (!line_length || fp == NULL)
    {
        puts("Bad arguments");
        return 1;
    }

    while (fscanf(fp, "%s", curr_word) != EOF)
    {
        printf("%s ", curr_word);
    }
    printf("\n");

    return 0;
}
