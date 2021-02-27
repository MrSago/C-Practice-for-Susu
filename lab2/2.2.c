
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int main() {
	int* mass;
	int max, min;
	int max_i, min_i;
	int start, end;
	int n, i;


	if (scanf("%d", &n) != 1 || n <= 0) {
		printf("Error input\n");
		return 0;
	}

	mass = (int*)malloc(sizeof(int) * n);
	if (mass == (int*)NULL) {
		printf("Error alocate memory\n");
		return 0;
	}

	for (i = 0; i < n; ++i) {
		if (scanf("%d", &mass[i]) != 1) {
			free(mass);
			printf("Error input\n");
			return 0;
		}
	}

	max = INT_MIN, min = INT_MAX;
    max_i = 0, min_i = 0;
	for (i = 0; i < n; ++i) {
		if (mass[i] > max) {
			max = mass[i];
			max_i = i;
		}
		if (mass[i] < min) {
			min = mass[i];
			min_i = i;
		}
	}
	if (max_i < min_i) {
		start = max_i;
		end = min_i;
	} else {
		start = min_i;
		end = max_i;
	}
	for (i = start + 1; i < end; ++i) {
		if (mass[i] % 2 == 0 && i < n - 1 && mass[i + 1] != 0) {
			mass[i] *= -1;
		}
	}

	for (i = 0; i < n; ++i) {
		printf("%d ", mass[i]);
	}
	printf("\n");

	free(mass);
	return 0;
}

