#include<stdio.h>

int main(void){
	printf("This program creates a magic sqaure of a specified size.\n");
	printf("The size must be an odd number between 1 and 99.\n");//introductory message//
	int n,start,row,col;
	for (;;){
		printf("Enter size of magic square: ");
		scanf("%d",&n);
		if((n % 2 != 0)&&(n>0)&&(n<100)){
		       break;
		}
	}		
	int m[n][n];//create an array//
	start = n/2;
	m[0][start] = 1; //place the number 1 in the middle of row 0 //

	int i,next_row,next_col;
	for(i=2,row = 0, col = start;i <= n*n;i++){
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

	int j;                                                                        
    	for (i = 0; i < n; i++) {                                                     
        	for (j = 0; j < n; j++) {                                                 
            		printf("%4d", m[i][j]);                                           
        	}                                                                         
        	printf("\n");                                                             
    	}
	return 0;
}	

		

