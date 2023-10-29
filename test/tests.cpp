
#include <stdexcept>
#include <gtest/gtest.h>

import cnf;
import dpll;

using sat::CNF;

TEST(CNF, Init) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
}

TEST(CNF, Dump) {
  CNF cnf({{1, 2, 3}, {1, 2, 3}});
  cnf.dump();
}

TEST(CNF, InvalidInput) {
  try {
    CNF cnf({{1, 2, 3, 4}, {1, 2, 3}});
  }
  catch (std::runtime_error& error) {}
}

TEST(DPLL, DPLLSolve) {
   CNF cnf({{1, 2, 3}, {-1, 2, 3}});
   solve(cnf);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
