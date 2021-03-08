
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <math.h>


int main() {
	double sum = 1.0; //i=0
	double next = -2.0; //i=1
	int i = 1, p = -2, f = 1;
	double eps;


	printf("Welcome to lab 1.6\n");

	printf("Enter eps: ");
	if (scanf("%lf", &eps) != 1 || eps <= 0.0) {
		printf("Error input\n");
		return 0;
	}

	do {
		sum += next;
		p *= -2;
		f *= ++i;
		next = (double)p / (double)f;
	} while (fabs(next) > eps);

	printf("%.8lf\n", sum);

	return 0;
}

