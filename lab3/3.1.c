
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

Array initArray() {
    Array a;


    a.m = (int*)malloc(sizeof(int));
    a.size = 0;
    a.capacity = 1;

    return a;
}

void freeArray(Array* a) {
    if (a != (Array*)NULL) {
        if (a->m != (int*)NULL) {
            free(a->m);
        }
        a->size = 0;
        a->capacity = 0;
    }
}

int pushElement(Array* a, int e) {
    int* tmp;


    if (a->size == a->capacity) {
        tmp = (int*)realloc(a->m, sizeof(int) * (a->capacity *= 2));
        if (tmp == (int*)NULL) {
            return 0;
        }
        a->m = tmp;
    }
    a->m[a->size++] = e;

    return 1;
}


int main() {
    Array arr;
    FILE* fd;
    int insert, repl, d, i;


    printf("Welcome to lab 3.1\n");

    printf("Enter insert value: ");
    if (scanf("%d", &insert) != 1) {
        printf("Error input\n");
        return -1;
    }

    printf("Enter replace value: ");
    if (scanf("%d", &repl) != 1) {
        printf("Error input\n");
        return -1;
    }

    arr = initArray();
    if (arr.m == (int*)NULL) {
        printf("Error allocate memory\n");
        return -3;
    }

    fd = fopen("INPUT.TXT", "r");
    if (fd == (FILE*)NULL) {
        freeArray(&arr);
        printf("Error open file\n");
        return -2;
    }

    printf("INPUT.TXT:\n");
    while (fscanf(fd, "%d", &d) != EOF) {
        printf("%d ", d);
        if (d == repl) {
            if (!pushElement(&arr, insert)) {
                fclose(fd);
                printf("Error reallocate memory\n");
                return -4;
            }
        }
        if (!pushElement(&arr, d)) {
            fclose(fd);
            printf("Error reallocate memory\n");
            return -4;
        }
    }
    fclose(fd);

    fd = fopen("OUTPUT.TXT", "w");
    if (fd == (FILE*)NULL) {
        freeArray(&arr);
        printf("Error open file\n");
        return -2;
    }

    printf("\nOUTPUT.TXT:\n");
    for (i = 0; i < arr.size; ++i) {
        printf("%d ", arr.m[i]);
        fprintf(fd, "%d ", arr.m[i]);
    }
    printf("\n");
    fprintf(fd, "\n");

    fclose(fd);
    freeArray(&arr);
    return 0;
}

