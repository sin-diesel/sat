module;

#include <optional>
#include <vector>
#include <cstdint>

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

export bool is_literal_polar(CNF& cnf, variable_id_t id) {
  // If literal has the same polarity in every clause,
  // multiplication of all literal values will be positive number.
  // Otherwise, negative.
  int multiplication_product = 1;
  for (auto it = cnf.begin(), end = cnf.end(); it != end; ++it) {
    clause_t current_clause = *it;
    if (current_clause.contains(id)) {
      // Normalize
      multiplication_product *= current_clause.at(id).first / id;
    }
  }
  return multiplication_product > 0;
}

export void eliminate_pure_literals(CNF& cnf) {
  for (auto it = cnf.begin(), end = cnf.end(); it != end; ++it) {
  
  }
}


// Solving using basic DPLL algorithm.
export std::optional<std::vector<bool>> solve(CNF& cnf) {
  // Step 1: choose random literal and assign true to it.
  select_literal(cnf);
  // Step 2: unit propagation
  unit_propagate(cnf);
  // Step 3: pure literal elimination
  eliminate_pure_literals(cnf);
  cnf.dump();
  return std::nullopt;
}

} // end namespace sat
