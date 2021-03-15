
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

int main() {
    Array arr;
    FILE* fd;
    int* tmp;
    int d, i;


    printf("Welcome to lab 3.1\n");

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

    while (fscanf(fd, "%d", &d) != EOF) {
        if (arr.size == arr.capacity) {
            tmp = (int*)realloc(arr.m, sizeof(int) * (arr.capacity *= 2));
            if (tmp == (int*)NULL) {
                fclose(fd);
                printf("Error allocate memory\n");
                return 0;
            }
            arr.m = tmp;
        }
        arr.m[arr.size++] = d;
    }
    fclose(fd);

    printf("INPUT.TXT:\n");
    for (i = 0; i < arr.size; ++i) {
        printf("%d ", arr.m[i]);
    }
    printf("\n");

    printf("Enter digit: ");
    if (scanf("%d", &d) != 1) {
        free(arr.m);
        printf("Error input\n");
        return 0;
    }

    tmp = (int*)realloc(arr.m, sizeof(int) * (arr.capacity = (arr.size * 2)));
    if (tmp == (int*)NULL) {
        printf("Error allocate memory\n");
        return 0;
    }
    arr.m = tmp;

    for (i = arr.size - 1; i >= 0; --i) {
        arr.m[(i + 1) * 2 - 1] = arr.m[i];
    }
    arr.size = arr.capacity;
    for (i = 0; i < arr.size; i += 2) {
        arr.m[i] = d;
    }

    fd = fopen("OUTPUT.TXT", "w");
    if (fd == (FILE*)NULL) {
        free(arr.m);
        printf("Error open file\n");
        return 0;
    }

    printf("OUTPUT.TXT:\n");
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

