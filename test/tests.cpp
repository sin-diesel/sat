
#include <gtest/gtest.h>

import sat;

TEST(CNF, Init) {
  CNF cnf({{1, 1, 1}, {1, 1, 1}});
}

TEST(CNF, Dump) {
  CNF cnf({{1, 1, 1}, {1, 1, 1}});
  cnf.dump();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
