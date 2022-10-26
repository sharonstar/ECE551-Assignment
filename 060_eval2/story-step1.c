#include <stdio.h>
#include <stdlib.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    exitFail("Only take one command line argument.");
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    exitFail("Could not open file.");
  }
  char * line = NULL;
  size_t sz = 0;
  size_t n = 0;
  char ** catNameArray = NULL;

  while (getline(&line, &sz, f) >= 0) {
    readStoryLine(line, catNameArray, NULL, n, NULL, 1);
  }
  free(line);
  if (fclose(f) != 0) {
    exitFail("Failed to close the input file!");
  }
  return EXIT_SUCCESS;
}
