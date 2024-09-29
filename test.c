#include <stdio.h>

void insert_space(char arr[], const int end, const int location, const int spaces)
{
    for (int i = end; i >= location; i--)
    {
        arr[i + spaces] = arr[i];
    }
    for (int i = location; i < location + spaces; i++)
    {
        arr[i] = ' ';
    }

}

int main(void)
{
    char smth[40] = "what thefuckareyoutalkingaboutman";

    insert_space(smth, 33, 4, 2);

    printf("%s\n", smth);

    return 0;
}