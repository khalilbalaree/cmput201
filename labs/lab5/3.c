#include<stdio.h>
void pb(int n){
        if (n != 0){
                pb(n /2 );
		/*printf("the value n:%d\n",n);*/
                putchar('0' + n%2);
        }
}

int main(){
	int n;
	printf("To input a decimal you want to convert into a binay one: ");
	scanf("%d",&n);
	pb(n);

}
