#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1000

void random_file_generator(char *filename);
void order_file_generator(char * filename);
void reverse_file_generator(char * filename);
void read_file_in_array(char *filename,int arr[],int size);


void measure_execution_time_quickSort(char* filename,int size);
void measure_execution_time_mergeSort(char* filename,int size);
void measure_execution_time_insertionSort(char* filename,int size);
void measure_execution_time_selectionSort(char* filename,int size);


void insertionSort(int arr[],int size,int* comparisons,int* exchanges);
void selectionSort(int A[],int size,int* comparisons,int* exchanges);
void mergeSort(int A[], int low, int high,int size,int* comparisons,int* exchanges);
void merge(int A[], int mid, int low, int high,int size,int* comparisons,int* exchanges);
int partition(int A[], int low, int high,int* comparisons,int* exchanges);
void quickSort(int A[], int low, int high,int* comparisons,int* exchanges);


int main()
{
    srand(time(NULL)); 
    random_file_generator("random.txt");
    order_file_generator("order.txt");
    reverse_file_generator("reverse.txt");

    printf("Sorting Algorithm\t| File Type\t| Time(s)\t| No.Of Elements\t| Comparisons\t|    Swaps\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");

    int sizes[] = {100, 1000, 5000, 10000};
    for (int i = 0; i < 4; i++) {
        int size = sizes[i];
        measure_execution_time_quickSort("random.txt", size);
        measure_execution_time_quickSort("order.txt", size);
        measure_execution_time_quickSort("reverse.txt", size);
        

        measure_execution_time_mergeSort("random.txt", size);
        measure_execution_time_mergeSort("order.txt", size);
        measure_execution_time_mergeSort("reverse.txt", size);
       
        measure_execution_time_insertionSort("random.txt", size);
        measure_execution_time_insertionSort("order.txt", size);
        measure_execution_time_insertionSort("reverse.txt", size);
        
        measure_execution_time_selectionSort("random.txt", size);
        measure_execution_time_selectionSort("order.txt", size);
        measure_execution_time_selectionSort("reverse.txt", size);
        printf("\n\n");

    }

    return 0;
}

void random_file_generator(char *filename)
{
    FILE *ptr = fopen(filename,"w");
    if(ptr == NULL)
    {
        printf("Error opening file.");
    }

    for(int i=0;i<N;i++)
    {
        fprintf(ptr,"%d ",rand() % 10001);
    }

    fclose(ptr);
}

void order_file_generator(char * filename)
{
    FILE *ptr = fopen(filename,"w");
    if(ptr == NULL)
    {
        printf("Error Opening file.");
    }
    for(int i=1;i<=N;i++)
    {
        fprintf(ptr,"%d ",i);
    }
    fclose(ptr);
}

void reverse_file_generator(char * filename)
{
    FILE * ptr = fopen(filename,"w");
    if(ptr==NULL)
    {
        printf("Error opening file.");
    }

    for(int i=N;i>0;i--)
    {
        fprintf(ptr,"%d ",i);
    }
    fclose(ptr);
}


void read_file_in_array(char *filename,int arr[],int size)
{
    FILE *ptr = fopen(filename,"r");
    if(ptr==NULL)
    {
        printf("Error opening file.");
    }
    for(int i=0;i<size;i++)
    {
        fscanf(ptr,"%d",&arr[i]);
    }
    fclose(ptr);
}

void measure_execution_time_quickSort(char* filename,int size)
{
    int comparisons = 0;
    int exchanges = 0;
    int arr[size];
    read_file_in_array(filename,arr,size);
    clock_t start = clock();
    quickSort(arr,0,size-1,&comparisons,&exchanges);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("quickSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n",filename, time_taken,size,comparisons, exchanges);
}

void measure_execution_time_mergeSort(char* filename,int size)
{
    int comparisons = 0;
    int exchanges = 0;
    int arr3[size];
    read_file_in_array(filename,arr3,size);
    clock_t start = clock();
    mergeSort(arr3,0,size-1,size,&comparisons,&exchanges);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("mergeSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n",filename, time_taken,size,comparisons, exchanges);
}

