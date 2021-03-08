
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>


int main() {
	int* mass;
	int* tmp;
	int last_min, count_even, cur;
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
	last_min = 0;
	count_even = 0;
	for (i = 0; i < n; ++i) {
		if (scanf("%d", &cur) != 1) {
			free(mass);
			printf("Error input\n");
			return 0;
		}
		if (cur % 2 == 0 && ++count_even % 2 == 0 && last_min < 0) {
			tmp = (int*)realloc(mass, sizeof(int) * ++n);
			if (tmp == (int*)NULL) {
				printf("Error allocate memory\n");
				return 0;
			}
			mass = tmp;
			mass[i++] = last_min;
			mass[i] = cur;
		}
		if (cur < 0) {
			last_min = cur;
		}
		mass[i] = cur;
	}

	printf("Result #1: ");
	for (i = 0; i < n; ++i) {
		printf("%d ", mass[i]);
	}
	printf("\n");

	for (i = 0; i < n; ++i) {
		if (mass[i] == 0) {
			--n;
			for (j = i; j < n; ++j) {
				mass[j] = mass[j + 1];
			}
			--i;
		}
	}

	tmp = (int*)realloc(mass, sizeof(int) * n);
	if (tmp == (int*)NULL) {
		printf("Error allocate memory\n");
		return 0;
	}
	mass = tmp;

	printf("Result #2: ");
	for (i = 0; i < n; ++i) {
		printf("%d ", mass[i]);
	}
	printf("\n");

	free(mass);
	return 0;
}

