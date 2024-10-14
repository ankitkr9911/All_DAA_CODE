#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 10000

void random_file_generator(char *filename);
void order_file_generator(char * filename);
void reverse_file_generator(char * filename);
void read_file_in_array(char *filename,int arr[],int size);

void measure_execution_time_countSort(char* filename,int size);
void measure_execution_time_radixSort(char* filename,int size);
void measure_execution_time_bucketSort(char* filename,int size);

int getMax(int arr[],int size,int* comparisons);
void countingSort(int arr[],int size,int place,int* comparisons,int* swaps);

void countSort(int arr[],int size,int* comparisons,int* swaps);
void radixSort(int arr[],int size,int* comparisons,int* swaps);
void bucketSort(int arr[],int size,int* comparisons,int* swaps);

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
        measure_execution_time_countSort("random.txt", size);
        measure_execution_time_countSort("order.txt", size);
        measure_execution_time_countSort("reverse.txt", size);
        

        measure_execution_time_radixSort("random.txt", size);
        measure_execution_time_radixSort("order.txt", size);
        measure_execution_time_radixSort("reverse.txt", size);
       
        measure_execution_time_bucketSort("random.txt", size);
        measure_execution_time_bucketSort("order.txt", size);
        measure_execution_time_bucketSort("reverse.txt", size);
        printf("\n");

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

void measure_execution_time_countSort(char* filename,int size)
{
    int comparisons = 0;
    int swaps = 0;
    int arr[size];
    read_file_in_array(filename,arr,size);
    clock_t start = clock();
    countSort(arr,size,&comparisons,&swaps);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("countSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n",filename, time_taken,size,comparisons,swaps);
}

void measure_execution_time_radixSort(char* filename,int size)
{
    int comparisons = 0;
    int swaps = 0;
    int arr3[size];
    read_file_in_array(filename,arr3,size);
    clock_t start = clock();
    radixSort(arr3,size,&comparisons,&swaps);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("radixSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n",filename, time_taken,size,comparisons, swaps);
}

void measure_execution_time_bucketSort(char* filename,int size)
{
    int comparisons = 0;
    int swaps = 0;
    int arr1[size];
    read_file_in_array(filename,arr1,size);
    clock_t start = clock();
    bucketSort(arr1,size,&comparisons,&swaps);
    clock_t stop = clock();

    double time_taken = ((double)(stop - start)) / CLOCKS_PER_SEC;
    
    printf("bucketSort\t\t%s\t%.6fsec\t\t%d\t\t\t%d\t\t%d\t\n", filename, time_taken,size,comparisons, swaps);
}


void countSort(int arr[],int size,int *comparisons,int *swaps)
{

    int max = arr[0];//-->O(1)
    (*comparisons)++;
    //Finding the max element-->O(n)
    for(int i=1;i<size;i++)
    {
        (*comparisons)++;
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
            (*swaps)++;
        }
    }

}

void countingSort(int array[], int n, int place,int* comparisons,int *swaps) {
    int output[n];
    int count[10] = {0};
    // Calculate count of elements
    for (int i = 0; i < n; i++) {
        int index = (array[i] / place) % 10;
        count[index]++;
    }
    // Calculate cumulative count
    for (int i = 1; i < 10; i++) {
        (*comparisons)++;
        count[i] += count[i - 1];
    }
    // Place the elements in sorted order
    for (int i = n - 1; i >= 0; i--) {
        int index = (array[i] / place) % 10;
        output[count[index] - 1] = array[i];
        count[index]--;
        (*swaps)++;
    }
    // Copy the sorted elements into original array
    for (int i = 0; i < n; i++) {
        array[i] = output[i];
        (*swaps)++;
    }
}

void radixSort(int array[], int n,int* comparisons,int* swaps) {
    // Get maximum element
    int maxElement = getMax(array, n,comparisons);
    // Apply counting sort to sort elements based on place value
    for (int place = 1; maxElement / place > 0; place *= 10) {
        countingSort(array, n, place,comparisons,swaps);
    }
}

