#include<stdio.h>

int median(int A[],int i,int r,int k,int size)
{
    int ind = r-i+1;
    int index = rand()%ind;
    int p,j=0,m=0,n=0;
    int S1[10],S2[10],S3[1];

    if(size==1)
    {
        return A[0];
    }

    for(p=0;p<=r;p++)
    {
        if(A[p]<A[index])
        {
            S1[j] = A[p];
            j++;
        }
        else if(A[p]==A[index])
        {
            S2[n] = A[p];
            n++;
        }
        else{
            S3[m] = A[p];
            m++;
        }
    }  

    if(j>=k)
    {
        return median(S1,i,index-1,k,j);
    }
    else if(j+n>=k){
        return A[index];
    }
    else{
        return median(S3,index+1,size-1,k-j-n,m);
    }
}

// select(k,s)
// {
//     if |s| ==1
//     return single element in s
//     else if(|s1| >=k) then return select(k,s1)
//     else if(|s1|+|s2| >=k) then return a
//     else return select(k-|s1|-|s2|,s3)
// }

int main()
{
    int arr[] =  {7,10,4,3,20,15,8,12,6};
    int size = sizeof(arr)/sizeof(arr[0]);
    int k=4;
    int element = median(arr,0,size-1,k,size);

    printf("Kth Smallest element is : %d",element);
    return 0;                           
}

