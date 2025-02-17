#include "../src/Line.h"
#include "../src/Triple.h"
#include <gtest/gtest.h>

#include <cstdlib>

TEST(Intersection, Simple) {
  auto line1 = Line(Point(0, 0), Point(2, 2));
  auto line2 = Line(Point(2, 0), Point(0, 2));

  auto point = line1.intersection(line2);

  ASSERT_TRUE((Triple(point->y) == Triple(1)) &&
              (Triple(point->x) == Triple(1)));
}

TEST(Intersection, Simple2) {
  auto line1 = Line(1, 2, 0);
  auto line2 = Line(2, 5, 2);


  auto point = line1.intersection(line2);

  ASSERT_TRUE((Triple(point->y) == Triple(-2)) &&
              (Triple(point->x) == Triple(4)));
}

TEST(Perpendicular, Simple) {
  Line line(Point(2, 1), Point(3, 3));
  auto per = line.perpendicular(Point(0, 0));

  ASSERT_TRUE(Triple(per.C) == Triple(0));

  ASSERT_TRUE(!per.intersection(Line(1, 2, 5)).has_value());
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
