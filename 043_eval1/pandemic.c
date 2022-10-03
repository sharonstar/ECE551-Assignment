#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  char name[64] = {0};
  country_t ans;
  for (int i = 0; i < 64; i++) {
    ans.name[i] = name[i];
  }
  char * split = strchr(line, ',');
  if (split == NULL) {
    fprintf(stderr, "wrong input");
    exit(EXIT_FAILURE);
  }
  ans.population = atoi(&split[1]);
  for (int i = 0; line[i] != ','; i++) {
    if (i == 64) {
      fprintf(stderr, "name is too long");
      exit(EXIT_FAILURE);
    }
    ans.name[i] = line[i];
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  for (size_t i = 0; i < n_days - 5; i++) {
    unsigned sum = 0;
    for (size_t j = i; j < i + 7; j++) {
      sum += data[j];
    }
    avg[i] = sum / (double)7;
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  unsigned sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum += data[i];
    cum[i] = sum / (double)pop * 100000;
  }
}
int LargestIndex(unsigned * array, int n) {
  int largrestIndex = 0;
  for (int i = 0; i < n; i++) {
    if (array[i] > array[largrestIndex]) {
      largrestIndex = i;
    }
  }
  return largrestIndex;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  for (size_t i = 0; i < n_days; i++) {
    unsigned array[n_countries];
    for (size_t j = 0; j < n_countries; j++) {
      array[j] = data[j][i];
    }
    int largestIndex = LargestIndex(array, n_countries);
    unsigned number_cases = array[largestIndex];
    printf("%s has the most daily cases with %u\n",
           countries[largestIndex].name,
           number_cases);
  }
}
