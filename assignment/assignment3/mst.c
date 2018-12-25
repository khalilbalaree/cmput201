#include<stdio.h>
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
}