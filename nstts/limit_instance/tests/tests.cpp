#include <gtest/gtest.h>

#include <cstdlib>
#include <limit_instance.hpp>

class Example : limit_instance<Example, 2> {
};

TEST(base, 1) {
  ASSERT_NO_THROW(Example());
  ASSERT_NO_THROW(Example());
  ASSERT_NO_THROW(Example());
  Example e1;
  Example e2;
  ASSERT_THROW(Example(), std::runtime_error);
}

TEST(base, 2) {
  ASSERT_NO_THROW(Example());
  Example* e1 = new Example();
  delete e1;
  Example* e2 = new Example();
  Example* e3 = new Example();
  ASSERT_THROW(Example(), std::runtime_error);
  delete e2;
  delete e3;
  Example e4;
  ASSERT_NO_THROW(Example());
}

/* RE: Creation of object via copy constructor
 * Using a copy constructor, you can create an unlimited number of object instances. 
 * To fix this, think about which base class constructor will be called 
 * before calling the copy constructor of the inheritor.
 *
 * Note: We can also count the usage of the move constructor, 
 * but I think it's pointless. With its normal use, one object will be created, 
 * and one will be dead very soon.
 */
TEST(review_test, copy_ctor) {
  Example origin;
  Example e1 {origin};
  ASSERT_THROW(Example e2 {origin}, std::runtime_error);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
