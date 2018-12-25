//Assignment3 
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
 

void final_print(int total_overlap,double length_MST,int outputfile,FILE *fp3){
    if (outputfile == 0){
        // printf("The total overlap is %d\n",total_overlap);
        printf("The reduction rate is %.2f\n",total_overlap/length_MST);
    }
    else{
        //fprintf(fp2,"The total overlap is %d\n",total_overlap);
        fprintf(fp3,"The reduction rate is %.2f\n",total_overlap/length_MST);
    }
    // fprintf(fp1,"#The total overlap is %d\n",total_overlap);
    // fprintf(fp1,"#The reduction rate is %.2f",total_overlap/length_MST);
}


void steiner(int outputfile,int parent[],int children_order[],int x_coordinate[],int y_coordinate[],double length_MST){
    struct point p[num_pt];
    int dfs[num_pt];
    int rever[num_pt];
    FILE *fp3;
    int total;
    if ((fp3 = fopen("output.txt","w")) == NULL){
        printf("open fp3 error");
        return;
    }
    init_points(p);
    dfs_data(p,x_coordinate,y_coordinate,parent,children_order);
    //print_point_1(p,outputfile);
    dfs_order(p,dfs);
    //dfs_print(p,dfs,outputfile);
    //total_overlap = reverse_dfs(p,dfs);
    reverse_dfs(p,dfs,rever);
    total = addon(p,rever);
    final_print(total,length_MST,outputfile,fp3);
    fclose(fp3);
    return;
}
