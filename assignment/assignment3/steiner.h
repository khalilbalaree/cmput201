#ifndef STEINER_H
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
#endif