#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->countArray = malloc(sizeof(*counts->countArray));
  counts->numStr = 1;
  counts->countArray[0].num = 0;
  return counts;
}
void addCount(counts_t * c, const char * name) {
  c->countArray = realloc(c->countArray, (c->numStr + 1) * sizeof(*c->countArray));
  if (name == NULL) {
    c->countArray[0].str = "<unknown>";
    c->countArray[0].num++;
    return;
  }
  for (size_t i = 1; i < c->numStr; i++) {
    if (strcmp(name, c->countArray[i].str) == 0) {
      c->countArray[i].num++;
      return;
    }
  }
  one_count_t new;
  new.num = 1;
  new.str = strdup(name);
  c->countArray[c->numStr] = new;
  c->numStr++;
}
void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 1; i < c->numStr; i++) {
    fprintf(outFile, "%s: %lx\n", c->countArray[i].str, c->countArray[i].num);
  }
  if (c->countArray[0].num > 0) {
    fprintf(outFile, "%s: %lx\n", c->countArray[0].str, c->countArray[0].num);
  }
}
void freeCounts(counts_t * c) {
  for (size_t i = 1; i < c->numStr; i++) {
    free(c->countArray[i].str);
  }
  free(c->countArray);
  free(c);
}
