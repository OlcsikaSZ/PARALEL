#include <stdio.h>
#include <unistd.h> 

int main() {
    printf("A program most alvó üzemmódban van.\n");

    sleep(3);

    printf("3 másodperc eltelt, a program folytatódik.\n");

    return 0;
}