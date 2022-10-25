#include "rand_story.h"

// Helper funcions

// This function takes a error message string as a parameter, print the error message and exit the program
void exitFail(const char * errormess) {
  fprintf(stderr, "%s\n", errormess);
  exit(EXIT_FAILURE);
}

const char * readCatName(char * start,
                         char ** catNameArray,
                         catarray_t * cats,
                         size_t n) {
  char * end = strchr(start + 1, '_');
  if (end == NULL) {
    exitFail("No matching underscore.");
  }
  size_t catLen = end - start;
  char * catName = strndup(start + 1, catLen - 1);
  // free catName
  // catName exists in catNameArray
  for (size_t i = 0; i < n; i++) {
    if (strcmp(catNameArray[i], catName) == 0) {
      const char * replace1 = chooseWord(catNameArray[i], cats);
      return replace1;
    }
  }
  // catName does not exist in catNameArray
  catNameArray = realloc(catNameArray, (n + 1) * sizeof(*catNameArray));
  catNameArray[n] = strdup(catName);
  // free catNameArray
  n++;
  const char * replace2 = chooseWord(catNameArray[n], cats);
  //printf("%s\n", start + 1);
  return replace2;
}
void readStoryLine(char * line, char ** catNameArray, catarray_t * cats, size_t n) {
  char * start = strchr(line, '_');
  char * printAns = line;
  while (start != NULL) {
    const char * replace = readCatName(start, catNameArray, cats, n);
    size_t replaceLen = strlen(replace);
    char * end = strchr(start + 1, '_') + 1;
    size_t endLen = strlen(end);
    char ans[start - printAns + 1 + replaceLen + endLen];

    strncpy(ans, printAns, start - printAns);
    ans[start - printAns] = '\0';
    strcat(ans, replace);
    strcat(ans, end);
    printAns = strdup(ans);
    // free printAns
    //printf("%s\n", printAns);
    start = strchr(printAns, '_');
  }
  printf("%s\n", printAns);
}
