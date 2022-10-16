#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * f = fopen(filename, "r");
  char * line = NULL;
  size_t sz = 0;
  counts_t * c = createCounts();
  if (f == NULL) {
    perror("could not open the files");
  }
  while (getline(&line, &sz, f) >= 0) {
    char * pointer = strchr(line, '\n');
    if (pointer != NULL) {
      *pointer = '\0';
    }
    const char * key = strdup(line);
    char * value = lookupValue(kvPairs, key);
    addCount(c, value);
  }
  free(line);
  assert(fclose(f) == 0);
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc <= 2) {
    fprintf(stderr, "incorrect input files.");
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 0; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    assert(fclose(f) == 0);
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
