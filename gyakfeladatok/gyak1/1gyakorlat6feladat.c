#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL)); 
    int num1 = rand() % 100 + 1; 
    int num2 = rand() % 100 + 1; 

    int correct_answer = num1 + num2;

    printf("Add meg a két szám összegét: %d + %d = ?\n", num1, num2);

    clock_t start_time = clock();

    int user_answer;
    scanf("%d", &user_answer);

    clock_t end_time = clock();

    if (user_answer == correct_answer) {
        printf("Helyes válasz!\n");
    } else {
        printf("Hibás válasz! A helyes válasz: %d\n", correct_answer);
    }

    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("A számítás %f másodpercig tartott.\n", time_taken);

    return 0;
}
