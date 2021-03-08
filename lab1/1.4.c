
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>


int main() {
	int n = 0, prod = 1, flag = 0, ret;


	printf("Welcome to lab 1.4\n");

	printf("Enter array (0 end): ");
	while ((ret = scanf("%d", &n)) == 1 && n != 0) {
		if (n >= -39 && n <= 90) {
			prod *= n;
			flag = 1;
		}
	}
	if (ret != 1) {
		printf("Error with input\n");
	} else {
		printf("Product in range [-39; 90] = %d\n", prod * flag);
	}

	return 0;
}

