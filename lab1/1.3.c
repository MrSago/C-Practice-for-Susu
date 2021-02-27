
#include <stdio.h>


int main() {
	int sum, f, s, i;


	for (i = 10; i <= 99; ++i) {
		f = i / 10;
		s = i % 10;
		sum = f + s;
		if (sum * (1 + sum) == i) {
			printf("%d ", i);
		}
	}
	printf("\n");

	return 0;
}

