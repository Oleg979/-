#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double root(double (*func)(double x), double a, double b, double eps) {
	if(func(a) * func(b) >=0) exit(0);

	double left, right, mid, buf;
	int desc = func(a) > 0 ? 1 : 0;
	left = a; right = b;
	do {
		mid = (right + left)*0.5;
		printf("(%lf + %lf) / 2 = %lf\n",left, right, mid);
		buf = func(mid);
		printf("%lf > %lf? %s\n", buf, eps, (fabs(buf) >= eps ? "yes" : "no") );
		if(buf > 0) {
			!desc ? right = mid : left = mid;
		}
		else if(buf < 0) {
			!desc ? left = mid : right = mid;
		}	
	} while (fabs(buf) >= eps);
	
	return mid;
	
}

int main() {
	printf("%lf", root(&sin, 1, 4, 1.0e-6));
}
