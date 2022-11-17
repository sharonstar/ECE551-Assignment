
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (high - low <= 1) {
    return low;
  }
  int mid = (low + high) / 2;
  int ans = f->invoke(mid);
  if (ans == 0) {
    return mid;
  }
  else if (ans > 0) {
    return binarySearchForZero(f, low, mid);
  }
  else {
    return binarySearchForZero(f, mid, high);
  }
}
