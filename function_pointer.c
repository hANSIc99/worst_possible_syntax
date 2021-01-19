#include <stdio.h>


int sum(int a, int b)
{
    return a+b;
}

int *next(int *arrayOfInt){
    return ++arrayOfInt;
}

int main(int argc, char* argv[]){
    printf("Hello World\n");

    /* Step one: Ordinary function pointer */
    int (*funcPtrOne)(int, int);

    funcPtrOne = &sum;

    int resultOne = funcPtrOne(2, 5);

    printf("The first result is: %d\n", resultOne);

    /* Step two: Pointer to functions with pointers as argument */

    int array[] = {1, 2, 3, 4, 5};

    int *(*funcPtrTwo)(int *intPtr);

    funcPtrTwo = &next;

    int resultTwo = *funcPtrTwo(&array[0]);

    printf("The second result is: %d\n", resultTwo);


}