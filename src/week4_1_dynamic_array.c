/*
 * week4_1_dynamic_array.c
 * Author: Rainers Bulgacs
 * Student ID: 251RDC073
 * Description:
 *   Demonstrates creation and usage of a dynamic array using malloc.
 *   Allocate memory for n integers, read them from the user,
 *   print their sum and average, and then free the memory.
 *
 *   Output must match the format in the Week 4 instructions exactly
 *   (it is checked by the autograder).
 */

#include <stdio.h>
#include <stdlib.h>

int array_sum(int arr[], int size){
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum = sum + arr[i];
  }
  return sum;
}

float array_avg(int arr[], int size) {
  int sum = 0;
  float avg = 0.00;
  for (int i = 0; i < size; i++) {
    sum = sum + arr[i];
  }
  avg = (float)sum / size;
  return avg;
}

int main(void) {
    int n;
    int *arr = NULL;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    // Allocate memory for n integers using malloc
    arr = malloc(n * sizeof(int));

    // TODO: Check allocation success
    // If arr is NULL: print "Memory allocation failed." and return 1
    if (arr == NULL) {
        printf ("Memory allocation failed.\n");
        return 1;
    }

    // TODO: Print the prompt "Enter %d integers: " (with n), then read
    //       n integers into the array.
    //       If a value cannot be read: print "Invalid input.",
    //       free the array and return 1
    printf ("Enter %d integers: ", n);
    for (int i = 0; i<n; i++) {
      int res = scanf("%d", &arr[i]);
      if (res !=1 ) {
        printf ("Invalid input.\n");
        free(arr);
        return 1;
      }
    }

// sum and arr


    // TODO: Print the results exactly as:
    //       Sum = <sum>
    //       Average = <average with 2 decimals, %.2f>

    // TODO: Free allocated memory
    // (void)arr;  // remove this line once you use arr
    printf("Sum = %d\n", array_sum(arr, n));
    printf("Average = %.2f\n", array_avg(arr, n));

    return 0;
}
