#include "Point.h"
#include <optional>


class Line {
public:
  double A, B, C;

  Line(const double A, const double B, const double C);

  Line(const Point& p1, const Point& p2);

  std::optional<Point> intersection(const Line& other);

  Line perpendicular(const Point& p);
};
