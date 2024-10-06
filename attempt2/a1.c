#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LENGTH 100
#define MAX_WORD_NUMS 40
#define MAX_TEXT_LENGTH 4000
#define SPACE ' '
#define EXECUTE_FORMAT "<EXECUTABLE> line_length filename.txt"

char* format_file(FILE* fp, const int line_length);
void cpy_word(const char from[], char to[], const int start_index, const int end);
int str_includes(char* arr, char ch);
void print_arr_int(int* arr, int n);
void print_arr_char(char* arr, int n);
void justify_line(char* text, int* word_locations, int line_words, int line_end, int spaces, int line_length);
void insert_space(char* arr, const int end, const int location, const int spaces);
void center_word(char* text, int location, int line_end, int spaces, int line_length);
void separate_word(char from[], char to[], const int start, const int end);
int main(int argc, char const* argv[])
{
   // Check to make sure there are aleast 3 arguments
   if(argc < 3)
   {
      printf("error: have to use file name and line length as command line arguments: %s", EXECUTE_FORMAT);
      exit(1);
   }

   // Use the atoi function to extract int from the argument
   const int line_length = atoi(argv[1]);

   // Exit the program if atoi does not return the number
   if(!line_length)
   {
      printf("Error. Bad line length. %s\n", EXECUTE_FORMAT);
      exit(1);
   }

   const char* file_name = argv[2];
   FILE* fp;

   char* formatted_file;

   // Try to open the file using and exit the program if returns the NULL pointer
   if((fp = fopen(file_name, "r")) == NULL)
   {
      printf("Bad file name: %s", EXECUTE_FORMAT);
      exit(1);
   }
   // format the file
   formatted_file = format_file(fp, line_length);
   // print it out to the screen
   fputs(formatted_file, stdout);

   return 0;
}

/**
 * Takes a file pointer and returns a formatted and justified text of the same file.
 *
 * @param fp          The file pointer
 * @param line_length The length we want every line to be
 * @returns Pointer to formatted and justified text
 */
char* format_file(FILE* fp, const int line_length)
{
   char* formatted_file = (char*)malloc(MAX_TEXT_LENGTH * sizeof(char));
   char curr_word[MAX_WORD_LENGTH];
   char hyphen_word[MAX_WORD_LENGTH] = "";
   int word_start[MAX_WORD_NUMS] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };


   int current_char = 0;
   int current_line_length = 0;
   int current_line_words = 0;
   int curr_line = 1;
   int hyphen_index;
   while(fscanf(fp, "%s", curr_word) != EOF)
   {
      hyphen_index = str_includes(curr_word, '-');

      if(hyphen_index && current_line_words + current_line_length + hyphen_index + 1 <= line_length)
      {
         word_start[current_line_words] = current_char;

         printf("found hyphen at %d of curr word\n", hyphen_index);
         print_arr_int(word_start, current_line_length);
         print_arr_char(formatted_file, current_char);

         separate_word(curr_word, hyphen_word, hyphen_index, strlen(curr_word));

         cpy_word(hyphen_word, formatted_file, current_char, MAX_TEXT_LENGTH);

         current_line_words++;
         current_char += strlen(hyphen_word);
         current_line_length += strlen(hyphen_word);
      }

      if(strlen(curr_word) > line_length)
      {
         printf("Error. The word processor can't display the output.\n");
         fclose(fp);
         exit(1);
      }

      if(current_line_length + strlen(curr_word) + current_line_words <= line_length)
      {
         word_start[current_line_words] = current_char;

         cpy_word(curr_word, formatted_file, current_char, MAX_TEXT_LENGTH);

         current_char += strlen(curr_word);
         current_line_length += strlen(curr_word);
         current_line_words++;

         // printf("curr char: %2d, curr line length: %d\n", current_char, current_line_length);
      }
      else
      {
         int spaces = line_length - current_line_length;
         justify_line(formatted_file, word_start, current_line_words, (curr_line * line_length), spaces, line_length);
         current_char += spaces;

         formatted_file[current_char] = '\n';
         current_char++;

         cpy_word(curr_word, formatted_file, current_char, MAX_TEXT_LENGTH);

         word_start[0] = current_char;
         current_char += strlen(curr_word);
         current_line_length = strlen(curr_word);
         current_line_words = 1;
         curr_line++;
      }
   }
   int spaces = line_length - current_line_length;
   justify_line(formatted_file, word_start, current_line_words, (curr_line * line_length), spaces, line_length);
   current_char += spaces;

   formatted_file[current_char] = '\n';
   current_char++;

   print_arr_char(formatted_file, current_char);

   return formatted_file;
}

