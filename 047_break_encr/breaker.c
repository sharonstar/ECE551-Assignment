#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
int findLargestIndex(int * array, int n, FILE * f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      array[c - 'a'] += 1;
    }
  }
  int largest = 0;
  for (int i = 0; i < n; i++) {
    if (array[i] > array[largest]) {
      largest = i;
    }
  }
  return largest;
}

int decrypt(FILE * f) {
  int cfre[26] = {0};
  int largestIndex = findLargestIndex(cfre, 26, f);
  int key;
  if (largestIndex >= 4) {
    key = largestIndex - 4;
  }
  else {
    key = largestIndex + 22;
  }
  return key;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong input: don't have 2 input");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = decrypt(f);
  if (key < 0 || key >= 26) {
    fprintf(stderr, "Wrong key: put of range");
    return EXIT_FAILURE;
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  fprintf(stdout, "%d\n", key);
  return EXIT_SUCCESS;
}
