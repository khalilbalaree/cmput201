#include<stdio.h>
void swap(int* a,int *b);
void build_heap(int *a,int size);
void heapfiy(int *a,int size,int n);
void heapsort(int*a,int size);
int main(){
    int size;
    printf("Enter the number of integers: ");
    scanf("%d",&size);
    int a[size];
    printf("Enter the %d number to be sorted: ",size);
    for (int i = 0; i < size;i++){
        scanf("%d",&a[i]);
    }
    heapsort(a,size);
    printf("In sorted ascending order: ");
    for (int i = 0; i < size; i++){
        printf("%d ",a[i]);
    }
    return 0;
}

void swap(int* a,int *b)
{
	int swap;
	swap = *a;
	*a = *b;
	*b = swap;
    return;
}
void build_heap(int *a,int size)
{
	int k;
	for (k = size;k>=0;k--){
		heapfiy(a,size,k);
    }
    return;
}
void heapfiy(int *a,int size,int n)
{
	int left = 2*n+1;
	int right = 2*n+2;
	int max = n;
	if (left<=size && a[n] < a[left])
		max = left;
	if (right<=size && a[max] < a[right])
		max = right;
	if (max!=n)
	{
		swap(&a[max],&a[n]);
		heapfiy(a,size,max);
	}
    return;
	
}
void heapsort(int*a,int size)
{
	build_heap(a,size);
	while (size>0)
	{
		swap(&a[0],&a[size--]);
		heapfiy(a,size,0);
	}
    return;
}

