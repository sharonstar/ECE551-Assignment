#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t maxAns = 1;
  size_t ans = 1;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i + 1] > array[i]) {
      ans++;
    }
    else {
      ans = 1;
    }
    if (ans > maxAns) {
      maxAns = ans;
    }
  }
  return maxAns;
}
