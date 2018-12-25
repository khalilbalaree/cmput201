#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <unistd.h>

int matrix[9][9];
//unsigned int usleep(unsigned int seconds);

int read_data(int argc, char *argv[]);
void solve(int row,int col);

int main(int argc, char *argv[]){
    int row = 0, col=0;
    read_data(argc, argv);
    solve(row,col);
    return 0;
}

int read_data(int argc, char *argv[]){
    FILE *fp;
    int inputfile = 0;
    for (int i = 1; i< argc; i++){
        if (strcmp(argv[i], "-i") == 0){
            inputfile = i+1;
        }
    }
    if (inputfile == 0){
        return -1;
    }
    fp = fopen(argv[inputfile], "r");

    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
           fscanf(fp,"%d",&matrix[i][j]); 
        }
        fscanf(fp, "%*[^\n]");
    }
	fclose(fp);
    //print the unsolved sodoku
    for (int i=0; i<9; i++){
        for(int j=0; j<9; j++){
			if (matrix[i][j] == 0){
				printf("%c",' ');
			}
			else{
				printf("%d", matrix[i][j]);
			}
		}
        printf("\n");
    }
    printf("\n");
    return 0;
}

void solve(int row,int col){
    bool end = true;
    int check[9] = {false}; //recording available numbers

    if (row == 9 && col == 9){  //the whole matrix has been filled then print itself
	//usleep(20000);
		for (int i = 0; i < 9; i++){  
			for (int j = 0; j < 9; j++){ 
				if (matrix[i][j] == 0){
					printf("%c",' ');
				}
				else{
					printf("%d", matrix[i][j]);  
				}  
			}
		printf("\n");  
		}  
	return;
	//printf("\n");
	//fflush(stdout);
	}
			  
    if (matrix[row][col] == 0){  
        for (int k = 0; k < 9; k++){ //checking for row  
            if (matrix[row][k] != 0){  
                check[matrix[row][k] - 1] = true; 
            }  
            if (matrix[k][col] != 0){  //checking for col
                check[matrix[k][col] - 1] = true;  
            }  
        }   
        for (int m = (row / 3) * 3; m < (row / 3) * 3 + 3; m++){  //checking for 3*3 blocks
            for (int n = (col / 3) * 3; n < (col / 3) * 3 + 3; n++){  
                if (matrix[m][n] != 0){
                    check[matrix[m][n] - 1] = true;  
                }  
            }
        }  
        for (int k = 0; k < 9; k++){  
            if (check[k] == false){
                end = false;
            } 
        }
        if (end){ //no available numbers, can not fill in the numbers
            return;
        }  
        else{  
            for (int k = 0; k < 9; k++){  
                if (check[k] == false){    
                    matrix[row][col] = k + 1; // fill in with the numbers in d[]  
                    check[k] = true;  
                    //go to next number  
                    if (col == 8 && row == 8){  
                        col = col + 1;  
                        row = row + 1;  
                    }  
                    else if (col == 8 && row < 8){  
                        col = 0;  
                        row += 1;  
                    }  
                    else if(col < 8 && row <= 8){  
                        col += 1;  
                    }  
                    solve(row, col); //call itself 
                    //cannot fill in the number and jump back 
                    //change back the number to 0
                    if (col == 0){  
                        col = 8;  
                        row -= 1;  
                    }  
                    else{  
                        col--;  
                    }  
                    matrix[row][col] = 0;  
                    check[k] = false;  
                }  
            }  
        }
    }  
    else{  //the number is not zero and directly go to next one
        if (col == 8 && row == 8){  
            col = col + 1;  
            row = row + 1;  
        }  
        else if (col == 8 && row < 8){  
            col = 0;  
            row += 1;  
        }  
        else if (col < 8 && row <= 8){  
            col += 1;  
        }  
        solve(row, col); //call itself
    }     
}