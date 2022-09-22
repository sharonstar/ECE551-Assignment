#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run(int * array, size_t n, size_t expected) {
  size_t ans = maxSeq(array, n);
  if (ans != expected) {
    printf("There is an error.\n");
    exit(EXIT_FAILURE);
  }
  else {
    printf("No error.\n");
  }
}
int main(void) {
  int arr1[3] = {1, 1, 1};
  int arr2[10] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int arr3[4] = {0, 0, 0, 0};
  int arr4[5] = {1, 2, 3, 3, 4};
  int arr5[5] = {4, 3, 3, 4, 5};
  int arr6[1] = {1};
  int arr7[4] = {-1, -2, 1, 2};

  run(arr1, 3, 1);
  run(arr2, 10, 4);
  run(arr3, 4, 1);
  run(arr4, 5, 3);
  run(arr5, 5, 3);
  run(arr6, 1, 1);
  run(arr7, 4, 3);
  run(NULL, 0, 0);
  return EXIT_SUCCESS;
}
