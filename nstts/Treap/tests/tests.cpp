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

  /*Note: can be written in such way:
   * 
   * int default_val = 1;
   * std::size_t size = 16;
   * std::vector test(size, default_val);

   * for (int val : test) {
   *   treap.insert(val);
   * }

   * and so on
   */

  
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

  std::cout << treap.sum() << std::endl;
  ASSERT_TRUE(treap.sum() == 16);
}

TEST(TreapTests, BigData1) {
  Treap treap;
  int sum = 0;
  for (const int item = rand() >> 16; sum < 1 << 20; sum += item)
    treap.insert(item);

  ASSERT_TRUE(treap.sum() == sum);
}

TEST(ReviewTest, copy_ctr) {
    Treap* treap = new Treap;
    int test_size = 10;
    int test_val = 42;
    std::vector<int> test(test_size, test_val);

    for (int elem : test) {
        treap->insert(elem);
    }
    
    Treap copy(*treap);
    delete treap;
    
    ASSERT_TRUE(copy.sum() == test_size * test_val);
}

// in this fucntion using parameter type
// I'm explicitly specified that I need to 
// parameter will be copied
int buisness_logic(Treap t) {
    t.insert(42); // change of local copy, should not affect to the original one
    if (t.sum() > 131) {
        return 42;
    } else {
        return 17;
    }
    // at this point dstr of t will be called
    // and the data of it will be freed
    /* RE: in your solution at this point the shared data of copy
     * will be freed. Access to original treap will cause UB
     */
}

TEST(ReviewTest, copy_ctr_and_functions) {
    Treap treap; 
    int test_size = 10;
    int test_val = 42;
    std::vector<int> test(test_size, test_val);

    for (int elem : test) {
        treap.insert(elem);
    }
    
    /* RE: at this point copy ctr will just copy pointer
     * not the data itself.
     * So the original data will be freed in the dstr of copy
     */
    buisness_logic(treap); 

    // UB
    ASSERT_TRUE(treap.sum() == test_size * test_val);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
