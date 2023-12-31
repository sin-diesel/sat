module;

#include <algorithm>
#include <optional>
#include <vector>
#include <cstdint>

import cnf;

export module dpll;

namespace sat {

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
  }
}

export bool is_literal_polar(CNF& cnf, variable_id_t id) {
  // If literal has the same polarity in every clause,
  // multiplication of all literal values will be positive number.
  // Otherwise, negative.
  int sum = 0;
  int nids = 0;
  for (auto it = cnf.begin(), end = cnf.end(); it != end; ++it) {
    clause_t current_clause = *it;
    if (current_clause.contains(id)) {
      // Normalize
      auto elem = current_clause.at(id);
      auto first = elem.first;
      sum += static_cast<int>(current_clause.at(id).first / id);
      nids++;
    }
  }
  return (sum - nids) == 0;
}

export void eliminate_pure_literals(CNF& cnf) {
  std::vector<variable_id_t> checked_ids;
  for (auto it = cnf.begin(), end = cnf.end(); it != end; ++it) {
    clause_t clause = *it;
    for (auto &literal: clause) {
      if (is_literal_polar(cnf, literal.first) && (std::find(checked_ids.begin(), checked_ids.end(), literal.first) == checked_ids.end())) {
        cnf.markEmpty(literal.first);
        checked_ids.push_back(literal.first);
        break;
      }
      checked_ids.push_back(literal.first);
    }
  }
  cnf.removeEmptyClauses();
}

bool is_literal_true(literal_t literal) {
  if (literal.second == state::TRUE) {
    return (literal.first > 0) ? true: false;
  } else {
    return (literal.first > 0) ? false: true;
  }
}

bool is_clause_true(clause_t& clause) {
  if (!check_assigned(clause)) {
    return true;
  }
  for (auto literal: clause) {
    if (is_literal_true(literal.second)) {
      return true;
    }
  }
  return false;
}

export bool detect_false_clauses(CNF& cnf) {
  for (auto it = cnf.begin(), end = cnf.end(); it != end; ++it) {
    clause_t clause = *it;
    if (!is_clause_true(clause)) {
      return true;
    }
  }
  return false;
}


// Solving using basic DPLL algorithm.
export bool solve(CNF& cnf) {
  // Step 1: unit propagation
  unit_propagate(cnf);
  if (detect_false_clauses(cnf)) {
    return false;
  }
  cnf.removeAssignedClauses();
  // Step 2: pure literal elimination
  eliminate_pure_literals(cnf);

  // Stopping conditions
  if (cnf.size() == 0) {
    return true;
  }
  if (detect_false_clauses(cnf)) {
    return false;
  }
  // Step 3: set another literal to true / false and to recursive search
  variable_id_t literal_id = cnf.select();
  cnf.set(literal_id, state::TRUE);
  bool solution_result = solve(cnf);
  if (!solution_result) {
    cnf.set(literal_id, state::FALSE);
    solution_result = solve(cnf);
  }
  return solution_result;
}

} // end namespace sat
