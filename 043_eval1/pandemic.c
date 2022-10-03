#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  if (line == NULL) {
    fprintf(stderr, "This line does not have country and population.");
    exit(EXIT_FAILURE);
  }
  // initialize a country_t named ans
  char name[64] = {0};
  country_t ans;
  for (int i = 0; i < 64; i++) {
    ans.name[i] = name[i];
  }
  char * split = strchr(line, ',');
  if (split == NULL) {
    fprintf(stderr, "Wrong input: there is no comma.");
    exit(EXIT_FAILURE);
  }
  // determine whether population is legal
  /*
  for (int i = 1; split[i] != '\n'; i++) {
    if (split[i] < '0' && split[i] > '9') {
      fprintf(stderr, "Wrong input: population is not an integer.");
      exit(EXIT_FAILURE);
    }
    } */
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
  for (size_t i = 0; i < n_days - 6; i++) {
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
  unsigned array[n_countries];
  for (size_t i = 0; i < n_countries; i++) {
    int largest_case_number = LargestIndex(data[i], n_days);
    array[i] = data[i][largest_case_number];
  }
  int largest_country_index = LargestIndex(array, n_countries);
  unsigned number_cases = array[largest_country_index];
  printf("%s has the most daily cases with %u\n",
         countries[largest_country_index].name,
         number_cases);
}
