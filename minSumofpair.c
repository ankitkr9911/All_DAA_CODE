#include<stdio.h>

int partition(int A[], int low, int high)
{
    int pivot = A[low];
    int i = low + 1;
    int j = high;
    int temp;

    do
    {
        while (A[i] <= pivot)
        {
            i++;
        }

        while (A[j] > pivot)
        {
            j--;
        }

        if (i < j)
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    } while (i < j);

    // Swap A[low] and A[j]
    temp = A[low];
    A[low] = A[j];
    A[j] = temp;
    return j;
}

void quickSort(int A[], int low, int high)
{
    int partitionIndex; // Index of pivot after partition

    if (low < high)
    {
        partitionIndex = partition(A, low, high); 
        quickSort(A, low, partitionIndex - 1);  // sort left subarray 
        quickSort(A, partitionIndex + 1, high); // sort right subarray
    }
}

void traversal(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        if(i!=size-1) printf("%d , ",arr[i]);
        else printf(" %d",arr[i]);
        
    }
    printf("\n");
}

void traverse2D(int arr[][2],int size1)
{
    for(int i=0;i<size1;i++)
    {
        for(int j=0;j<2;j++)
        {
            if(j!=1) printf("(%d ,",arr[i][j]);
            
            if(j==1) printf(" %d)",arr[i][j]);
        }
        printf("\n");
    }
}

void minSumOfPairs(int arr[],int size){
    int low =0;
    int high = size-1;
    quickSort(arr,low,high);

    int B[size/2][2];
    for(int i=0;i<size/2;i++){
        B[i][0] = arr[i];
        B[i][1] = arr[size-1-i];
    }

    printf("Optimized list of partitions are:\n");
    traverse2D(B,size/2);

    int storeSum[size/2];
    for(int i=0;i<size/2;i++)
    {
        storeSum[i] = B[i][0] + B[i][1];
    }
    int max = 0;
    for(int i=0;i<size/2;i++)
    {
        if(storeSum[i]>max)
        {
            max = storeSum[i];
        }
    }
    printf("The sum of different partitions are :");
    traversal(storeSum,size/2);

    printf("Maximum sum of the minimized pairs of partition: %d\n",max);
}

int main()
{
    int sequences[] = {1,3,5,9};
    minSumOfPairs(sequences,4);

    return 0;
}