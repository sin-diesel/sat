module;

#include <optional>
#include <vector>

import cnf;

export module dpll;

namespace sat {

// Solving using basic DPLL algorithm.
export std::optional<std::vector<bool>> solve(CNF& cnf) {
  // Step 1: choose random literal and assign true to it.
  auto chosen_literal = cnf.choose();
  cnf.set(chosen_literal, true);
  cnf.dump();
  return std::nullopt;
}

} // end namespace sat
