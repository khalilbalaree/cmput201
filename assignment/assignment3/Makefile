mst.h                                                                                               000644  000765  000024  00000000265 13211446246 012716  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                         #ifndef MST_H
#define MST_H
#define MAX(x,y) ((x)>(y)?(x):(y))
extern int num_pt;
extern int outputfile;
void MST(int MAX_X,int MAX_Y,int x_coordinate[],int y_coordinate[]);
#endif
                                                                                                                                                                                                                                                                                                                                           steiner.h                                                                                           000644  000765  000024  00000001043 13212416362 013554  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                         #ifndef STEINER_H
#define STEINER_H
#define MAX(x,y) ((x)>(y)?(x):(y))
#define MIN(x,y) ((x)<(y)?(x):(y))
struct point{
    int index;   //the order in instance file
    int x;
    int y;
    int parent;
    int num_children; //has value 0 -- 8
    int child[8];
    int overlap_hv;  //total overlap when horizntal then vertical
    int overlap_vh;  //total overtap when other way 
};
extern int num_pt;
extern FILE *fp2,*fp1;
void steiner(int outputfile,int parent[],int children[],int x_coordinate[],int y_coordinate[],double length_MST);
#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             ./._main.c                                                                                          000755  000765  000024  00000000414 13212435433 013400  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                             Mac OS X            	   2   �                                           ATTR         �   L                  �     com.apple.lastuseddate#PS       �   <  com.apple.quarantine ��(Z    ��0    q/0083;5a1f497d;Safari;A45436E2-33B3-44D9-8671-F3188BB593D1                                                                                                                                                                                                                                                     main.c                                                                                              000755  000765  000024  00000014512 13212435433 013032  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                         #include <stdio.h>
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






                                                                                                                                                                                      ./._result_1488834.txt                                                                              000644  000765  000024  00000000260 13212454307 015307  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                             Mac OS X            	   2   ~      �                                      ATTR       �   �                     �     com.apple.lastuseddate#PS    �Y*Z    �
�.                                                                                                                                                                                                                                                                                                                                                    result_1488834.txt                                                                                  000644  000765  000024  00000000776 13212454307 014751  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                         n        average_overlap        running_time_for_A2        running_time_for_A3
100          0.10                     0.01s                       0.01s
200          0.10                     0.01s                       0.01s
400          0.09                     0.01s                       0.01s
600          0.09                     0.01s                       0.01s
800          0.09                     0.01s                       0.02s
1000         0.09                     0.01s                       0.02s  mst.c                                                                                               000644  000765  000024  00000007177 13211421347 012715  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                         #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mst.h"
#include"steiner.h"

extern int num_pt;
extern int outputfile;

