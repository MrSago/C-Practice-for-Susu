
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>


typedef struct __array {
    int* m;
    int size;
    int capacity;
} Array;

int resizeArray(Array* a) {
    int* tmp;


    if (a->size == a->capacity) {
        tmp = (int*)realloc(a->m, sizeof(int) * (a->capacity *= 2));
        if (tmp == (int*)NULL) {
            return -1;
        }
        a->m = tmp;
    }

    return 0;
}

int main() {
    Array arr;
    FILE* fd;
    int insert, repl, d, i;


    printf("Welcome to lab 3.1\n");

    printf("Enter insert value: ");
    if (scanf("%d", &insert) != 1) {
        printf("Error input\n");
        return 0;
    }

    printf("Enter replace value: ");
    if (scanf("%d", &repl) != 1) {
        printf("Error input\n");
        return 0;
    }

    fd = fopen("INPUT.TXT", "r");
    if (fd == (FILE*)NULL) {
        printf("Error open file\n");
        return 0;
    }

    arr.m = (int*)malloc(sizeof(int));
    if (arr.m == (int*)NULL) {
        fclose(fd);
        printf("Error allocate memory\n");
        return 0;
    }
    arr.size = 0;
    arr.capacity = 1;

    printf("INPUT.TXT:\n");
    while (fscanf(fd, "%d", &d) != EOF) {
        printf("%d ", d);
        if (d == repl) {
            if (resizeArray(&arr)) {
                fclose(fd);
                printf("Error reallocate memory\n");
                return 0;
            }
            arr.m[arr.size++] = insert;
        }
        if (resizeArray(&arr)) {
            fclose(fd);
            printf("Error reallocate memory\n");
            return 0;
        }
        arr.m[arr.size++] = d;
    }
    fclose(fd);

    fd = fopen("OUTPUT.TXT", "w");
    if (fd == (FILE*)NULL) {
        free(arr.m);
        printf("Error open file\n");
        return 0;
    }

    printf("\nOUTPUT.TXT:\n");
    for (i = 0; i < arr.size; ++i) {
        printf("%d ", arr.m[i]);
        fprintf(fd, "%d ", arr.m[i]);
    }
    printf("\n");
    fprintf(fd, "\n");

    fclose(fd);
    free(arr.m);
    return 0;
}

