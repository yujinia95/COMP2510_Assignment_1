#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 100
#define MAX_WORD_NUMS 40
#define MAX_TEXT_LENGTH 200

char *format_text(char words[MAX_WORD_NUMS][MAX_WORD_LENGTH], int word_count, int line_length);
void cpy_word(const char from[], char to[], const int start_index, const int end_index);
void print_array(char arr[MAX_WORD_NUMS][MAX_WORD_LENGTH], const int rows, const int cols);
int main(int argc, char const *argv[])
{
    const int line_length = atoi(argv[1]);
    const char *file_name = argv[2];

    FILE *fp;

    char curr_word[MAX_WORD_LENGTH];
    char words[MAX_WORD_NUMS][MAX_WORD_LENGTH];

    char *formatted_file;

    fp = fopen(argv[2], "r");

    if (!line_length || fp == NULL)
    {
        puts("Bad arguments");
        fclose(fp);
        exit(1);
    }

    int i = 0;
    while (fscanf(fp, "%s", words[i]) != EOF && i + strlen(words[i]) < MAX_TEXT_LENGTH)
    {
        if (strlen(words[i]) > line_length)
        {
            puts("A word is longer then the line length");
            fclose(fp);
            exit(1);
        }
        i++;
    }
    print_array(words, i, MAX_WORD_LENGTH);
    formatted_file = format_text(words, i, line_length);
    printf("%s\n", formatted_file);

    fclose(fp);
    free(formatted_file);
    return 0;
}

char *format_text(char words[MAX_WORD_NUMS][MAX_WORD_LENGTH], int word_count, int line_length)
{
    char *formatted_text = (char *)malloc(MAX_TEXT_LENGTH * sizeof(char));

    int curr_char = 0;
    for (int i = 0; i < word_count; i++)
    {
        /* TODO: do it so that it checks for more than 2 words in loop if it has to until it gets bigger than line
        length and then pad it*/
        if (strlen(words[i]) + strlen(words[i + 1]) < line_length)
        {
            cpy_word(words[i], formatted_text, curr_char, curr_char + strlen(words[i]));
            curr_char += strlen(words[i]) + 1;
        }
        else
        {
            cpy_word(words[i], formatted_text, curr_char, curr_char + strlen(words[i]));
            curr_char += strlen(words[i]) + 1;
            formatted_text[curr_char] = '\n';
            curr_char++;
        }
    }
    return formatted_text;
}

void cpy_word(const char from[], char to[], const int start_index, const int end_index)
{
    for (int i = start_index, j = 0; i < end_index; i++, j++)
    {
        to[i] = from[j];
    }
    to[end_index] = ' ';
}

void print_array(char arr[MAX_WORD_NUMS][MAX_WORD_LENGTH], const int rows, const int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("%s, ", arr[i]);
    }
    printf("\n");
}
