#include<stdio.h>

int main(void)
{
	float loan,rate,monthly_payment,monthly_rate,first,second,third;
	printf("Enter amount of loan: ");
	scanf("%f",&loan);
	printf("Enter interest rate: ");
	scanf("%f",&rate);
	printf("Enter monthly payment: ");
	scanf("%f",&monthly_payment);
	
	monthly_rate = rate/12/100;
	first = (loan - monthly_payment)*(1 + monthly_rate);
	second = (first - monthly_payment)*(1 + monthly_rate);
	third = (second - monthly_payment)*(1 + monthly_rate);

	printf("\nBalance remaining after first payment: $%.2f\n",first);
	printf("Balance remaining after second payment: $%.2f\n",second);
	printf("Balance remaining after third  payment: $%.2f\n",third);

	return 0;
}
