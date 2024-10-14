#include<stdio.h>
#include<string.h>

struct Item{
    char Color[10];
    int data;
};

void swap(struct Item *a, struct Item *b) {
    struct Item temp = *a;
    *a = *b;
    *b = temp;
}

void sortGroupByNumber(struct Item arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        for (int j = i + 1; j <= end; j++) {
            if (arr[i].data > arr[j].data) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void sortPairsByColor(struct Item arr[], int n) {
    int redIndex = 0, blueIndex = 0, yellowIndex = n - 1;

    while (blueIndex <= yellowIndex) {
        if (strcmp(arr[blueIndex].Color, "red") == 0) {
            swap(&arr[redIndex], &arr[blueIndex]);
            redIndex++;
            blueIndex++;
        } else if (strcmp(arr[blueIndex].Color, "blue") == 0) {
            blueIndex++;
        } else if (strcmp(arr[blueIndex].Color, "yellow") == 0) {
            swap(&arr[blueIndex], &arr[yellowIndex]);
            yellowIndex--;
        }
    }

    // Sort the red group
    sortGroupByNumber(arr, 0, redIndex - 1);
    
    // Sort the blue group
    sortGroupByNumber(arr, redIndex, blueIndex - 1);
    
    // Sort the yellow group
    sortGroupByNumber(arr, blueIndex, n - 1);
}

void traversal(struct Item array[],int size)
{
    for(int i=0;i<size;i++)
    {
        printf("(%d,%s) ",array[i].data,array[i].Color);
    }
}

int main()
{
    int n; // No of pairs
    printf("Enter the value of n: ");
    scanf("%d",&n);

    struct Item array[n];
    for(int i=0;i<n;i++)
    {
        printf("Enter value of Item%d[num]: ",i+1);
        scanf("%d",&array[i].data);

        printf("Enter the value of Item[color]: ");
        scanf("%s",&array[i].Color);
    }

    sortPairsByColor(array,n);
    traversal(array,n);

    return 0;
}