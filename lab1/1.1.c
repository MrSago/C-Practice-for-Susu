
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <math.h>

#ifndef M_PI
	#define M_PI (acos(-1))
#endif //M_PI


int main() {
	double x, y, z;


	printf("Welcome to lab 1.1\n");

	printf("Enter x y z: ");
	if (scanf("%lf%lf%lf", &x, &y, &z) != 3) {
		printf("Error with input\n");
		return 0;
	}

	printf(\
		"a = %lf\nb = %lf\n",\
		(2.0*cos(x-M_PI/4.0)) / (0.5+pow(sin(y),2.0)) + (acos(x+M_PI/2.0)),\
		1.0 + (pow(z,2.0)) / (3+pow(z,2.0)/5.0)\
	);

	return 0;
}

