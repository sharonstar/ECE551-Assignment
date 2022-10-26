#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void exitFail(const char * errormess);
void setUsedWords(const char * str, category_t * usedWords);
int isvalid(char * str);
void removeUsedWords(char * catName, const char * str, catarray_t * cat);
void readStoryLine(char * line,
                   char ** catNameArray,
                   catarray_t * cats,
                   size_t n,
                   category_t * usedWord,
                   int index);
const char * readCatName(char * start,
                         char ** catNameArray,
                         catarray_t * cats,
                         size_t n,
                         category_t * usedWord,
                         int index);

void readWordLine(char * line, catarray_t * cats);
void freeCatArr(catarray_t * cats);
void freeCat(category_t * oneCat);
void freeStrArr(char ** strarr, size_t n);

#endif
