#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

void exitFail(const char * message);
void readStoryLine(char * line, char ** catNameArray, catarray_t * cats, size_t n);

#endif
