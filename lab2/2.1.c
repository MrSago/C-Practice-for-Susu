
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>


int main() {
    double* mass;
    double* new_mass;
    char flag;
    double res;
    int n = 0, i;


    printf("Welcome to lab 2.1\n");

    printf("Enter n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Error input\n");
        return 0;
    }

    mass = (double*)malloc(sizeof(double) * n);
    if (mass == (double*)NULL) {
        printf("Error allocate memory\n");
        return 0;
    }

    new_mass = (double*)malloc(sizeof(double) * n);
    if (new_mass == (double*)NULL) {
        free(mass);
        printf("Error allocate memory\n");
        return 0;
    }

    printf("Enter array: ");
    for (i = 0; i < n; ++i) {
        if (scanf("%lf", &mass[i]) != 1) {
            free(mass);
            free(new_mass);
            printf("Error input\n");
            return 0;
        }
        if (mass[i] < 0.0) {
            new_mass[i] = mass[i] * mass[i];
        } else {
            new_mass[i] = mass[i];
        }
    }

    flag = 1;
    for (i = 0; i < n - 1; ++i) {
        if (new_mass[i] > new_mass[i + 1]) {
            flag = 0;
            break;
        }
    }
    if (flag) {
        res = mass[--n];
        while (n--) {
            res += mass[n];
        }
    } else {
        res = mass[--n];
        while (n--) {
            res *= mass[n];
        }
    }
    printf("Result: %lf\n", res);

    free(mass);
    free(new_mass);
    return 0;
}

