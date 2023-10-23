
#include <gtest/gtest.h>

import cnf;

using cnf::CNF;

TEST(CNF, Init) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
}

TEST(CNF, Dump) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
  cnf.dump();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
