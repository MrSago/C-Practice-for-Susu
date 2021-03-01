
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
	
}

int initZnak(znak** out) {
	znak* z, * tmp;
	void* field_ptr[COUNT_FIELDS];
	char buf[BUF_SIZE] = { '\0' };
	char* ret_ptr = &buf[0];
	int i, j;


	z = (znak*)malloc(sizeof(znak) * MAX_ZNAK);
	if (z == (znak*)NULL) {
		return 0;
	}

	printf("Input data:\n");
	for (i = 0; i < MAX_ZNAK && ret_ptr != (char*)NULL; ++i) {
		field_ptr[FIO_INDEX] = (void*)&z[i].fio[0];
		field_ptr[ZODIAC_INDEX] = (void*)&z[i].zodiac[0];
		field_ptr[DATE_INDEX] = (void*)&z[i].date[0];
		for (j = 0;
				j < COUNT_FIELDS &&
				(ret_ptr = fgets(buf, BUF_SIZE, stdin)) != (char*)NULL;
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

int main() {
	znak* z;


	initZnak(&z);

	return 0;
}

