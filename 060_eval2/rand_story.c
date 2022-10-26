#include "rand_story.h"

// Helper funcions
void exitFail(const char * errormess) {
  fprintf(stderr, "%s\n", errormess);
  exit(EXIT_FAILURE);
}
// Funtions for step1 and step3
void setUsedWords(const char * str, category_t * usedWords) {
  usedWords->words =
      realloc(usedWords->words, (usedWords->n_words + 1) * sizeof(*usedWords->words));
  usedWords->words[usedWords->n_words] = strdup(str);
  usedWords->n_words++;
}
size_t isvalid(char * str) {
  char * end;
  long int backRef = strtol(str, &end, 10);
  if (*end != '\0') {
    return 0;
  }
  if (backRef < 1) {
    return 0;
  }
  size_t back = (size_t)backRef;
  return back;
}
// Funtions for step4
void removeUsedWords(char * catName, const char * str, catarray_t * cat) {
  for (size_t i = 0; i < cat->n; i++) {
    if (strcmp(cat->arr[i].name, catName) == 0) {
      char ** temp = malloc((cat->arr[i].n_words - 1) * sizeof(*temp));
      size_t j = 0;
      size_t t = 0;
      while (j < cat->arr[i].n_words && t < (cat->arr[i].n_words - 1)) {
        if (strcmp(cat->arr[i].words[j], str) == 0) {
          j++;
        }
        temp[t] = strdup(cat->arr[i].words[j]);
        j++;
        t++;
      }
      freeStrArr(cat->arr[i].words, cat->arr[i].n_words);
      cat->arr[i].words = temp;
      cat->arr[i].n_words--;
      return;
    }
  }
}
const char * readCatName(char * start,
                         char ** catNameArray,
                         catarray_t * cats,
                         size_t n,
                         category_t * usedWord,
                         int index) {
  char * end = strchr(start + 1, '_');
  if (end == NULL) {
    exitFail("No matching underscore.");
  }
  size_t catLen = end - start;
  char * catName = strndup(start + 1, catLen - 1);
  char * currName;
  // catName exists in catNameArray
  for (size_t i = 0; i < n; i++) {
    if (strcmp(catNameArray[i], catName) == 0) {
      currName = catNameArray[i];
    }
  }
  // catName does not exist in catNameArray
  catNameArray = realloc(catNameArray, (n + 1) * sizeof(*catNameArray));
  catNameArray[n] = strdup(catName);
  currName = catName;
  n++;
  // step1: cats is always NULL
  if (cats == NULL) {
    const char * replace = strdup(chooseWord(currName, cats));
    free(catName);
    freeStrArr(catNameArray, n);
    return replace;
  }
  // step3: need determine what currName is
  for (size_t i = 0; i < cats->n; i++) {
    // currname is catergory name
    if (strcmp(currName, cats->arr[i].name) == 0) {
      //step4: remove used words
      if (index == 2) {
        const char * replace = strdup(chooseWord(currName, cats));
        setUsedWords(replace, usedWord);
        removeUsedWords(currName, replace, cats);
        free(catName);
        freeStrArr(catNameArray, n);
        return replace;
      }
      else {
        const char * replace = strdup(chooseWord(currName, cats));
        setUsedWords(replace, usedWord);
        free(catName);
        freeStrArr(catNameArray, n);
        return replace;
      }
    }
  }
  // currname is neither a backrefence nor a catergory name
  size_t backRef = isvalid(currName);
  if (backRef == 0) {
    exitFail("Blank is neither a backrefence nor a catergory name.");
  }
  if ((int)usedWord->n_words - (int)backRef < 0) {
    exitFail("Invalid backrefence.");
  }
  // currname is a backrefence
  char * replace = strdup(usedWord->words[usedWord->n_words - backRef]);
  setUsedWords(replace, usedWord);
  free(catName);
  freeStrArr(catNameArray, n);
  return replace;
}

void readStoryLine(char * line,
                   char ** catNameArray,
                   catarray_t * cats,
                   size_t n,
                   category_t * usedWord,
                   int index) {
  char * start = strchr(line, '_');
  char * printAns = line;
  // use ansArray to store answer after a replace for blank
  char ** ansArray = NULL;
  size_t ansSize = 0;
  while (start != NULL) {
    const char * replace = readCatName(start, catNameArray, cats, n, usedWord, index);
    size_t replaceLen = strlen(replace);
    char * end = strchr(start + 1, '_') + 1;
    size_t endLen = strlen(end);
    char ans[start - printAns + 1 + replaceLen + endLen];
    //copy answer after a replace for blank to char ans
    strncpy(ans, printAns, start - printAns);
    ans[start - printAns] = '\0';
    strcat(ans, replace);
    strcat(ans, end);
    //put each ans into ansArray
    ansArray = realloc(ansArray, (ansSize + 1) * sizeof(*ansArray));
    ansArray[ansSize] = strdup(ans);
    printAns = ansArray[ansSize];
    ansSize++;
    free((char *)replace);
    start = strchr(printAns, '_');
  }
  printf("%s\n", printAns);
  freeStrArr(ansArray, ansSize);
}

// Funtions for step2
void readWordLine(char * line, catarray_t * cats) {
  char * split = strchr(line, ':');
  if (split == NULL) {
    exitFail("Invalid words.txt.");
  }
  // read each category name and word name
  size_t catNameLen = split - line;
  char * catName = strndup(line, catNameLen);
  char * end = strchr(split, '\n');
  size_t wordNameLen = end - split - 1;
  char * wordName = strndup(split + 1, wordNameLen);

  // catName exists in catarray_t * cats
  for (size_t i = 0; i < cats->n; i++) {
    if (strcmp(cats->arr[i].name, catName) == 0) {
      cats->arr[i].words = realloc(
          cats->arr[i].words, (cats->arr[i].n_words + 1) * sizeof(*cats->arr[i].words));
      cats->arr[i].words[cats->arr[i].n_words] = wordName;
      cats->arr[i].n_words++;
      free(catName);
      return;
    }
  }
  // catName does not exist in catarray_t * cats
  cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
  cats->arr[cats->n].name = catName;
  cats->arr[cats->n].n_words = 1;
  cats->arr[cats->n].words = malloc(sizeof(*cats->arr[cats->n].words));
  cats->arr[cats->n].words[0] = wordName;
  cats->n++;
}
// Free functions for every data structure
void freeCatArr(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    category_t * curr = &cats->arr[i];
    freeCat(curr);
  }
  free(cats->arr);
  free(cats);
}

void freeCat(category_t * oneCat) {
  for (size_t i = 0; i < oneCat->n_words; i++) {
    if (oneCat->words[i] != NULL) {
      free(oneCat->words[i]);
    }
  }
  free(oneCat->name);
  free(oneCat->words);
}
void freeStrArr(char ** strarr, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (strarr[i] != NULL) {
      free(strarr[i]);
    }
  }
  free(strarr);
}
