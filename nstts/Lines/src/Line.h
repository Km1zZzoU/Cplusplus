#include "Point.h"
#include <optional>


/* Note: there is no private field in current version of line
 * so it can be 'struct'
 */
class Line {
public:
  double A, B, C; // RE: should these fileds be public?
                  // can I broke your class using them?

  Line(const double A, const double B, const double C);

  Line(const Point& p1, const Point& p2);

  std::optional<Point> intersection(const Line& other);

  Line perpendicular(const Point& p);
};
