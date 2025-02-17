#include "Line.h"
#include "Triple.h"
#include <optional>
using m = Line;

m::Line(const double A, const double B, const double C) {
  this->A = A;
  this->B = B;
  this->C = C;
}

m::Line(const Point& p1, const Point& p2) {
  // px + y + q = 0
  // p = a/b q = c/b
  double p = (p2.y - p1.y) / (p1.x - p2.x);
  double q = -p1.y - p2.y - (p2.x + p1.x) * p;

  this->A = 2 * p;
  this->B = 2;
  this->C = q;
}

std::optional<Point> m::intersection(const Line& other) {
  auto k1 = Triple(A / B);
  auto k2 = Triple(other.A / other.B);
  if (k1 == k2)
    return std::nullopt;
  double p1 = A / B;
  double p2 = other.A / other.B;
  double q1 = C / B;
  double q2 = other.C / other.B;

  double x = (q2 - q1) / (p1 - p2);
  double y = (-x * (p1 + p2) - q1 - q2) / 2;
  return Point(x, y);
}

Line m::perpendicular(const Point& p) {
  return Line(p, Point(p.x + A, p.y + B));
}
