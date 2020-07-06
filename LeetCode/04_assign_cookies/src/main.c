#include <stdio.h>

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 

int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] < pivot) 
        { 
            i++;
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 

void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

int findContentChildren(int* g, int gSize, int* s, int sSize){
    quickSort(g, 0, gSize-1);
    quickSort(s, 0, sSize-1);

    int si = 0; // cookie
    int gi = 0; // child
    int satisfied = 0;

    while (si < sSize && gi < gSize) {
        if (s[si] >= g[gi]) {
            gi++;
            si++;
            satisfied++;
        }
        else si++;
    }

    return satisfied;
}

int main() {

    int greed[] = {10, 9, 8, 7};
    int cookies[] = {5, 6, 7, 8};

    printf("out = %d\n", findContentChildren(greed, 4, cookies, 4));

	return 0;
}