#include <stdio.h>
//#define foo short
typedef short int foo;

int main (int argc, char** argv) {
    foo x = 0, y = 2, z = 4;
    int* j=100;
    x = (z++)/(--y);
    printf("%d \n", (int)(j+1));
    return 0;
}
