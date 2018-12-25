#include<stdio.h>

void create_magic_square(int n, char m[99][99]){
	int start,row,col;
        start = n/2;
        m[0][start] = 1; //place the number 1 in the middle of row 0 //

        int next_row,next_col;
        for(int i=2,row = 0, col = start;i <= n*n;i++){
                if ((row-1) < 0){
                        next_row = n-1;
                }
                else{
                        next_row = row-1;
                }
                if ((col + 2) > n ){
                        next_col = 0;
                }
                else{
                        next_col = col + 1;
                }

                if (m[next_row][next_col] == 0){
                        m[next_row][next_col] = i;
                        row = next_row;
                        col = next_col;
                }
                else{
                        if (row > (n-1)){
                                row = 0;
                                m[row][col] =i;
                        }
                        else{
                                row++;
                                m[row][col] =i;
                        }
                }
	}
}

void print_magic_square(int n, char m[99][99]){
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        printf("%4d", m[i][j]);
                }
                printf("\n");
        }
}


int main(void){
        printf("This program creates a magic sqaure of a specified size.\n");
        printf("The size must be an odd number between 1 and 99.\n");//introductory message//
   	int n;
        while (1){
                printf("Enter size of magic square: ");
                scanf("%d",&n);
                if((n % 2 != 0)&&(n>0)&&(n<100)){
                       break;
                }
        }
	char magic[99][99];
	create_magic_square(n, magic);
	print_magic_square(n, magic);
	return 0;
}
