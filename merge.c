/* About merge sort requires knowledge about recursion tree method and
 * master master method(DAA). In this snippet code below I have already use
 * binary search to search a key element. */
/* Note: Binary search is used only when the element in an array has already 
 * sorted */
/* However in this code I use iterative function to illustrate the merge sort*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool check = true;

struct read{
    char first_alpha;
    int len_alpha;
};

typedef struct{
    int input[100];
}arr1d;

int user_num();
arr1d user_inputArray(int arr_size);
int userInput_element();
int BinarySearch_asc(int array[], int start_idx, int end_idx, int x);
int BinarySearch_desc(int array[], int start_idx, int end_idx, int x);
int min(int x, int y);
void merge_asc(int arr[], int left, int mid, int right);
void mergeSort_asc(int arr[], int arr_size);
void merge_desc(int arr[], int left, int mid, int right);
void mergeSort_desc(int arr[], int arr_size);
void printArray(int arr[], int arr_size);
void readArray(int arr[], int arr_size);
void user_choice(char *choice);
struct read getch();
void process();

int main()
{
    process();

    return 0;
}

/* Driver code */
void process()
{
    char choice;
    user_choice(&choice);

    int arr_size = user_num();

    arr1d result;
    result = user_inputArray(arr_size);

    // key element to search
    int key = userInput_element();

    readArray(result.input, arr_size);

    int result_key;

    if(choice == 'A'){
        printf("The ascending order is: \n");
        mergeSort_asc(result.input, arr_size);
        printArray(result.input, arr_size);
        result_key = BinarySearch_asc(result.input, 0, arr_size - 1, key);
        if(result_key == -1)
            printf("Not found");
        else
            printf("Element is found at index %d", result_key + 1);
    }
    else{
        printf("The descending order is: \n");
        mergeSort_desc(result.input, arr_size);
        printArray(result.input, arr_size);
        result_key = BinarySearch_desc(result.input, 0, arr_size - 1, key);
        if(result_key == -1)
            printf("Not found");
        else
            printf("Element is found at index %d", result_key + 1);
    }
}

/* Asking for input the array size */
int user_num()
{
    int num;
    do{
        if(num <= 20 || num > 0){
            printf("Please enter the length(0-20) of an array: ");
            while(!scanf("%d", &num)){
                printf("Invalid value.Please enter an integer: ");
                scanf("%*s");
            }
            while(getc(stdin) != '\n')
                ;
        }
    }while(num > 20 || num <= 0);

    return num;
}

/* Asking for input rhe elements in an array with user's arr_size*/
arr1d user_inputArray(int arr_size)
{
    arr1d result;
    int i;
    for(i = 0; i < arr_size; i++){
        printf("Please enter number in array[%d]: ", i + 1);
        while(!scanf("%d", (result.input + i))){
            printf("Invalid value. Please try to input integer: ");
            scanf("%*s");
        }
        while(getc(stdin) != '\n')
            ;
    }
    return result;
}

/* It use to ask the input from user to fill the key search value */
int userInput_element()
{
    int key;
    printf("Please input your search element(number): ");
    while(!scanf("%d", &key)){
        printf("Invalid value. Please input integer: ");
        scanf("%*s");
    }
    while(getc(stdin) != '\n')
        ;
    return key;
}

/* Function to search if element X is present in reverse sorted array */
int BinarySearch_desc(int array[], int start_idx, int end_idx, int x)
{
    while (start_idx <= end_idx){

        int mid = start_idx + (end_idx - start_idx )/2;
        if (array[mid] == x)
            return mid;

        // This condition check only for descending order
        if (array[mid] > x)
            start_idx = mid + 1; // Search in right half of subarray
        else
            end_idx = mid - 1; // Search in left half of subarray
    }
    return -1;
}


/* Function to search if element X is present in sorted array */
int BinarySearch_asc(int array[], int start_idx, int end_idx, int x)
{
   while (start_idx <= end_idx){

        int mid = start_idx + (end_idx - start_idx )/2;
        if (array[mid] == x)
            return mid;

        // This condition check only for ascending order
        if (array[mid] < x)
            start_idx = mid + 1; // Search in right half of subarray
        else
            end_idx = mid - 1; // Search in left half of subarray
    }
    return -1;
}

/* Utility function to find minimum of 2 integers */
int min(int x, int y) {return (x < y) ? x : y;}

/* Iterative mergesort function to sort arr[0..n-1] */
void mergeSort_asc(int arr[], int arr_size)
{
    int curr_size;  // For current size of subarrays to be merged
                    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
                    // to be merged

    /* Merge subarrays in bottom up manner. First merge subarrays of size
     * 1 to create sorted subarrays of size 2, then merge subarrays of size
     * 2 to create sorted subarrays of size 4, and so on. */
     for(curr_size = 1; curr_size <= arr_size - 1; curr_size = 2*curr_size)
     {
        /* Pick starting point of different subarrays of current size */
        for(left_start = 0; left_start < arr_size - 1; left_start += 2*curr_size)
        {
            /* Find ending point of left subarray. mid + 1 is starting point of
             * right */
          int mid       = min(left_start + curr_size - 1, arr_size - 1);
          int right_end = min(left_start + 2*curr_size - 1, arr_size - 1);

          /* Merge Subarrays arr[left_start..mid] & arr[mid + 1..right_end] */
          merge_asc(arr, left_start, mid, right_end);
        }
     }

}

