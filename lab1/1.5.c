
#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
#endif //_MSC_VER

#include <stdio.h>
#include <math.h>


int main() {
	double sum, f, s;
	int n, i, j;


	if (scanf("%d", &n) != 1) {
		printf("Error input\n");
		return 0;
	}

	sum = 0.0;
	for (i = 1; i <= n; ++i) {
		f = 0.0;
		s = 0.0;
		for (j = 1; j <= i; ++j) {
			f += cos((double)j);
			s += sin((double)j);
		}
		sum += f/s;
	}
	printf("%lf\n", sum);

	return 0;
}

