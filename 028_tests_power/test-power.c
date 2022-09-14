#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    printf("There is an error.");
    exit(EXIT_FAILURE);
  }
}
int main(void) {
  run_check(2, 4, 16);
  run_check(2, 0, 1);
  run_check(3, 3, 27);
  run_check(5, 6, 15625);
  run_check(3, 2, 9);
  run_check(1, 2, 1);
  run_check(2, 4, 16);
  run_check(0, 0, 1);
  run_check(-2, 3, -8);
  return EXIT_SUCCESS;
}
