#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  const char * outsuffix = ".counts";
  int len = strlen(inputName) + 8;
  char * output = malloc(len * sizeof(*output));
  snprintf(output, len, "%s%s", inputName, outsuffix);
  return output;
}
