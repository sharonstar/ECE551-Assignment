#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
double Vector2D::getMagnitude() const {
  using std::sqrt;
  double ans = sqrt(x * x + y * y);
  return ans;
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.x = x + rhs.x;
  ans.y = y + rhs.y;
  return ans;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}
double Vector2D::dot(const Vector2D & rhs) const {
  double ans = x * rhs.x + y * rhs.y;
  return ans;
}
void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
