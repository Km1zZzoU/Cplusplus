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

bool m::operator!=(const Triple& other) const {
  return !(value == other.value);
}