void MST(int MAX_X,int MAX_Y,int x_coordinate[],int y_coordinate[]){
    /* From Prof. Lin slides Prim's MST algorithm: starting point p[0] */ 
    int i,j;
    int edge[num_pt][num_pt];
    int d[num_pt];

    /*Computing all pairwise distances*/
    for (i = 0; i < num_pt; i++) { 
        for (j = i+1; j < num_pt; j++) { 
            edge[i][j] = edge[j][i] = abs(x_coordinate[i] - x_coordinate[j]) + abs(y_coordinate[i] - y_coordinate[j]); 
        } 
        edge[i][i] = 0; 
    } 
    /*MST algorithm*/
    char color[num_pt];
    int parent[num_pt];
    int children_order[num_pt];
    int num;

    for (int i = 0; i < num_pt; i++) { /* initialization */
        color[i] = 'w';  /* color 'white' stands for outside the tree */
        parent[i] = -1; /*-1 stands for no parent*/
        d[i] = edge[0][i];         
    } 
    
    for (int i= 1;  i < num_pt; i++){
        parent[i] = 0;
    } 

    color[0] = 'b'; /* color the root black*/
    num = 1; 
    int length_MST = 0; 
    int point_added;
    while (num < num_pt) { 
        int min = 2 * (MAX_X + MAX_Y) + 1; 
        for (i = 0; i < num_pt; i++) { /* find the p[i^*] */ 
            if (color[i] == 'w' && d[i] < min) {
                min = d[i]; 
                point_added = i; 
            } 
            else if (color[i] == 'w' && d[i] == min) { /*child tie-breaking rule */ 
                if ((abs(y_coordinate[i] - y_coordinate[parent[i]]) > abs(y_coordinate[point_added]) - y_coordinate[parent[point_added]]) || 
                (abs(y_coordinate[i] - y_coordinate[parent[i]]) == abs(y_coordinate[point_added] - y_coordinate[parent[point_added]]) && 
                (MAX(x_coordinate[i],x_coordinate[parent[i]]) > MAX(x_coordinate[parent[point_added]],x_coordinate[point_added])))||
                ((abs(y_coordinate[i] - y_coordinate[parent[i]]) == abs(y_coordinate[point_added] - y_coordinate[parent[point_added]])) &&
                (MAX(x_coordinate[i], x_coordinate[parent[i]]) == MAX(x_coordinate[parent[point_added]],x_coordinate[point_added]) ) && (i <= point_added))) {
                    min = d[i]; 
                    point_added = i; 
                }
            }
        }
        //printf("%d\t%d\t%d\n",parent[point_added],point_added,min);
        children_order[num] = point_added;

        length_MST += min; 
        color[point_added] = 'b';//color the point
        num++;
        for (i = 0; i < num_pt; i++) { /* updating the distances and parents */ 
            if (color[i] == 'w' && d[i] > edge[i][point_added]) { 
                d[i] = edge[i][point_added]; 
                parent[i] = point_added; 
            } 
            else if (color[i] == 'w' && d[i] == edge[i][point_added]) { /*parent tie-breaking rule */ 
                if ((abs(y_coordinate[i] - y_coordinate[parent[i]]) < abs(y_coordinate[i] - y_coordinate[point_added]))|| 
                (abs(y_coordinate[i] - y_coordinate[parent[i]]) == abs(y_coordinate[i] - y_coordinate[point_added]) && 
                (MAX(x_coordinate[i],x_coordinate[parent[i]]) < MAX(x_coordinate[i],x_coordinate[point_added]))) ||
                (abs(y_coordinate[i] - y_coordinate[parent[i]]) == abs(y_coordinate[i] - y_coordinate[point_added]) &&
                MAX(x_coordinate[i], x_coordinate[parent[i]]) == MAX(x_coordinate[i],x_coordinate[point_added]) && (i <= point_added))){ 
                    parent[i] = point_added; 
                } 
            }
        }
    }
    //Call steiner()
    steiner(outputfile,parent,children_order,x_coordinate,y_coordinate,length_MST);

    return;
}                                                                                                                                                                                                                                                                                                                                                                                                 ./._steiner.c                                                                                       000644  000765  000024  00000000260 13212455471 014125  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                             Mac OS X            	   2   ~      �                                      ATTR       �   �                     �     com.apple.lastuseddate#PS    f*Z    U�=                                                                                                                                                                                                                                                                                                                                                    steiner.c                                                                                           000644  000765  000024  00000021171 13212455471 013557  0                                                                                                    ustar 00zijunwu                         staff                           000000  000000                                                                                                                                                                         //Assignment3 
//Collaborating classmates: Chongzheng Chen & Simon Jang
//Reference: lecture11.pdf
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"steiner.h"
#include"mst.h"

extern int num_pt;
extern FILE *fp2,*fp1;
static int num = 0;
void init_points(struct point p[]){
    for (int i = 0; i < num_pt; i++){
        p[i].index = i;
        p[i].x = -1;
        p[i].y = -1;
        p[i].parent = -1;
        p[i].num_children = 0;
        for(int j = 0; j < 8; j++){
            p[i].child[j] = -1;
        }
        p[i].overlap_hv = -1;
        p[i].overlap_vh = -1;
    }
    return;
}

