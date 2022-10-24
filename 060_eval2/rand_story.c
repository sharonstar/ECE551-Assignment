#include "rand_story.h"

// helper funcions
void exitFail(const char * message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
