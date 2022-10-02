#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rotate(char array[][10], char ans[][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      ans[i][j] = array[9 - j][i];
    }
  }
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "wrong input");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("could not open");
    return EXIT_FAILURE;
  }
  char array[10][10];
  char line[12];
  int linenum = 0;
  while (fgets(line, 12, f) != NULL) {
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "the line has more than 10 characters");
      return EXIT_FAILURE;
    }
    if (linenum == 10) {
      fprintf(stderr, "this txt has more than 10 lines");
      return EXIT_FAILURE;
    }
    memcpy(array[linenum], line, sizeof(int) * 10);
    linenum += 1;
  }
  if (fclose(f) != 0) {
    perror("failed to close");
    return EXIT_FAILURE;
  }
  char ans[10][10];
  rotate(array, ans);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      printf("%c", ans[i][j]);
    }
    printf("\n");
  }
}