void print_point_1(struct point p[],int outputfile){
    if (outputfile == 0){
        printf("p[1].index = %d;\n",p[1].index);
        printf("p[1].x = %d;\n",p[1].x);
        printf("p[1].y = %d;\n",p[1].y);
        printf("p[1].parent = %d;\n",p[1].parent);
        printf("p[1].num_children = %d;\n",p[1].num_children);
        if (p[1].num_children == 0){
            printf("p[1].child[8] = {};\n");
        }
        else{
            printf("p[1].child[8] = {");
            int i = 0;
            while(i < p[1].num_children - 1){
                printf("%d,",p[1].child[i]);
                i++;
            }
            printf("%d};\n",p[1].child[i]);
        }
        printf("p[1].overlap_hv = %d;\np[1].overlap_vh = %d;\n\n", p[1].overlap_hv, p[1].overlap_vh);
    }
    else{
        fprintf(fp2,"p[1].index = %d;\n",p[1].index);
        fprintf(fp2,"p[1].x = %d;\n",p[1].x);
        fprintf(fp2,"p[1].y = %d;\n",p[1].y);
        fprintf(fp2,"p[1].parent = %d;\n",p[1].parent);
        fprintf(fp2,"p[1].num_children = %d;\n",p[1].num_children);
        if (p[1].num_children == 0){
            fprintf(fp2,"p[1].child[8] = {};\n");
        }
        else{
            fprintf(fp2,"p[1].child[8] = {");
            int i = 0;
            while(i < p[1].num_children - 1){
                fprintf(fp2,"%d",p[1].child[i]);
                i++;
            }
            fprintf(fp2,"%d};\n",p[1].child[i]);
        }
            fprintf(fp2,"p[1].overlap_hv = -1;\np[1].overlap_vh = -1;\n\n");
    }
    return;
}

void dfs_data(struct point p[],int x_coordinate[],int y_coordinate[],int parent[],int children[]){
    for (int i = 0; i < num_pt; i++){
        p[i].index = i;
        p[i].x = x_coordinate[i];
        p[i].y = y_coordinate[i];
        p[i].parent = parent[i];
        int count = 0;
        for(int j = 1; j < num_pt; j++){
            if (parent[children[j]] == i){
                p[i].child[count] = children[j];
                count++;
            }
        }
        p[i].num_children = count;
    }
    return;
}
void dfs_traversal(struct point p[], int dfs[], int root) {
    dfs[num] = root;
    num++;
    //printf("%d",root);
    if (p[root].num_children == 0) 
        return;
    for (int i = 0; i < p[root].num_children; i++) {
        dfs_traversal(p, dfs, p[root].child[i]);
    }
}

void dfs_order(struct point p[],int dfs[]) {
    dfs_traversal(p, dfs, 0);
    return;
}

void dfs_print(struct point p[],int dfs[],int outputfile){
    if (outputfile == 0){
        for(int i =0;i < num_pt;i++){
            int order = dfs[i];
            printf("p[%d].index = %d,",order,order);
            printf(".num_children = %d",p[order].num_children);
            for(int j = 0; j < p[order].num_children; j++){
                printf(", .child[%d] = %d",j,p[order].child[j]);
            }
            printf("\n");
        }  
        printf("\n");
    }
    else{
        for(int i =0;i < num_pt;i++){
            int order = dfs[i];
            fprintf(fp2,"p[%d].index = %d,",order,order);
            fprintf(fp2,".num_children = %d",p[order].num_children);
            for(int j = 0; j < p[order].num_children; j++){
                fprintf(fp2,", .child[%d] = %d",j,p[order].num_children);
            }
            fprintf(fp2,"\n");
        }  
        fprintf(fp2,"\n");
    }  
}

void reverse_dfs(struct point p[],int dfs[],int rever[]){
    int i = 0;
    for(int pos = num_pt - 1;pos >= 0; pos--){
        rever[i] = dfs[pos];
        i++;
    }
}

int addOverlapBasedOnGroup( int processing_value,int max_value[], int current_overlap){
    int overlap;
    overlap = MIN(processing_value, max_value[0]);
    max_value[0] = MAX(processing_value, max_value[0]);
    return current_overlap + overlap;
}

