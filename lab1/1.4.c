
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <stdlib.h>


int main() {
	int* mass = (int*)NULL;
	int* tmp;
	int count = 0;
	int d;
	int res;


	while (1) {
		if (scanf("%d", &d) != 1) {
			printf("Error input\n");
			if (mass != (int*)NULL) {
				free(mass);
			}
			return 0;
		}
		if (d == 0) {
			break;
		}

		tmp = (int*)realloc(mass, sizeof(int) * ++count);
		if (tmp == (int*)NULL) {
			if (mass != (int*)NULL) {
				free(mass);
			}
			printf("Error allocate memory\n");
			return 0;
		}
		mass = tmp;

		mass[count - 1] = d;
	}
	if (count == 0) {
		printf("Mass is empty\n");
		return 0;
	}

	res = 1;
	while(count--) {
		d = mass[count];
		if (d >= -34 && d <= 90) {
			res *= d;
		}
	}
	printf("%d\n", res);

	free(mass);
	return 0;
}

