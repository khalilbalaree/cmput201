#include<stdio.h>

int main(void)
{
 	float  x, result;
	printf("Enter a value: ");
	scanf("%f",&x);
	result = 3*x*x*x*x*x + 2*x*x*x*x - 5*x*x*x - x*x + 7*x - 6;	
	printf("The result is: %.2f \n",result);
	return 0;


}
