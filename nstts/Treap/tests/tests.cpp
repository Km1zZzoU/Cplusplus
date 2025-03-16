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

TEST(ReviewTest, RemoveLast) {
  Treap treap;
  treap.insert(42);
  treap.remove(42);
}

TEST(ReviewTest, Im_User_and_Im_dumb_and_Im_doing_what_I_want) {
  int test_size = 10000;
  Treap* treap = new Treap(0);

  // large, super non-BST, totally unbalanced Treap 
  Treap* curr = treap;
  for (std::size_t i = 1; i < test_size; i++) {
      curr->left = new Treap(i); // in the left sub-tree values always large than in the root
      curr = curr->left;
  }

  delete treap;
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
