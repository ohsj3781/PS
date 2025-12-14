#include <stdio.h>
#include <stdlib.h>

int compare_ints (const void* a, const void* b){
    const int *la = a;
    const int *lb = b;

    return *la == *lb ? 0 : *la < *lb ? -1 : 1;
}



int main(){
    int i;
    int arr[5];

    for(i = 0; i < 5; ++i){
        scanf("%d",arr+i);
    }

    qsort((void*)arr, 5, sizeof(int), compare_ints);

    int sum = 0;
    for(i = 0; i < 5; ++i){
        sum += arr[i];
    }

    printf("%d\n%d", sum / 5, arr[2]);

    return 0;
}