
#include <stdexcept>
#include <gtest/gtest.h>

import cnf;

using sat::CNF;

TEST(CNF, Init) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
}

TEST(CNF, Dump) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
  cnf.dump();
}

TEST(CNF, DumpValues) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
  cnf.dumpValues();
}

TEST(CNF, InvalidInput) {
  try {
    CNF cnf({{1, 2, 3, 4}, {1, 2, 3}});
  }
  catch (std::runtime_error& error) {}
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
