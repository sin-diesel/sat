module;

#include <optional>
#include <vector>

import cnf;

export module dpll;

namespace sat {

void select_literal(CNF& cnf) {
  variable_id_t selected_id = cnf.select();
  cnf.set(selected_id, state::TRUE);
}

export std::optional<variable_id_t> get_propagated_literal(const clause_t &clause) {
  unsigned unassigned_literals = 0;
  variable_id_t candidate;
  for (const auto &literal: clause) {
    if (literal.second.second == state::UNASSIGNED) {
      unassigned_literals += 1;
      candidate = literal.first;
    }
  }
  return (unassigned_literals == 1) ? std::optional(candidate) : std::nullopt;
}

export void unit_propagate(CNF& cnf) {
  for (auto it = cnf.begin(), end = cnf.end(); it != end; ++it) {
    clause_t clause = *it;
    auto opt_propagate_candidate = get_propagated_literal(clause);
    if (opt_propagate_candidate.has_value()) {
      variable_id_t propagate_candidate = opt_propagate_candidate.value();
      // Set literals in all clauses to their corresponding value
      for (auto &entry: clause) {
        if (entry.second.first < 0) {
          cnf.set(entry.first, state::FALSE);
        } else {
          cnf.set(entry.first, state::TRUE);
        }
      }
    }
    it = cnf.eraseClause(it);
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
