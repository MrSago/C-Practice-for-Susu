
#ifdef _MSC_VER
    #define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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

    printf("������� ������:\n");
    printf("1.�������\n");
    printf("2.���� �������\n");
    printf("3.���� ��������\n");

    for (i = 0;
            i < MAX_ZNAK &&
            ret_ptr != (char*)NULL;
        ++i
    ) {
        printf("\n%d ������\n", i + 1);
        z = (znak*)malloc(sizeof(znak));
        if (z == (znak*)NULL) {
            return head;
        }
        field[FAMILIYA_INDEX] = (void*)z->familiya;
        field[ZODIAC_INDEX] = (void*)z->zodiac;
        field[DATE_INDEX] = (void*)z->date;
        for (j = 0;
                j < COUNT_FIELDS &&
                (ret_ptr = fgets(buf, BUF_SIZE, stdin)) != (char*)NULL;
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
        if (ret_ptr != (char*)NULL) {
            pushZnak(head, z);
            while (head->prev != (list*)NULL) head = head->prev;
        } else {
            free(z);
        }
    }


    
    return head;
}

void printList(list* l) {
    int i;


    if (l == (list*)NULL) {
        printf("\n������ ����!\n");
        return;
    }

    printf("\n������:\n");
    for (i = 0; l != (list*)NULL; ++i) {
        printf("�%d\n�������: %s\n", i + 1, l->z->familiya);
        printf("���� �������: %s\n", l->z->zodiac);
        printf("���� ��������: %d.%d.%d\n", l->z->date[0], l->z->date[1], l->z->date[2]);
        l = l->next;
    }
}

void findZnak(list* l) {
    char buf[BUF_SIZE] = { '\0' };
    int i;
    int check = 0;


    if (l == (list*)NULL) {
        printf("\n������ ����!\n");
        return;
    }

    printf("\n������� �������: ");
    fgets(buf, BUF_SIZE, stdin);
    buf[strlen(buf) - 1] = '\0';

    for (i = 0; l != (list*)NULL; ++i) {
        if (!strcmp(l->z->familiya, buf)) {
            printf("������� ����������:\n");
            printf("�%d\n�������: %s\n", i + 1, l->z->familiya);
            printf("���� �������: %s\n", l->z->zodiac);
            printf("���� ��������: %d.%d.%d\n", l->z->date[0], l->z->date[1], l->z->date[2]);
            check = 1;
        }
        l = l->next;
    }

    if (!check) {
        printf("������ �� �������\n");
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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    list* l = (list*)NULL;
    char c;


    while (1) {
        printf("\n����\n");
        printf("1.���� ������\n");
        printf("2.����� ������\n");
        printf("3.����� �� �������\n");
        printf("0.�����\n");

        c = getchar();
        while (getchar() != '\n');
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

