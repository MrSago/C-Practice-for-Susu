
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>

int main() {
    int* mass;
    int* tmp;
    int last_neg, count_even;
    int n = 0, i, j;


    printf("Welcome to lab 2.3\n");

    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error input\n");
        return 0;
    }

    mass = (int*)malloc(sizeof(int) * n);
    if (mass == (int*)NULL) {
        printf("Error allocate memory\n");
        return 0;
    }

    printf("Enter array: ");
    last_neg = 0;
    count_even = 0;
    for (i = 0; i < n; ++i) {
        if (scanf("%d", mass + i) != 1) {
            free(mass);
            printf("Error input\n");
            return 0;
        }
        if (mass[i] < 0) {
            last_neg = mass[i];
        }
        if (mass[i] != 0 && mass[i] % 2 == 0) {
            ++count_even;
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

    tmp = (int*)realloc(mass, sizeof(int) * (n + count_even / 2));
    if (tmp == (int*)NULL) {
        printf("Error allocate memory\n");
        return 0;
    }
    mass = tmp;

    count_even = 0;
    for (i = 0; i < n; ++i) {
        if (mass[i] % 2 == 0) {
            if (++count_even % 2 == 0) {
                for (j = n; j > i; --j) {
                    mass[j] = mass[j - 1];
                }
                mass[i] = last_neg;
                ++n; ++i;
            }
        }
    }

    printf("Result: ");
    for (i = 0; i < n; ++i) {
        printf("%d ", mass[i]);
    }
    printf("\n");

    free(mass);
    return 0;
}

