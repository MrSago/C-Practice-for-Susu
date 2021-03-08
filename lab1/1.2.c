
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <math.h>


int main() {
	double a, b, c, D, sqrtD, x1, x2;


	printf("Welcome to lab 1.2\n");

	printf("Enter a b c: ");
	if (scanf("%lf%lf%lf", &a, &b, &c) != 3 || a == 0.0) {
		printf("Error with input\n");
		return 0;
	}

	D = b*b - 4.0*a*c;
	if (D == -0.0) {
		D = 0.0;
	}

	if (D < 0.0) {
		printf("No roots\n");
	} else if (D == 0.0) {
		x1 = -b/(2.0*a);
		if (x1 == -0.0) {
			x1 = 0.0;
		}
		printf("Have 1 root:\n%lf\n", x1);
	} else {
		sqrtD = sqrt(D);
		x1 = (-b+sqrtD)/(2.0*a);
		x2 = (-b-sqrtD)/(2.0*a);
		if (x1 == -0.0) {
			x1 = 0.0;
		}
		if (x2 == -0.0) {
			x2 = 0.0;
		}
		printf("Have 2 roots:\n%lf %lf\n", x1, x2);
	}

	return 0;
}