/* Function to merge the 2 halves arr[1..m] and arr[m + 1..r] of array arr[] */
void merge_asc(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* create temp arrays */
    int Left[n1], Right[n2];

    /* Copy data to temp arrays Left[] and Right[] */
    //copying appropriate elements from array[] to left[]
    for(i = 0; i < n1; i++) Left[i] = arr[left + i];
    //copying appropriate elements from array[] to right[]
    for(j = 0; j < n2; j++) Right[j]  = arr[mid + 1 + j];

    /* Merge the temp arrays back into arr[1..r] */
    i = 0; // initial index of sub-array left[]
    j = 0; // initial index of sub-array right[]
    k = left; //initial index of merged array
    while(i < n1 && j < n2)
    {
        // This is condition for ascending order
        //storing value of left[i] in array[k] if the former is smaller
        if(Left[i] <= Right[j]) arr[k] = Left[i++];
        /*
        if(Left[i] <= Right[j])
        {
            arr[k] = Left[i];
            i++;
        } */
        //storing value of right[j] in array[j] if the former is smaller
        else arr[k] = Right[j++];
        /*
        else
        {
            arr[k] = Right[j];
            j++;
        } */
        k++;
    }

    /* copying back the remaining elements of left[] to array[] */
    while(i < n1) arr[k++] = Left[i++];
    /*
    while(i < n1)
    {
        arr[k] = Left[i];
        i++;
        k++;
    } */

    /* copying back the remaining elements of right[] to array[] */
    while(j < n2) arr[k++] = Right[j++];
    /*
    while(j < n2)
    {
        arr[k] = Right[j];
        j++;
        k++;
    } */
}

void mergeSort_desc(int arr[], int arr_size)
{
    int curr_size;  // For current size of subarrays to be merged
                    // curr_size varies from 1 to n/2
    int left_start; // For picking starting index of left subarray
                    // to be merged

    /* Merge subarrays in bottom up manner. First merge subarrays of size
     * 1 to create sorted subarrays of size 2, then merge subarrays of size
     * 2 to create sorted subarrays of size 4, and so on. */
     for(curr_size = 1; curr_size <= arr_size - 1; curr_size = 2*curr_size)
     {
        /* Pick starting point of different subarrays of current size */
        for(left_start = 0; left_start < arr_size - 1; left_start += 2*curr_size)
        {
            /* Find ending point of left subarray. mid + 1 is starting point of
             * right */
          int mid       = min(left_start + curr_size - 1, arr_size - 1);
          int right_end = min(left_start + 2*curr_size - 1, arr_size - 1);

          /* Merge Subarrays arr[left_start..mid] & arr[mid + 1..right_end] */
          merge_desc(arr, left_start, mid, right_end);
        }
     }

}

/* Function to change from ascending to descending order */
void merge_desc(int arr[], int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    /* create temp arrays */
    int Left[n1], Right[n2];

    /* Copy data to temp arrays Left[] and Right[] */
    //copying appropriate elements from array[] to left[]
    for(i = 0; i < n1; i++) Left[i] = arr[left + i];
    //copying appropriate elements from array[] to right[]
    for(j = 0; j < n2; j++) Right[j]  = arr[mid + 1 + j];

    /* Merge the temp arrays back into arr[1..r] */
    i = 0; // initial index of sub-array left[]
    j = 0; // initial index of sub-array right[]
    k = left; //initial index of merged array
    while(i < n1 && j < n2)
    {
        // This is codition for descending order
        //storing value of left[i] in array[k] if the former is larger
        if(Left[i] > Right[j])
        {
            arr[k] = Left[i];
            i++;
        }
        //storing value of right[j] in array[j] if the former is larger
        else
        {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    /* copying back the remaining elements of left[] to array[] */
    while(i < n1)
    {
        arr[k] = Left[i];
        i++;
        k++;
    }

    /* copying back the remaining elements of right[] to array[] */
    while(j < n2)
    {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

/* Function to print an array */
void printArray(int arr[], int arr_size)
{
    int i;
    printf("\nSorted array: \n");
    for(i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

/* Function to read an array */
void readArray(int arr[], int arr_size)
{
    int i;
    printf("\nOriginal array: \n");
    for(i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

/* keep asking for only character choice */
void user_choice(char *choice)
{
    printf("Before search for the value, please choose which order: \n");
    printf("Type A for ascending order of the array or type D for descending order of the array: ");
    struct read halo;
    do{
        halo = getch();
        *choice = toupper(halo.first_alpha);

        if((*choice == 'A' || *choice == 'D') && halo.len_alpha == 1)
            break;
        printf("Please try enter again: ");
    }while(check == true);

    *choice = toupper(halo.first_alpha);

    putchar('\n');
}

struct read getch()
{
    int count = 1;
    struct read input;
    input.first_alpha = getc(stdin);
    while(getc(stdin) != '\n')
        count++;
    input.len_alpha = count;
    return input;
}
