#include <stdio.h>
#include <stdlib.h>    
int globeArr[10] = { 1,2,3,4,5,6,7,8,9,10 };
int main(void)
{
    int* ip = (int*)malloc(10 * sizeof(int));
    ip[0] = 66446;
    int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int arr2[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int i = 10;

    printf("%p\n", arr);
    printf("%p\n", arr2);
    printf("%p\n", globeArr);
    printf("%p\n", ip);

    return 0;
}