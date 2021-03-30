
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>

#define MAX_N (1000)

int main() {
    int mass[MAX_N];
    int last_min, count_even;
    int n = 0, i, j;


    printf("Welcome to lab 2.3\n");

    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error input\n");
        return 0;
    }

    printf("Enter array: ");
    last_min = 0;
    count_even = 0;
    for (i = 0; i < n; ++i) {
        if (scanf("%d", mass + i) != 1) {
            printf("Error input\n");
            return 0;
        }
        if (mass[i] < 0) {
            last_min = mass[i];
        }
    }

    for (i = 0; i < n; ++i) {
        if (mass[i] % 2 == 0 && ++count_even % 2 == 0) {
            for (j = n; j > i; --j) {
                mass[j] = mass[j - 1];
            }
            mass[i] = last_min;
            ++n; ++i;
        }
    }

    for (i = 0; i < n; ++i) {
        if (mass[i] == 0) {
            --n;
            for (j = i; j < n; ++j) {
                mass[j] = mass[j + 1];
            }
            --i;
        }
    }

    printf("Result: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", mass[i]);
    }
    printf("\n");

    return 0;
}

