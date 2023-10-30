
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

TEST(CNF, CNFIterator) {
  CNF cnf({{1, 2, 3}, {-1, -2, 3}});
  for (auto &clause: cnf.clauses) {
  }
}

TEST(DPLL, UnitClauseCheck) {
  CNF cnf({{1, 2, 3}, {-1, -2, 3}});
  cnf.set(1, state::TRUE);
  cnf.set(2, state::TRUE);
  cnf.set(3, state::UNASSIGNED);
  ASSERT_TRUE(sat::is_clause_unit(cnf.clauses[0]));
}

TEST(DPLL, Solve) {
   CNF cnf({{1, 2, 3}, {-1, 2, 3}});
   solve(cnf);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
