
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ZNAK (12)
#define BUF_SIZE (128)


typedef struct __znak {
    char familiya[BUF_SIZE];
    char zodiac[BUF_SIZE];
    int date[3];
} znak;

enum znak_index {
    FAMILIYA_INDEX,
    ZODIAC_INDEX,
    DATE_INDEX,
    COUNT_FIELDS
};

enum date_index {
    DAY_INDEX,
    MONTH_INDEX,
    YEAR_INDEX
};


int cmp(const void* a, const void* b) {
    int* t1 = ((znak*)a)->date;
    int* t2 = ((znak*)b)->date;


    return t1[YEAR_INDEX] < t2[YEAR_INDEX] ? -1 :       \
                t1[YEAR_INDEX] > t2[YEAR_INDEX] ? 1 :   \
            t1[MONTH_INDEX] < t2[MONTH_INDEX] ? -1 :    \
                t1[MONTH_INDEX] > t2[MONTH_INDEX] ? 1 : \
            t1[DAY_INDEX] < t2[DAY_INDEX] ? -1 :        \
                t1[DAY_INDEX] > t2[DAY_INDEX] ? 1 : 0;
}

znak* initZnak(int* size) {
    void* field[COUNT_FIELDS];
    znak* z = (znak*)NULL, * tmp;
    char buf[BUF_SIZE] = { '\0' };
    char* ret_ptr = buf;
    int i, j;


    z = (znak*)malloc(sizeof(znak) * MAX_ZNAK);
    if (z == (znak*)NULL) {
        *size = 0;
        return z;
    }

    printf("Введите данные (0 - конец ввода):\n");
    printf("1.Фамилия\n");
    printf("2.Знак зодиака\n");
    printf("3.Дата рождения\n");

    for (i = 0;
            i < MAX_ZNAK &&
            ret_ptr[0] != '0';
        ++i
    ) {
        printf("\n%d. клиент\n", i + 1);

        field[FAMILIYA_INDEX] = (void*)z[i].familiya;
        field[ZODIAC_INDEX] = (void*)z[i].zodiac;
        field[DATE_INDEX] = (void*)z[i].date;

        for (j = 0;
                j < COUNT_FIELDS &&
                (ret_ptr = fgets(buf, BUF_SIZE, stdin))[0] != '0';
            ++j
        ) {
            switch (j) {
                case DATE_INDEX:
                    sscanf(buf, "%d%d%d",
                            ((int*)field[j]) + DAY_INDEX,
                            ((int*)field[j]) + MONTH_INDEX,
                            ((int*)field[j]) + YEAR_INDEX
                    );
                    break;
                default:
                    strcpy((char*)field[j], buf);
                    ((char*)field[j])[strlen(buf) - 1] = '\0';
                    break;
            }
        }
    }

    tmp = (znak*)realloc(z, sizeof(znak) * (i - 1));
    if (tmp == (znak*)NULL) {
        *size = 0;
        return tmp;
    }

    *size = i - 1;
    qsort(tmp, *size, sizeof(znak), cmp);
    return tmp;
}

void printZnak(znak* z, int size) {
    int i;


    if (size <= 0) {
        printf("\nСписок пуст!\n");
        return;
    }

    printf("\nСписок:\n");
    for (i = 0; i < size; ++i) {
        printf("№%d\nФамилия: %s\n", i + 1, z[i].familiya);
        printf("Знак зодиака: %s\n", z[i].zodiac);
        printf("Дата рождения: %d.%d.%d\n", z[i].date[0], z[i].date[1], z[i].date[2]);
    }
}

void findZnak(znak* z, int size) {
    char buf[BUF_SIZE] = { '\0' };
    int i;
    int check = 0;


    if (size <= 0) {
        printf("\nСписок пуст!\n");
        return;
    }

    printf("\nВведите фамилию: ");
    fgets(buf, BUF_SIZE, stdin);
    buf[strlen(buf) - 1] = '\0';

    for (i = 0; i < size; ++i) {
        if (!strcmp(z[i].familiya, buf)) {
            printf("Найдено совпадение:\n");
            printf("№%d\nФамилия: %s\n", i + 1, z[i].familiya);
            printf("Знак зодиака: %s\n", z[i].zodiac);
            printf("Дата рождения: %d.%d.%d\n", z[i].date[0], z[i].date[1], z[i].date[2]);
            check = 1;
        }
    }

    if (!check) {
        printf("Записи не найдены\n");
    }
}

int main() {
    znak* z = (znak*)NULL;
    int size = 0;
    char c;


    while (1) {
        printf("\nМеню\n");
        printf("1.Ввод данных\n");
        printf("2.Вывод данных\n");
        printf("3.Вывод по фамилии\n");
        printf("0.Выход\n");

        c = getchar();
        while (c != '\n' && getchar() != '\n');
        switch(c) {
        case '1':
            if (z != (znak*)NULL) {
                free(z);
            }
            z = initZnak(&size);
            break;
        case '2':
            printZnak(z, size);
            break;
        case '3':
            findZnak(z, size);
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