/**
 * Copy a word from an array to another probably longer array.
 *
 * @attention Might overflow
 * @param from[]      The word we want to copy to our array
 * @param to[]        The array we want to copy the word into
 * @param start_index The start index in the destination where we want the copied word to be
 * @param end         The max length of the destination array
 */
void cpy_word(const char from[], char to[], const int start_index, const int end)
{
   for(int i = start_index, j = 0; i < end && j < strlen(from); i++, j++)
   {
      to[i] = from[j];
   }
}

/**
 * Checks to see if a string includes a certain charecter and if it exists returns its index.
 *
 * @param arr The string we want to search
 * @param ch  The char we want to search for
 * @returns The index of the first instance of the char if exists and 0 if it does not
 */
int str_includes(char* arr, char ch)
{
   for(int i = 0; i < strlen(arr); i++)
   {
      if(arr[i] == ch)
      {
         return i;
      }
   }
   return 0;
}
//TODO: Document this function
void justify_line(char* text, int* word_locations, int line_words, int line_end, int spaces, int line_length)
{
   // printf("Before:%s\n", text);
   if(line_words == 1)
   {
      center_word(text, word_locations[0], line_end, spaces, line_length);
      return;
   }

   int i;
   while(spaces > 0)
   {
      for(i = 1; i < line_words; i++)
      {
         insert_space(text, line_end, word_locations[i], 1);
         spaces--;

         if(!(spaces > 0))
         {
            break;
         }

         for(int j = i + 1; j < line_words; j++)
         {
            word_locations[j]++;
         }
      }
   }
   for(int i = 0; i < line_words; i++)
   {
      word_locations[i] = 0;
   }

   // printf("After: %s\n", text);
}

/**
 * Prints out an array of ints.
 *
 * @param arr The array to be printed out
 * @param n   The number of elements to print out
 */
void print_arr_int(int* arr, int n)
{
   printf("{ ");

   for(int i = 0; i < n; i++)
   {
      printf("%d", arr[i]);
      if(i < n - 1)
      {
         printf(", ");
      }

   }

   printf(" }\n");
}

/**
 * Prints out an array of chars.
 *
 * @param arr The array to be printed out
 * @param n   The number of elements to print out
 */
void print_arr_char(char* arr, int n)
{
   printf("{ ");

   for(int i = 0; i < n; i++)
   {
      printf("%d", arr[i]);
      if(i < n - 1)
      {
         printf(", ");
      }

   }

   printf(" }\n");
}

/**
 * Inserts spaces in an array of chars.
 */
void insert_space(char arr[], const int end, const int location, const int spaces)
{
   if(spaces < 1)
   {
      printf("Warning. Adding negative spaces is impossible location: %d, spaces %d\n", location, spaces);
      return;
   }

   for(int i = end; i >= location; i--)
   {
      arr[i + spaces] = arr[i];
   }

   for(int i = location; i < location + spaces; i++)
   {
      arr[i] = SPACE;
   }
}

void center_word(char* text, int location, int line_end, int spaces, int line_length)
{
   const int end_spaces = spaces / 2;
   const int start_spaces = (spaces + 1) / 2;
   const int word_length = line_length - spaces;

   insert_space(text, line_end, location + word_length, end_spaces);
   insert_space(text, line_end, location, start_spaces);
}

void separate_word(char from[], char to[], const int start, const int end)
{
   for(int i = 0; i <= start; i++)
   {
      to[i] = from[i];
   }

   for(int i = 0; i < end; i++)
   {
      from[i] = from[i + start + 1];
      from[i + start + 1] = '\0';
   }

   printf("\n");
}