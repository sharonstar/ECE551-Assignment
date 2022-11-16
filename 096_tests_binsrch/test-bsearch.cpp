#include <cmath>
#include <cstdlib>
#include <ostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  int invoke_num;
  if (high > low) {
    invoke_num = log(high - low) / log(2) + 1;
  }
  else {
    invoke_num = 1;
  }
  CountedIntFn * func = new CountedIntFn(invoke_num, f, mesg);
  int ans = binarySearchForZero(func, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "The answer is incorrect in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}
// test function sin
// range [0,150000), return 3652359 in fewer than 20 invocations
class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};
// test function f(x) = x
class linearFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

int main() {
  SinFunction s;
  linearFunction l;
  // test sin
  check(&s, 0, 150000, 52359, "sin");
  // test f(x) = x
  check(&l, -5, -1, -2, "f(x) = x in [-5, -1)");
  check(&l, -5, 5, 0, "f(x) = x in [-5, 5)");
  check(&l, 1, 5, 1, "f(x) = x in [1, 5)");
  check(&l, -1, 3, 0, "f(x) = x in [-1, 3)");
  check(&l, -2, 0, -1, "f(x) = x in [-2,0)");
  // check(&l, -5, -5, -6, "f(x) = x in [-5, -5)");
  check(&l, 1, 1, 1, "f(x) = x in [5, 5)");
}
