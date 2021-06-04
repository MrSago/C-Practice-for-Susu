
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

typedef struct __list {
    struct __list* prev;
    struct __list* next;
    znak* z;
} list;

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

void pushZnak(list* l, znak* z) {
    list* prev;


    if (l->z == (znak*)NULL) {
        l->z = z;
        return;
    }

    while (l != (list*)NULL && cmp(l->z, z) != 1) {
        prev = l;
        l = l->next;
    }

    list* p = (list*)malloc(sizeof(list*));
    if (p == (list*)NULL) {
        return;
    }

    if (l == (list*)NULL) {
        prev->next = p;
        p->prev = prev;
        p->next = (list*)NULL;
    } else {
        if (l->prev != (list*)NULL) {
            l->prev->next = p;
        }
        p->prev = l->prev;
        p->next = l;
        l->prev = p;
    }
    p->z = z;
}

list* initList() {
    void* field[COUNT_FIELDS];
    list* head;
    znak* z;
    char buf[BUF_SIZE] = { '\0' };
    char* ret_ptr = buf;
    int i, j;


    head = (list*)malloc(sizeof(list));
    if (head == (list*)NULL) {
        return head;
    }
    head->prev = (list*)NULL;
    head->next = (list*)NULL;
    head->z = (znak*)NULL;

    printf("Введите данные (0 - конец ввода):\n");
    printf("1.Фамилия\n");
    printf("2.Знак зодиака\n");
    printf("3.Дата рождения\n");

    for (i = 0;
            i < MAX_ZNAK &&
            ret_ptr[0] != '0';
        ++i
    ) {
        printf("\n%d клиент\n", i + 1);

        z = (znak*)malloc(sizeof(znak));
        if (z == (znak*)NULL) {
            return head;
        }

        field[FAMILIYA_INDEX] = (void*)z->familiya;
        field[ZODIAC_INDEX] = (void*)z->zodiac;
        field[DATE_INDEX] = (void*)z->date;

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
        if (ret_ptr[0] != '0') {
            pushZnak(head, z);
            while (head->prev != (list*)NULL) head = head->prev;
        } else {
            free(z);
            if (head->z == (znak*)NULL) {
                free(head);
                return (list*)NULL;
            }
        }
    }

    return head;
}

void printList(list* l) {
    int i;


    if (l == (list*)NULL) {
        printf("\nСписок пуст!\n");
        return;
    }

    printf("\nСписок:\n");
    for (i = 0; l != (list*)NULL; ++i) {
        printf("№%d\nФамилия: %s\n", i + 1, l->z->familiya);
        printf("Знак зодиака: %s\n", l->z->zodiac);
        printf("Дата рождения: %d.%d.%d\n", l->z->date[0], l->z->date[1], l->z->date[2]);
        l = l->next;
    }
}

void findZnak(list* l) {
    char buf[BUF_SIZE] = { '\0' };
    int i;
    int check = 0;


    if (l == (list*)NULL) {
        printf("\nСписок пуст!\n");
        return;
    }

    printf("\nВведите фамилию: ");
    fgets(buf, BUF_SIZE, stdin);
    buf[strlen(buf) - 1] = '\0';

    for (i = 0; l != (list*)NULL; ++i) {
        if (!strcmp(l->z->familiya, buf)) {
            printf("Найдено совпадение:\n");
            printf("№%d\nФамилия: %s\n", i + 1, l->z->familiya);
            printf("Знак зодиака: %s\n", l->z->zodiac);
            printf("Дата рождения: %d.%d.%d\n", l->z->date[0], l->z->date[1], l->z->date[2]);
            check = 1;
        }
        l = l->next;
    }

    if (!check) {
        printf("Записи не найдены\n");
    }
}

void freeList(list* l) {
    list* prev;


    do {
        prev = l;
        l = l->next;
        free(prev->z);
        free(prev);
    } while (l != (list*)NULL);
}

int main() {
    list* l = (list*)NULL;
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
            if (l != (list*)NULL) {
                freeList(l);
            }
            l = initList();
            break;
        case '2':
            printList(l);
            break;
        case '3':
            findZnak(l);
            break;
        case '0':
            if (l != (list*)NULL) {
                freeList(l);
            }
            return 0;
        }
    }

    return 0;
}

