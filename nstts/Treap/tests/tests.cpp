#include <gtest/gtest.h>

TEST(SimpleTest, Test1) {
  EXPECT_EQ(1 + 1, 2);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS;
}
