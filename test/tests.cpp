
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
  for (auto &clause: cnf) {
  }
}

TEST(DPLL, UnitClauseCheck) {
  CNF cnf({{1, 2, 3}, {-1, -2, 3}});
  cnf.set(1, state::TRUE);
  cnf.set(2, state::TRUE);
  cnf.set(3, state::UNASSIGNED);
  ASSERT_EQ(sat::get_propagated_literal(cnf.getClause(0)), 3);
}

TEST(DPLL, UnitPropagate) {
  CNF cnf({{1, 2, 3}, {-1, -2, 3}});
  cnf.set(1, state::TRUE);
  cnf.set(2, state::TRUE);
  cnf.set(3, state::UNASSIGNED);
  unit_propagate(cnf);
  ASSERT_EQ(cnf.size(), 0);
}

TEST(DPLL, PolarLiteral) {
  CNF cnf({{1, 2, 3}, {-1, -2, 3}});
  ASSERT_TRUE(is_literal_polar(cnf, 3));
  ASSERT_FALSE(is_literal_polar(cnf, 1));
  ASSERT_FALSE(is_literal_polar(cnf, 2));
}

TEST(DPLL, PureLiteralElimination) {
  CNF cnf({{1, 2, 3}, {1, -2, -3}});
  eliminate_pure_literals(cnf);
  cnf.dump();
}

TEST(DPLL, PureLiteralEliminationIncomplete) {
  CNF cnf({{1, 2, 3}, {1, -2, -3}, {4, 2, 3}});
  eliminate_pure_literals(cnf);
  cnf.dump();
}

TEST (DPLL, ClauseAllAssigned) {
  CNF cnf({{1, 2, 3}, {4, 5, 6}});
  cnf.set(1, state::TRUE);
  cnf.set(2, state::TRUE);
  cnf.set(3, state::TRUE);
  ASSERT_FALSE(detect_false_clauses(cnf));
  cnf.dump();
}

TEST (DPLL, CheckFalseClauses) {
  CNF cnf({{1, 2, 3}, {4, 5, 6}});
  cnf.set(1, state::FALSE);
  cnf.set(2, state::FALSE);
  cnf.set(3, state::FALSE);
  ASSERT_TRUE(detect_false_clauses(cnf));
  cnf.dump();
}

TEST(DPLL, CheckFalseClausesWithNegatives) {
  CNF cnf({{-1, -2, -3}, {4, 5, 6}});
  cnf.set(1, state::TRUE);
  cnf.set(2, state::TRUE);
  cnf.set(3, state::TRUE);
  ASSERT_TRUE(detect_false_clauses(cnf));
  cnf.dump();
}

TEST(DPLL, Solve) {
  CNF cnf({{1, 2, 3}, {1, -2, -3}});
  solve(cnf);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
