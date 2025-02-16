#include <gtest/gtest.h>
#include "../src/Treap.h"

#include <cstdlib>
#include <vector>

TEST(TreapTests, Init) {
  Treap treap(3);
  ASSERT_TRUE(treap.sum() == 3);
}

TEST(TreapTests, Simple) {
  Treap treap(42);
  treap.insert(1);
  treap.insert(4);
  treap.insert(3);
  treap.insert(2);
  treap.insert(5);
  treap.insert(13);

  ASSERT_TRUE(treap.sum() == 70);
}

TEST(TreapTests, Equals) {
  Treap treap(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);
  treap.insert(1);

  ASSERT_TRUE(treap.sum() == 16);
}

TEST(TreapTests, BigData1) {
  Treap treap;
  int sum = 0;
  for (const int item = rand() >> 16; sum < 1 << 20; sum += item)
    treap.insert(item);

  ASSERT_TRUE(treap.sum() == sum);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
