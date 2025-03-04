#include "Triple.h"
#include <cstdlib>

using m = Triple;

m::Triple(const double v) {
  value = v;
}

bool m::operator==(const Triple& other) const {
  double e = 1e-9;
  return std::abs(value - other.value) < e;
}

/* RE: about floating point comparison
 * Actually `==` works like bitwise comparision 
 * And it is almost always tricky.
 * use bitwise comparison only if your know what your doing
 */
bool m::operator!=(const Triple& other) const {
  /* RE: why not this == other */
  return !(value == other.value);
}
