#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include"steiner.h"
#include"mst.h"
#define max_num 100

FILE *fp, *fp1, *fp2;
int inputfile = 0, outputfile = 0;
int num_pt;

int main(int argc, char *argv[]) {
    int max_x, max_y;
    int *x_coordinate, *y_coordinate;
    int i;
    int xnum;
    int MAX_X,MAX_Y,NUM_PT,num_of_instances; 
    if (argc == 1) {
        /* to generate random instances, accepting parameters from stdin */
	    printf("Generating random instances...\n");
	    printf("Enter the circuit board size MAX_X MAX_Y: ");
	    scanf("%d%d", &MAX_X, &MAX_Y);
	    printf("Enter the number points NUM_PT: ");
	    scanf("%d",&NUM_PT);
	if (NUM_PT > (MAX_X +1)*(MAX_Y +1)){
        printf("Error in generating instances!\n");
        return -15;
        }
	else if ((NUM_PT < 1) || (NUM_PT > max_num)){
		printf("Error in generating instances!\n");
	}
	printf("Enter the number of random instances to be generated: ");
	scanf("%d",&num_of_instances);

	char filename[max_num];
	srand(time(NULL));
	for (i=1; i<= num_of_instances; i++){
		sprintf(filename,"instance%d_%d.txt",NUM_PT,i);
		fp = fopen(filename,"w");
		if(fp == NULL){
			printf("Error in generating instances!\n");
			/*can't be created*/
			return -14;
		}
		fprintf(fp, "##################################################\n");
	        fprintf(fp, "#%s\n", filename);
        	fprintf(fp, "#area [0, MAX_X] x [0, MAX_Y]\n");
        	fprintf(fp, "%d\t%d\n", MAX_X, MAX_Y);
        	fprintf(fp, "#number of points NUM_PT\n");
       		fprintf(fp, "%d\n", NUM_PT);
      		fprintf(fp, "#coordinates\n");

		x_coordinate = (int *)malloc(num_pt * sizeof(int));
    	y_coordinate = (int *)malloc(num_pt * sizeof(int));
		for (int j = 0; j < NUM_PT; j++){
			x_coordinate[j] = rand() % (MAX_X + 1);
		 	y_coordinate[j] = rand() % (MAX_Y + 1);
			for (int x = j-1 ;x >=0; x--){
				if ((x_coordinate[j] == x_coordinate[x])&&( y_coordinate[j]==y_coordinate[x])){
					x_coordinate[j] = rand() % (MAX_X + 1);
                        		y_coordinate[j] = rand() % (MAX_Y + 1);
				}
			}	
			fprintf(fp,"%d\t%d\n",x_coordinate[j], y_coordinate[j]);
		}
		fclose(fp);
		if (i == num_of_instances){
			printf("%s generated... done!\n",filename);
		}
		else{
			printf("%s generated\n",filename);
		}
        free(x_coordinate);
        free(y_coordinate);
	    
	}
	return 1;
    }
    for (i = 1; i < argc; i++) {
        if (strcmp (argv[i], "-i") == 0)
            inputfile = i+1;
        else if (strcmp (argv[i], "-o") == 0)
            outputfile = i+1;
    }
    if (inputfile == 0) {
        /* invalid command line options */
	printf("%s [-i inputfile [-o outputfile]]\n",argv[0]);
        return -1;
    }
    if ((fp1 = fopen(argv[inputfile], "r+")) == NULL) {
        /* open file error */
	printf("Open file error\n");
        return -2;
    }
    while (fscanf(fp1, "%d", &max_x) != 1) {
        if (ferror(fp1)) {
            /* read error */
	    printf("Error in reading the instance file!\n");
            fclose(fp1);
            return -3;
        }
        if (feof(fp1)) {
            /* no integer to read */
	    printf("Error in reading the instance file!\n");
            fclose(fp1);
            return -4;
        }
        fscanf(fp1, "%*[^\n]"); /* skip the rest of line */
    }
    if (fscanf(fp1, "%d", &max_y) != 1) {
        /* max_y not following max_x */
	printf("Error in reading the instance file!\n");
        fclose(fp1);
        return -5;
    }
    while (fscanf(fp1, "%d", &num_pt) != 1) {
        if (ferror(fp1)) {
            /* read error */
	    printf("Error in reading the instance file!\n");
            fclose(fp1);
            return -6;
        }
        if (feof(fp1)) {
            /* no integer to read */
	    printf("Error in reading the instance file!\n");
            fclose(fp1);
            return -7;
        }
        fscanf(fp1, "%*[^\n]"); /* skip the rest of line */
    }

    x_coordinate = (int *)malloc(num_pt * sizeof(int));
    y_coordinate = (int *)malloc(num_pt * sizeof(int));
    for (i = 0; i < num_pt; i++) {
        while (fscanf(fp1, "%d", &x_coordinate[i]) != 1) {
            if (ferror(fp1)) {
                /* read error */
		printf("Error in reading the instance file!\n");
                fclose(fp1);
                return -8;
            }
            if (feof(fp1)) {
                /* no integer to read */
		printf("Error in reading the instance file!(not enough coordinates)\n");
                fclose(fp1);
                return -9;
            }
            fscanf(fp1, "%*[^\n]"); /* skip the rest of line */
        }
        if (fscanf(fp1, "%d", &y_coordinate[i]) != 1) {
            /* y_coordinate not following x_coordinate */
            printf("Error, y_coordinate not following x_coordinate\n");
            fclose(fp1);
            return -10;
        }
    }
    if (fscanf(fp1, "%d", &xnum) == 1){
	    printf("Error in reading the instance file! (too many coordinates)\n");
	    fclose(fp1);
	    return -12;
    }
    //fclose(fp1);

    for (int j = 0; j < num_pt; j++){
	    for (i = j + 1; i < num_pt; i++){
		    if (x_coordinate[j] == x_coordinate[i]){
			    if (y_coordinate[j] == y_coordinate[i]){
				    /*duplicate coordinate*/
				    printf("Error in reading the instance file (duplicate coordinates)!\n");
			            return -13;	
			    }
		    }
	    }
    }
    fscanf(fp1, "%*[^\n]");

    for (i = 0; i < num_pt; i++){
		if( x_coordinate[i] > max_x ){
			/* coordinate bigger than max*/
		    	printf("Error in reading the instance file! (x_cordinate bigger than max_x)\n");
		return -11;
		}

		else if (y_coordinate[i] > max_y){
			printf("Error in reading the instance file! (y_coordinate bigger than max_y)\n");
		return -11;
		}
    }

    if (outputfile > 0) {
        if ((fp2 = fopen(argv[outputfile], "w")) == NULL) {
        /* open file error */
            printf("No file to write!\n");
            return -2;
        }
        //Call MST()
        MST(max_x, max_y, x_coordinate,y_coordinate);
        fclose(fp2);
    }
    else {
        //Call MST()
        MST(max_x, max_y, x_coordinate,y_coordinate);
    }
    fclose(fp1);
    free(x_coordinate);
    free(y_coordinate);
    return 0; 
}






