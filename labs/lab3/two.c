#include<stdio.h>

int main(void){
int a, first, second, third, remain_two_digits;
printf("Enter a three-digit number: ");
scanf("%d",&a);
first = a/100;
remain_two_digits = a%100;
second = remain_two_digits/10;
third = remain_two_digits%10;
printf("The reversal is: %d%d%d \n",third,second,first);
return 0;
}
