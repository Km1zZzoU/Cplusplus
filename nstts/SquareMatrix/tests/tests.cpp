#include "../src/Matrix.cpp"
#include <gtest/gtest.h>

#include <cstdlib>

TEST(Smatrix, 1) {
  double diag[3] = {1.0, 2.0, 3.0};
  Smatrix m(diag, 3);

  ASSERT_EQ(m[0][0], 1.0);
  ASSERT_EQ(m[1][1], 2.0);
  ASSERT_EQ(m[2][2], 3.0);
}

TEST(Smatrix, 2) {
  double diag[3] = {4.0, 5.0, 6.0};
  Smatrix m(diag, 3);

  double sum = static_cast<double>(m);
  ASSERT_EQ(sum, 4.0 + 5.0 + 6.0);
}

TEST(Smatrix, 3) {
  double diag1[2] = {1.0, 2.0};
  double diag2[2] = {3.0, 4.0};

  Smatrix m1(diag1, 2);
  Smatrix m2(diag2, 2);
  Smatrix result = m1 + m2;

  ASSERT_EQ(result[0][0], 4.0);
  ASSERT_EQ(result[0][1], 0.0);
  ASSERT_EQ(result[1][0], 0.0);
  ASSERT_EQ(result[1][1], 6.0);
}

TEST(Smatrix, 4) {
  double diag1[2] = {1.0, 2.0};
  double diag2[2] = {3.0, 4.0};

  Smatrix m1(diag1, 2);
  Smatrix m2(diag2, 2);
  m1 += m2;

  ASSERT_EQ(m1[0][0], 4.0);
  ASSERT_EQ(m1[0][1], 0.0);
  ASSERT_EQ(m1[1][0], 0.0);
  ASSERT_EQ(m1[1][1], 6.0);
}

TEST(Smatrix, 5) {
  double diag[2] = {2.0, 3.0};
  Smatrix m(diag, 2);
  Smatrix result = m * 2;

  ASSERT_EQ(result[0][0], 4.0);
  ASSERT_EQ(result[1][1], 6.0);
}

TEST(Smatrix, 6) {
  double diag[2] = {2.0, 3.0};
  Smatrix m(diag, 2);
  m *= 2;

  ASSERT_EQ(m[0][0], 4.0);
  ASSERT_EQ(m[1][1], 6.0);
}

TEST(Smatrix, 7) {
  double diag1[2] = {1.0, 2.0};
  double diag2[2] = {3.0, 4.0};

  Smatrix m1(diag1, 2);
  Smatrix m2(diag2, 2);
  Smatrix result = m1 * m2;

  ASSERT_EQ(result[0][0], 3.0);
  ASSERT_EQ(result[0][1], 0.0);
  ASSERT_EQ(result[1][0], 0.0);
  ASSERT_EQ(result[1][1], 8.0);
}

TEST(Smatrix, 8) {
  double diag1[2] = {1.0, 2.0};
  double diag2[2] = {3.0, 4.0};

  Smatrix m1(diag1, 2);
  Smatrix m2(diag2, 2);
  m1 *= m2;

  ASSERT_EQ(m1[0][0], 3.0);
  ASSERT_EQ(m1[0][1], 0.0);
  ASSERT_EQ(m1[1][0], 0.0);
  ASSERT_EQ(m1[1][1], 8.0);
}

TEST(Smatrix, 9) {
  double diag1[2] = {7.0, 8.0};
  double diag2[2] = {7.0, 8.0};
  double diag3[2] = {9.0, 10.0};

  Smatrix m1(diag1, 2);
  Smatrix m2(diag2, 2);
  Smatrix m3(diag3, 2);

  ASSERT_TRUE(m1 == m2);
  ASSERT_FALSE(m1 == m3);
  ASSERT_TRUE(m1 != m3);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
