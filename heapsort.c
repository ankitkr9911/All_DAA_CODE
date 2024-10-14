#include<stdio.h>
#include<stdlib.h>

void maxheapify(int arr[],int n,int i)//i is the variable or position from where we have to make it maxheap
{
    int largest = i;//largest index of non-leaf node
    int left = 2*i +1;
    int right = 2*i + 2;

    if(left<=n && arr[left]>arr[largest])
    {
        largest = left;
    }
    if(right<=n && arr[right]>arr[largest])
    {
        largest = right;
    }

    if(largest != i)
    {
        //Swapping arr[largest] and arr[i]
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        maxheapify(arr,n,largest);
    }
}

void heapsort(int arr[],int n)
{
    //Build maxheap first
    for(int i=n/2-1;i>=0;i--) // i=n/2-1 because in a complete binary tree n/2-1 is the index of the last non leaf node.
    {
        maxheapify(arr,n,i);
    } 

    //Deleting the root element after building maxheap
    for(int i=n-1;i>=0;i--)
    {
        //Swapping arr[1] and arr[i]
        int temp  = arr[0];
        arr[0] = arr[i];
        arr[i] =  temp;

        maxheapify(arr,i-1,0);//0 because deletion is happening from the root 
    }   
}

void traversal(int arr[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {12,9, 19, 5, 30};
    printf("Elements of array before sorting: \n");
    traversal(arr,5);
    heapsort(arr,5);
    printf("Elements of the array after sorting:\n");
    traversal(arr,5);
    return 0;
}