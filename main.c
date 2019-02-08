#include <stdio.h>
#include <string.h>

int float_to_int(float src);
int double_to_int(double src);
float int_to_float(int src);
double float_to_double(float src);
float double_to_float(double src);

int main(){
	int num = 0, c = 0;
	float a = 0.0;
	double b = 0.0;
	printf("Which function do you want to test? Enter a number. \n");
	printf("1. float_to_int\n");
	printf("2. double_to_int\n");
	printf("3. int_to_float\n");
	printf("4. float_to_double\n");
	printf("5. double_to_float\n");
	scanf("%d", &num);

	switch(num){
		case 1 :
			printf("input : ");
			scanf("%f", &a);
			printf("mine : %d\n", float_to_int(a));
			printf("cast : %d\n", (int)a);
			break;
		case 2 : 
			printf("input : ");
			scanf("%lf", &b);
			printf("mine : %d\n", double_to_int(b));
			printf("cast : %d\n", (int)b);
			break;
		case 3 :
			printf("input : ");
			scanf("%d", &c);
			printf("mine : %f\n", int_to_float(c));
			printf("cast : %f\n", (float)c);
			break;
		case 4 :
			printf("input : ");
			scanf("%f", &a);
			printf("mine : %lf\n", float_to_double(a));
			printf("cast : %lf\n", (double)a);
			break;
		case 5 :
			printf("input : ");
			scanf("%lf", &b);
			printf("mine : %f\n", double_to_float(b));
			printf("cast : %f\n", (float)b);
			break;
		default : 
			printf("Wrong input! Enter a number between 1 to 5\n");
	}
	return 0;
}