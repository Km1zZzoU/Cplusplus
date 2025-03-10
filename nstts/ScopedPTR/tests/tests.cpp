#include "../src/ScopedPTR.cpp"
#include "../src/ScopedPTR.hpp"
#include <gtest/gtest.h>

#include <cstdlib>

TEST(deep, 1) {
  ScopedPTRdeep deep_p{new Triple{13, 42, 1}};
  ASSERT_EQ(deep_p->x, 13);
  ASSERT_EQ(deep_p->y, 42);
  ASSERT_EQ(deep_p->z, 1);
}

TEST(deep, 2) {
  ScopedPTRdeep deep_p{new Triple{13, 42, 1}};
  ScopedPTRdeep p2 = deep_p;
  ScopedPTRdeep p3  = p2;
  ASSERT_EQ(p3->x, 13);
  ASSERT_EQ(p3->y, 42);
  ASSERT_EQ(p3->z, 1);
}

TEST(trans, 1) {
  ScopedPTRtrans trans_p{new Triple{13, 42, 1}};
  ASSERT_EQ(trans_p->x, 13);
  ASSERT_EQ(trans_p->y, 42);
  ASSERT_EQ(trans_p->z, 1);
}

TEST(trans, 2) {
  ScopedPTRtrans trans_p{new Triple{13, 42, 1}};
  ScopedPTRtrans moved_p = std::move(trans_p);
  ASSERT_EQ(trans_p.operator->(), nullptr);
  ASSERT_EQ(moved_p->x+moved_p->y+moved_p->z, 56);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
