#include <stdio.h>
#include <stdlib.h>
unsigned power_helper(unsigned x, unsigned ans, unsigned y) {
  if (y == 0) {
    return ans;
  }
  else {
    return power_helper(x, ans * x, y - 1);
  }
}
unsigned power(unsigned x, unsigned y) {
  return power_helper(x, 1, y);
}
