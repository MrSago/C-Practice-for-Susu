
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <math.h>
#include <stdio.h>


int main() {
    double sum, f, s;
    int i, n;


    printf("Welcome to lab 1.5\n");

    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error input\n");
        return 0;
    }

    sum = 0.0;
    for (i = 1; i <= n; ++i) {
        f += cos((double)i);
        s += sin((double)i);
        sum += f/s;
    }
    printf("Result: %lf\n", sum);

    return 0;
}

