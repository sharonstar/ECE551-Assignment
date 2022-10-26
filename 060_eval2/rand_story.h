#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
/* This function takes a error message as a parameter, print error message and exit the program when there is a error
 */
void exitFail(const char * errormess);
/* This function takes a string and a category_t as parameters. If a string has been used by chooseword function, it stores the string into usedWords->word  
 */
void setUsedWords(const char * str, category_t * usedWords);
/* This function takes a string as a parameter and determine whether it is a valid back reference. If it is not a valid positive integer, it will return 0;  otherwise return the positive integer.
 */
size_t isvalid(char * str);
/* This function takes a catergory name, a used word, and a catarray_t as parameters. It removes the used word of specific catergory in the catarray_t.
 */
void removeUsedWords(char * catName, const char * str, catarray_t * cat);
/* This function takes a line of a file, a catergory name array, its size n,a catarray_t *, a used words category_t, and an index indicated whether chooseword return used words as parameters. It calls readCatName each time there is a blank in this line. After that, all the blanks in the line has heen replaced by a word from the catarray_t. Finally it prints the line to strdout.
 */
void readStoryLine(char * line,
                   char ** catNameArray,
                   catarray_t * cats,
                   size_t n,
                   category_t * usedWord,
                   int index);
/* This function takes a start pointer which points at the start of an underscore, a catergory name array, its size n,a catarray_t *, a used words category_t, and an index indicated whether chooseword return used words as parameters. It reads one blank each time and return a string that should replace it in the blank in story templates.
 */
const char * readCatName(char * start,
                         char ** catNameArray,
                         catarray_t * cats,
                         size_t n,
                         category_t * usedWord,
                         int index);
/* This function takes a line of a file, and a catarray_t * as parameters. It reads catergory names and words in the lines and store them into the catarray_t.
 */
void readWordLine(char * line, catarray_t * cats);
/* This function takes a catarray_t * as parameter. It calls freeCat function for every category_t in the array of catarray_t  and frees the catarray_t structure. 
 */
void freeCatArr(catarray_t * cats);
/* This function takes a category_t * as a parameter. It frees the category_t structure.
 */
void freeCat(category_t * oneCat);
/* This function takes a string array and its size as parameters and frees the string array structure.
 */
void freeStrArr(char ** strarr, size_t n);

#endif
