
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>


int main() {
	int** matrix;
	int* res;
	int count;
	int prod;
	int n = 0, i, j, k, l, s;


	printf("Welcome to lab 2.4\n");

	printf("Enter n: ");
	if (scanf("%d", &n) != 1 || n <= 0) {
		printf("Error input\n");
		return 0;
	}

	matrix = (int**)malloc(sizeof(int*) * n);
	if (matrix == (int**)NULL) {
		printf("Error allocate memory\n");
		return 0;
	}

	printf("Enter matrix(%d)(%d):\n", n, n);
	for (i = 0; i < n; ++i) {
		matrix[i] = (int*)malloc(sizeof(int) * n);
		if (matrix[i] == (int*)NULL) {
			free(matrix);
			printf("Error allocate memory\n");
			return 0;
		}
		for (j = 0; j < n; ++j) {
			if (scanf("%d", &matrix[i][j]) != 1) {
				for (k = 0; k <= i; ++k) {
					free(matrix[k]);
				}
				free(matrix);
				printf("Error input\n");
				return 0;
			}
		}
	}

	count = n*2 - 1;
	res = (int*)malloc(sizeof(int) * count);
	if (res == (int*)NULL) {
		for (i = 0; i < n; ++i) {
			free(matrix[i]);
		}
		free(matrix);
		printf("Error allocate memory\n");
		return 0;
	}

	for (
		i = 0, j = count - 1;
		i < n - 1;
		++i, --j
	) {
		prod = 1;
		for (
			s = 0, k = i;
			s <= i;
			++s, --k
		) {
			prod *= matrix[s][k];
		}
		res[i] = prod;

		prod = 1;
		for (
			l = 0, s = n - 1 - i, k = n - 1;
			l <= i;
			++l, ++s, --k
		) {
			prod *= matrix[s][k];
		}
		res[j] = prod;
	}

	prod = 1;
	for (i = 0, j = n - 1; i < n; ++i, --j) {
		prod *= matrix[i][j];
	}
	res[n - 1] = prod;

	printf("Result: ");
	for (i = 0; i < count; ++i) {
		printf("%d ", res[i]);
	}
	printf("\n");

	while (n--) {
		free(matrix[n]);
	}
	free(matrix);
	free(res);
	return 0;
}

