#include<stdio.h>
#include<stdbool.h>
#define max 100

void get_char(char *str)
{	
	//int i = 0; 
	char *p;
	char ch;
	p = str;
	printf("Enter a message:\n");
	while ((ch = getchar()) != '\n'){
		if ((ch>='a')&&(ch <= 'z')){
			*p++ = ch - 32;
		}
		if ((ch >= 'A')&&(ch <= 'Z')){
			*p++ = ch;
		}
	}
	return;
}

bool is_palindrome(char *message){
	char *p,*q;
	p=message;
	q=message;
	while ( *q != '\0'){
		q++;
	}
	while(p<q){
		q--;
		if (*p != *q){
			return false;
		}
		p++;
	}
	return true; 
}

int main()
{ 
	char str[max];
	get_char(str);
	if (is_palindrome(str)){
		printf("Palindrome\n");
	}
	else{
		printf("Not a Palindrome\n");
	}
	return 0;
}

