
#include <stdio.h>


int main() {
	int sum, i;


	printf("Welcome to lab 1.3\n");

	printf("Result: ");
	for (i = 10; i <= 99; ++i) {
		sum = i / 10 + i % 10;
		if (sum * (1 + sum) == i) {
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}

