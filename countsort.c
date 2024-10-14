#include<stdio.h>
#include<stdlib.h>

void countSort(int arr[],int size)
{

    int max = arr[0];//-->O(1)
    //Finding the max element-->O(n)
    for(int i=1;i<size;i++)
    {
        if(arr[i]>max)
        {
            max = arr[i];
        }
    }

    //Initialising the count array with 0 -->O(k) where k is the value of the max element
    int B[max+1];
    for(int i=0;i<max+1;i++)
    {
        B[i] = 0;
    }

    //inserting values in the count array or counting the occurrences -->O(n)
    //We need to traverse the original array
    for(int i=0;i<size;i++)
    {
        B[arr[i]]++;
    }

    //reinserting the values in the array
    //We need to traverse the count array
    int j=0;
    for(int i=0;i<max+1;i++)
    {
        while(B[i]!=0) //Check until it becomes zero! that is why using while not if
        {
            arr[j] = i;
            j++;
            B[i]--;
        }
    }

    //The outer loop runs k+1 times and while loop runs a number of times equals to the no of elements n.
    //Hence Total time complexity O(n+k)

    // final time complexity of countSort: O(n+k)
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
    int arr[] ={45,11,21,12, 8, 7};
    int size = sizeof(arr)/sizeof(arr[0]);

    traversal(arr,size);

    countSort(arr,size);

    traversal(arr,size);

    return 0;

    
}