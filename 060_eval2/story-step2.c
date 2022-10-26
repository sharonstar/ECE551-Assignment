#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitFail("Only take one command line argument.");
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    exitFail("Could not open file.");
  }
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats->arr = NULL;

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    readWordLine(line, cats);
  }
  free(line);
  if (fclose(f) != 0) {
    exitFail("Failed to close the input file!");
  }
  printWords(cats);
  freeCatArr(cats);
  return EXIT_SUCCESS;
}
