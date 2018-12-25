#include<stdio.h>

int main(void){
	int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p;
	printf("Enter the number from 1 to 16 in any order: ");
	scanf("%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",&a,&b,&c,&d,&e,&f,&g,&h,&i,&j,&k,&l,&m,&n,&o,&p);
	printf("%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n%d %d %d %d\n",a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
	
	printf("\nRow sums:%4d%4d%4d%4d\n",a+b+c+d,e+f+g+h,i+j+k+l,m+n+o+p);
	printf("Column sums:%4d%4d%4d%4d\n",a+e+i+m,b+f+j+n,c+g+k+o,d+h+l+p);
	printf("Diagonal sums:%4d%4d \n",a+f+k+p,d+g+j+m);
	return 0;
	
}

