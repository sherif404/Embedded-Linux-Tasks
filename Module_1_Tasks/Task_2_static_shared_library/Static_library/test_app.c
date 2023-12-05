#include <stdio.h>
#include <stdint.h>
#include "main.h"


int main() {
    int32_t a = 10, b = 5;

    printf("Addition: %ld\n", add(a, b));
    printf("Subtraction: %d\n", sub(a, b));
    printf("Multiplication: %ld\n", mul(a, b));
    printf("Custom Square Root of 64: %d\n", sqrt64(64));

    return 0;
}