void measure_execution_time_insertionSort(char* filename,int size)
{
    int comparisons = 0;
    int exchanges = 0;
    int arr1[size];
    read_file_in_array(filename,arr1,size);
    clock_t start = clock();
    insertionSort(arr1,size,&comparisons,&exchanges);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("insertionSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n", filename, time_taken,size,comparisons, exchanges);
}

void measure_execution_time_selectionSort(char* filename,int size)
{
    int comparisons = 0;
    int exchanges = 0;
    int arr2[size];
    read_file_in_array(filename,arr2,size);
    clock_t start = clock();
    selectionSort(arr2,size,&comparisons,&exchanges);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("selectionSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n", filename, time_taken,size,comparisons, exchanges);
}

// it is modifying the original array rather than creating a copy of it.
void insertionSort(int A[],int size,int* comparisons,int* exchanges)
{
    int key,i;
    for(i=1;i<size;i++)
    {
        int j = i-1;
        key = A[i];
        while(j>=0 && A[j]>key)
        {
            (*comparisons)++;
            A[j+1] = A[j];
            j--;
            (*exchanges)++;
        }
        A[j+1] = key;
    }
}

//it modifies the original array directly rather than creating a copy of it.
void selectionSort(int A[],int size,int* comparisons,int* exchanges)
{
    int minIndex;
    for(int i=0;i<size;i++)
    {
        minIndex = i;
        for(int j=i+1;j<size;j++)
        {
            (*comparisons)++;
            if(A[j]<A[minIndex])
            {
                minIndex = j;
            }
        }
        if(minIndex!=i)
        {
            //Swapping A[i] and A[minIndex]
            int temp = A[i];
            A[i] = A[minIndex];
            A[minIndex] = temp;
            (*exchanges)++;
        }
    }
}

// The mergeSort function is sorting the array arr in place, but it does use an auxiliary array B for the merging process.
// The mergeSort function modifies the original array A directly. It does not create a new array that replaces A; it sorts A in place.
void merge(int A[], int mid, int low, int high,int size,int* comparisons,int* exchanges)
{
    int i, j, k, B[size];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high)
    {
        (*comparisons)++;
        if (A[i] < A[j])
        {
            B[k] = A[i];
            i++;
            k++;
        }
        else
        {
            B[k] = A[j];
            j++;
            k++;
        }
        (*exchanges)++;
    }
    while (i <= mid)
    {
        B[k] = A[i];
        k++;
        i++;
        (*exchanges)++;
    }
    while (j <= high)
    {
        B[k] = A[j];
        k++;
        j++;
        (*exchanges)++;
    }
    for (int i = low; i <= high; i++)
    {
        A[i] = B[i];
    }
    
}

void mergeSort(int A[], int low, int high,int size,int* comparisons,int* exchanges){
    int mid; 
    if(low<high){
        mid = (low + high) /2;
        mergeSort(A, low, mid,size,comparisons, exchanges);
        mergeSort(A, mid+1, high,size,comparisons, exchanges);
        merge(A, mid, low, high,size,comparisons, exchanges);
    }
}

//-->The partition function rearranges elements in the array such that elements less than the pivot are on the left and elements greater
// than the pivot are on the right. It then places the pivot in its correct position.
//-->This function modifies the original array directly by swapping elements, not by creating a copy.
int partition(int A[], int low, int high,int* comparisons,int* exchanges)
{
    int pivot = A[low];
    int i = low + 1;
    int j = high;
    int temp;

    do
    {
        while (A[i] <= pivot)
        {
            (*comparisons)++;
            i++;
        }

        while (A[j] > pivot)
        {
            (*comparisons)++;
            j--;
        }

        if (i < j)
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            (*exchanges)++;
        }
    } while (i < j);

    // Swap A[low] and A[j]
    temp = A[low];
    A[low] = A[j];
    A[j] = temp;
    (*exchanges)++;
    return j;
}

void quickSort(int A[], int low, int high,int* comparisons,int* exchanges)
{
    int partitionIndex; // Index of pivot after partition

    if (low < high)
    {
        partitionIndex = partition(A, low, high,comparisons, exchanges); 
        quickSort(A, low, partitionIndex - 1,comparisons, exchanges);  // sort left subarray 
        quickSort(A, partitionIndex + 1, high,comparisons, exchanges); // sort right subarray
    }
}