int calculate_overlap_based_on_combination(struct point points[], int index,int combination[], int p_lay){
    int i, overlap_on_left=0, overlap_on_right=0, overlap_on_top=0, overlap_on_botton=0,max_on_left=0, max_on_right=0, max_on_top=0, max_on_botton=0, sub_overlap=0;
    struct point p=points[index];

    for(i=0; i<p.num_children+1; i++){
        int c_lay = combination[i];
        struct point c = points[(p.child[i])];
        if(i==p.num_children){
            c_lay = (p_lay + 1) % 2;
            if (p.parent!=-1){ 
                c = points[p.parent];
            }
            else{
                break;
            }
        }

        // divided children into 4 groups
        if (c_lay==0 && c.x > p.x) {//right
            overlap_on_right = addOverlapBasedOnGroup(c.x - p.x, &max_on_right, overlap_on_right);
        }
        if (c_lay==0 && c.x <= p.x) {//left
            overlap_on_left = addOverlapBasedOnGroup(p.x - c.x,&max_on_left, overlap_on_left);
        }
        if (c_lay==1 && c.y > p.y){//top
            overlap_on_top = addOverlapBasedOnGroup( c.y - p.y,&max_on_top, overlap_on_top);
        }
        if (c_lay==1 && c.y <= p.y){//botton
            overlap_on_botton = addOverlapBasedOnGroup( p.y - c.y,&max_on_botton, overlap_on_botton);
        }

        // add sub_overlap
        if(c_lay==0 && i!=p.num_children){
            sub_overlap += c.overlap_hv;
        }
        else if (c_lay==1 && i!=p.num_children){
            sub_overlap += c.overlap_vh;
        }
    }

    // printf("Index %d, sub_overlap:%d, p_lay:%d\n", index, sub_overlap, p_lay);
    // printf("Index %d, overlap:%d, p_lay:%d\n", index, overlap_on_left + overlap_on_right + overlap_on_top + overlap_on_botton, p_lay);
    return sub_overlap + overlap_on_left + overlap_on_right + overlap_on_top + overlap_on_botton;
}
int calculateOverlap(struct point points[], int index, int p_lay){
    //p_lay == 0: hv
    //p_lay == 1: vh
    struct point p = points[index];
    int combination[p.num_children], i, overlap=0, new_overlap;
    for(i=0; i<p.num_children; i++){
        combination[i] = 0;
    }

    while (1){
        int is_combination_updated = 1;
        // calculate the overlap based on this combination
        new_overlap = calculate_overlap_based_on_combination(points, index,combination, p_lay);
        overlap = MAX(new_overlap, overlap);

        for(i=0; i<p.num_children; i++){
            combination[i] = (combination[i] + 1) % 2;
            if(combination[i]==0){
                if(i==p.num_children-1){
                    is_combination_updated = 0;
                }
                continue;
            }
            else{
                break;
            }
        }
        // check if combination is updated
        if(!is_combination_updated){
            break;
        }
    }
    return overlap;
}


int addon(struct point p[],int rever[]){
    for(int pos = 0 ;pos < num_pt; pos++) {
    // for(int pos = 0 ;pos < 10; pos++) {
        int i = rever[pos];
        // printf("Index = %d ",i);
        if (p[i].num_children == 0){
            p[i].overlap_hv = 0;
            p[i].overlap_vh = 0;
            // printf("No children\n");
        }
        else{
            p[i].overlap_hv = calculateOverlap(p,i,0);
            p[i].overlap_vh = calculateOverlap(p,i,1);    
        }
    
    }
    return p[0].overlap_vh;
}
 

void final_print(int total_overlap,double length_MST,int outputfile){
    if (outputfile == 0){
        printf("The total overlap is %d\n",total_overlap);
        printf("The reduction rate is %.2f\n",total_overlap/length_MST);
    }
    else{
        fprintf(fp2,"The total overlap is %d\n",total_overlap);
        fprintf(fp2,"The reduction rate is %.2f\n",total_overlap/length_MST);
    }
    fprintf(fp1,"#The total overlap is %d\n",total_overlap);
    fprintf(fp1,"#The reduction rate is %.2f",total_overlap/length_MST);
}


void steiner(int outputfile,int parent[],int children_order[],int x_coordinate[],int y_coordinate[],double length_MST){
    struct point p[num_pt];
    int dfs[num_pt];
    int rever[num_pt];
    int total;
    init_points(p);
    dfs_data(p,x_coordinate,y_coordinate,parent,children_order);
    print_point_1(p,outputfile);
    dfs_order(p,dfs);
    dfs_print(p,dfs,outputfile);
    //total_overlap = reverse_dfs(p,dfs);
    reverse_dfs(p,dfs,rever);
    total = addon(p,rever);
    final_print(total,length_MST,outputfile);
    return;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       