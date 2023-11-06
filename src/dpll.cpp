module;

#include <optional>
#include <vector>

import cnf;

export module dpll;

namespace sat {

void select_literal(CNF& cnf) {
  literal_t selected_literal = cnf.select();
  cnf.set(selected_literal, state::TRUE);
}

export std::optional<literal_t> get_propagated_literal(const clause_t &clause) {
  unsigned unassigned_literals = 0;
  variable_id_t candidate;
  for (const auto &literal: clause) {
    if (literal.second.second == state::UNASSIGNED) {
      unassigned_literals += 1;
      candidate = literal.first;
    }
  }
  return (unassigned_literals == 1) ? candidate : std::nullopt;
}

export void unit_propagate(CNF& cnf) {
  for (auto it = cnf.clauses.begin(), end = cnf.clauses.end(); it != end; ++it) {
    clause_t clause = *it;
    auto opt_propagate_candidate = get_propagated_literal(clause):
    if (opt_propagate_candidate.has_value()) {
      propagate_candidate = opt_propagate_candidate.value();
      // Set literals in all clauses to their corresponding value
      for (auto &entry: clause) {
        if (entry.second.first < 0) {
          cnf.set(literal.first, state::FALSE);
        } else {
          cnf.set(literal.first, state::TRUE);
        }
      }
    }
  }
}


// Solving using basic DPLL algorithm.
export std::optional<std::vector<bool>> solve(CNF& cnf) {
  // Step 1: choose random literal and assign true to it.
  select_literal(cnf);
  // Setup 2: unit propagation
  unit_propagate(cnf);
  cnf.dump();
  return std::nullopt;
}

} // end namespace sat
