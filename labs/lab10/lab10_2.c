#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TOTALWORDS 10
#define LENGTH 20

int read_line(char str[],int n);
void quicksort(char *a[],int low, int high);
int split(char *a[], int low, int high);
int main(void){
    char *words[LENGTH];
    char word[TOTALWORDS +1];
    int i = 0,j = 0,length, index = 0;
    for (;;){
        if(index == LENGTH){
            printf("\nNo Space...\n");
            break;
        }
        printf("Enter word:");
        length = read_line(word,TOTALWORDS);
        if (length == 0){
            break;
        }
        words[j] = (char *)malloc(strlen(word)+1);
        if(words[j] == NULL){
            printf("\nmalloc failed %d of words!\n",index);
            exit(EXIT_FAILURE);
        }
        strcpy(words[j],word);
        index++;
        j++;
    }
    quicksort(words,0,index - 1);
    for(i = 0; i < index;i++){
        printf("%s\n",words[i]);
    }
    for(i = 0; i < index;i++){
        free(words[i]);
    }
    return 0;

}

int read_line(char str[],int n){
    int ch, i = 0;
    while ((ch = getchar()) != '\n'){
        if(i<n){
            str[i++] = ch;
        }
    }
    str[i] = '\0';
    return i; 
}

void quicksort(char *a[],int low, int high)
{
    int middle;
    if (low >= high){ 
        return;
    }
    middle = split(a, low, high);
    quicksort(a, low, middle - 1);
    quicksort(a, middle + 1, high);
}

int split(char *a[], int low, int high)
{
    char *part_element = a[low];
    for(;;){
        while (low < high && strcmp(part_element,a[high])<=0){
            high--;
        }
        if(low >= high){
            break;
        }
        a[low++] = a[high];
        while (low < high && strcmp(a[low],part_element)<=0){
            low++;
        }
        if (low >= high){
            break;
        }
        a[high--] = a[low]; 
    }
    a[high] = part_element;
    return high;
}