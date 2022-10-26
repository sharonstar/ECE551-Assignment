#include <stdio.h>
#include <stdlib.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    exitFail("Only take one command line argument.");
  }
  FILE * fCat = fopen(argv[1], "r");
  if (fCat == NULL) {
    exitFail("Could not open the word file.");
  }
  FILE * fStory = fopen(argv[2], "r");
  if (fStory == NULL) {
    exitFail("Could not open the story template file.");
  }
  category_t * usedWord = malloc(sizeof(*usedWord));
  // free useWord
  usedWord->name = NULL;
  usedWord->n_words = 0;
  usedWord->words = NULL;

  // read catarray_t from word.txt
  catarray_t * cats = malloc(sizeof(*cats));
  cats->n = 0;
  cats->arr = NULL;
  char * wordline = NULL;
  size_t wordsz = 0;
  while (getline(&wordline, &wordsz, fCat) >= 0) {
    readWordLine(wordline, cats);
  }
  free(wordline);
  // read category name array from blank in story.txt
  char * storyline = NULL;
  size_t storysz = 0;
  size_t n = 0;
  char ** catNameArray = NULL;
  while (getline(&storyline, &storysz, fStory) >= 0) {
    readStoryLine(storyline, catNameArray, cats, n, usedWord, 1);
  }
  free(storyline);

  if (fclose(fCat) != 0) {
    exitFail("Failed to close the words file!");
  }
  if (fclose(fStory) != 0) {
    exitFail("Failed to close the story template file!");
  }
  //freeCat(usedWord);
  for (size_t i = 0; i < usedWord->n_words; i++) {
    free(usedWord->words[i]);
  }
  free(usedWord->words);
  freeCatArr(cats);
  return EXIT_SUCCESS;
}
