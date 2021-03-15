
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ZNAK (12)
#define BUF_SIZE (128)

#define FIO_INDEX (0)
#define ZODIAC_INDEX (1)
#define DATE_INDEX (2)
#define COUNT_FIELDS (3)

#define DAY_INDEX (0)
#define MONTH_INDEX (1)
#define YEAR_INDEX (2)

typedef struct __znak {
    char fio[BUF_SIZE];
    char zodiac[BUF_SIZE];
    int date[3];
} znak;

int cmp(const void* a, const void* b) {
    int* t1 = ((znak*)a)->date;
    int* t2 = ((znak*)b)->date;


    if (t1[YEAR_INDEX] < t2[YEAR_INDEX]) {
        return -1;
    } else if (t1[YEAR_INDEX] > t2[YEAR_INDEX]) {
        return 1;
    } else if (t1[MONTH_INDEX] < t2[MONTH_INDEX]) {
        return -1;
    } else if (t1[MONTH_INDEX] > t2[MONTH_INDEX]) {
        return 1;
    } else if (t1[DAY_INDEX] < t2[DAY_INDEX]) {
        return -1;
    } else if (t1[DAY_INDEX] > t2[DAY_INDEX]) {
        return 1;
    }
    return 0;
}

int initZnak(znak** out) {
    znak* z = (znak*)NULL;
    znak* tmp;
    void* field_ptr[COUNT_FIELDS];
    char buf[BUF_SIZE] = { '\0' };
    char* ret_ptr = &buf[0];
    int i, j;


    z = (znak*)malloc(sizeof(znak) * MAX_ZNAK);
    if (z == (znak*)NULL) {
        return 0;
    }

    printf("Input data:\nfio\nzodiac\ndate\n");
    for (i = 0; i < MAX_ZNAK && ret_ptr != (char*)NULL && !feof(stdin); ++i) {
        field_ptr[FIO_INDEX] = (void*)&z[i].fio[0];
        field_ptr[ZODIAC_INDEX] = (void*)&z[i].zodiac[0];
        field_ptr[DATE_INDEX] = (void*)&z[i].date[0];
        for (j = 0;
                j < COUNT_FIELDS &&
                (ret_ptr = fgets(buf, BUF_SIZE, stdin)) != (char*)NULL &&
                !feof(stdin);
            ++j) {
            switch (j) {
                case DATE_INDEX:
                    sscanf(buf, "%d%d%d",
                            &((int*)field_ptr[DATE_INDEX])[DAY_INDEX],
                            &((int*)field_ptr[DATE_INDEX])[MONTH_INDEX],
                            &((int*)field_ptr[DATE_INDEX])[YEAR_INDEX]
                    );
                    break;
                default:
                    strcpy((char*)field_ptr[j], buf);
                    ((char*)field_ptr[j])[strlen(buf) - 1] = '\0';
                    break;
            }
        }
    }


    tmp = (znak*)realloc(z, sizeof(znak) * (i - 1));
    if (tmp == (znak*)NULL) {
        free(z);
        return 0;
    }
    *out = tmp;

    return i - 1;
}

void printZnak(znak* z, int size) {
    int i;


    for(i = 0; i < size; ++i) {
        printf("#1\nfio: %s\nzodiac: %s\ndate: %d.%d.%d\n",
            z[i].fio, z[i].zodiac,
            z[i].date[0], z[i].date[1], z[i].date[2]
        );
    }
}

int main() {
    znak* z = (znak*)NULL;
    int size = 0;
    char c;


    while (1) {
        printf("Menu:\n1.Init data\n2.Print data\n3.Sort data\n0.Exit\n");
        c = getchar();
        while (getchar() != '\n');
        switch(c) {
        case '1':
            if (z != (znak*)NULL) {
                free(z);
            }
            size = initZnak(&z);
            break;
        case '2':
            printZnak(z, size);
            break;
        case '3':
            if (z == (znak*)NULL) {
                printf("mass is empty\n");
                break;
            }
            qsort(z, size, sizeof(znak), cmp);
            printf("sorted!\n");
            break;
        case '0':
            if (z != (znak*)NULL) {
                free(z);
            }
            return 0;
        }
    }

    return 0;
}

