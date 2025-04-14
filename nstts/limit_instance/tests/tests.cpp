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

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