void bucketSort(int a[], int n,int* comparisons,int* swaps)  
{  
  int max = getMax(a, n,comparisons); //max is the maximum element of array 
  (*comparisons)++;

  int bucket[max], i;  
  for (int i = 0; i <= max; i++)  
  {  
    bucket[i] = 0;  
  }  
  for (int i = 0; i < n; i++)  
  {  
    bucket[a[i]]++;  
  }  
  for (int i = 0, j = 0; i <= max; i++)  
  {  
    while (bucket[i] > 0)  
    {  
      a[j++] = i;  
      bucket[i]--;  
      (*swaps)++;
    }  
  }  
} 

int getMax(int a[], int n,int* comparisons) // function to get maximum element from the given array  
{  
  int max = a[0];  
  for (int i = 1; i < n; i++) 
  {
    (*comparisons)++;
    if(a[i] > max)  
      {
        max = a[i]; 
      }
  } 
  return max;  
}  

//---------------------------------------COUNT SORT---------------------------------------
// void countSort(int a[], int n) // function to perform counting sort  
// {  
//    int output[n+1];  
//    int max = getMax(a, n);  
//    int count[max+1]; //create count array with size [max+1]  
  
  
//   for (int i = 0; i <= max; ++i)   
//   {  
//     count[i] = 0; // Initialize count array with all zeros  
//   }  
    
//   for (int i = 0; i < n; i++) // Store the count of each element  
//   {  
//     count[a[i]]++;  
//   }  
  
//    for(int i = 1; i<=max; i++)   
//       count[i] += count[i-1]; //find cumulative frequency  
  
//   /* This loop will find the index of each element of the original array in count array, and 
//    place the elements in output array*/  
//   for (int i = n - 1; i >= 0; i--) {  
//     output[count[a[i]] - 1] = a[i];  
//     count[a[i]]--; // decrease count for same numbers  
// }  
  
//    for(int i = 0; i<n; i++) {  
//       a[i] = output[i]; //store the sorted elements into main array  
//    }  
// }  

//---------------------------------RADIX SORT---------------------------------------

// void countingSort(int a[], int n, int place) // function to implement counting sort  
// {  
//   int output[n + 1];  
//   int count[10] = {0};    
  
//   // Calculate count of elements  
//   for (int i = 0; i < n; i++)  
//     count[(a[i] / place) % 10]++;  
      
//   // Calculate cumulative frequency  
//   for (int i = 1; i < 10; i++)  
//     count[i] += count[i - 1];  
  
//   // Place the elements in sorted order  
//   for (int i = n - 1; i >= 0; i--) {  
//     output[count[(a[i] / place) % 10] - 1] = a[i];  
//     count[(a[i] / place) % 10]--;  
//   }  
  
//   for (int i = 0; i < n; i++)  
//     a[i] = output[i];  
// }  
  
// // function to implement radix sort  
// void radixsort(int a[], int n) {  
   
//   // get maximum element from array  
//   int max = getMax(a, n);  
  
//   // Apply counting sort to sort elements based on place value  
//   for (int place = 1; max / place > 0; place *= 10)  
//     countingSort(a, n, place);  
// }  


//--------------------------------BUCKET SORT-------------------------------------
// void bucket(int a[], int n) // function to implement bucket sort  
// {  
//   int max = getMax(a, n); //max is the maximum element of array  
//   int bucket[max], i;  
//   for (int i = 0; i <= max; i++)  
//   {  
//     bucket[i] = 0;  
//   }  
//   for (int i = 0; i < n; i++)  
//   {  
//     bucket[a[i]]++;  
//   }  
//   for (int i = 0, j = 0; i <= max; i++)  
//   {  
//     while (bucket[i] > 0)  
//     {  
//       a[j++] = i;  
//       bucket[i]--;  
//     }  
//   }  
// }  
  