#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 100
#define MAX_WORD_NUMS 40
#define MAX_TEXT_LENGTH 200
#define SPACE ' '

char* format_text(char words[MAX_WORD_NUMS][MAX_WORD_LENGTH], int word_count, int line_length);
void cpy_word(const char from[], char to[], const int start_index, const int end_index);
void print_array(char arr[], const int rows);
void insert_space(char arr[], const int end, const int location, const int spaces);
int str_includes(char* arr, int n, char ch);
void separate_word(char from[], char to[], const int start, const int end);
void center_word(char* arr, const int line_end, const int word_start, const int word_end);
void round_robin(char* arr, int curr_line, int line_length, int curr_line_length);
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
    int i = 0;
    int hyphen_index;
    while (fscanf(fp, "%s", words[i]) != EOF)
    {

        if (hyphen_index = str_includes(words[i], strlen(words[i]), '-'))
        {
            separate_word(words[i], words[i + 1], hyphen_index + 1, strlen(words[i]));

            if (strlen(words[i]) > line_length)
            {
                printf("Error. The word processor can't display the output.\n");
                fclose(fp);
                exit(1);
            }
            i++;
        }

        if (strlen(words[i]) > line_length)
        {
            printf("Error. The word processor can't display the output.\n");
            fclose(fp);
            exit(1);
        }
        i++;
    }
    formatted_file = format_text(words, i, line_length);
    // print_array(formatted_file, MAX_TEXT_LENGTH);
    printf("%s\n", formatted_file);

    fclose(fp);
    free(formatted_file);
    return 0;
}

char* format_text(char words[MAX_WORD_NUMS][MAX_WORD_LENGTH], int word_count, int line_length)
{
    char* formatted_text = (char*)malloc(MAX_TEXT_LENGTH * sizeof(char));

    int curr_char = 0;
    int curr_line = 1;
    int curr_line_length = 0;
    int curr_line_words = 0;
    for (int i = 0; i < word_count && ((curr_line - 1) * 10 + curr_line_length) < MAX_TEXT_LENGTH; i++)
    {
        // printf("WE AT WORD '%s'\n", words[i]);
        if (curr_line_length + strlen(words[i]) <= line_length)
        {
            cpy_word(words[i], formatted_text, curr_char, curr_char + strlen(words[i]));
            curr_char += strlen(words[i]) + 1;
            curr_line_length += strlen(words[i]) + 1;
            curr_line_words++;
        }
        else
        {
            if (curr_line_words > 1)
            {
                formatted_text[curr_char - 1] = '\0';
            }
            round_robin(formatted_text, curr_line, line_length, curr_line_length);
            if (curr_line_words != 1)
                curr_char += line_length - curr_line_length;

            formatted_text[curr_char] = '\n';
            curr_char++;
            curr_line++;
            cpy_word(words[i], formatted_text, curr_char, curr_char + strlen(words[i]));
            curr_char += strlen(words[i]) + 1;
            curr_line_length = strlen(words[i]) + 1;
            curr_line_words = 1;
        }
    }
    if (curr_line_words > 1)
    {
        formatted_text[curr_char - 1] = '\0';
    }
    round_robin(formatted_text, curr_line, line_length, curr_line_length);
    if (curr_line_words > 1)
    {
        curr_char += line_length - curr_line_length;
    }
    formatted_text[curr_char] = '\n';
    formatted_text[curr_char + 1] = '\0';

    return formatted_text;
}

void cpy_word(const char from[], char to[], const int start_index, const int end_index)
{
    for (int i = start_index, j = 0; i < end_index; i++, j++)
    {
        to[i] = from[j];
    }
    to[end_index] = SPACE;
}

void separate_word(char from[], char to[], const int start, const int end)
{
    for (int i = 0, j = start; j < end; i++, j++)
    {
        to[i] = from[j];
        from[j] = '\0';
    }
}

void print_array(char arr[], const int rows)
{
    for (int i = 0; i < rows; i++)
    {
        printf("%d|", arr[i]);
    }
    printf("\n");
}

void insert_space(char arr[], const int end, const int location, const int spaces)
{
    if (spaces == 0)
    {
        return;
    }

    for (int i = end; i >= location; i--)
    {
        arr[i + spaces] = arr[i];
    }

    for (int i = location; i < location + spaces; i++)
    {
        arr[i] = SPACE;
    }
}

int str_includes(char* arr, int n, char ch)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == ch)
        {
            return i;
        }
    }
    return 0;
}

void center_word(char* arr, const int line_end, const int word_start, const int word_end)
{
    // puts("" + arr);
    const int spaces = (word_start - line_end) - (word_start - word_end + 1);
    const int start_spaces = (spaces % 2 == 1) ? spaces / 2 + 1 : spaces / 2;
    const int end_spaces = spaces / 2;

    insert_space(arr, line_end, word_start, start_spaces);
    insert_space(arr, line_end, word_end + start_spaces, end_spaces);
}

void round_robin(char* arr, int curr_line, int line_length, int curr_line_length)
{
    int loops_done = 1;

    for (int j = (curr_line - 1) * (line_length + 1), total_space = line_length - curr_line_length + 1; total_space > 0; j++)
    {
        if (arr[j] == SPACE)
        {
            insert_space(arr, (curr_line * line_length), j, 1);
            j += loops_done;
            total_space--;
            puts("WE IN HERE");
        }
        if ((j + 1) == (line_length * curr_line))
        {
            j = (curr_line - 1) * (line_length + 1);
            loops_done++;
        }
    }
}
