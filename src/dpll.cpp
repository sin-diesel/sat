module;

#include <optional>
#include <vector>

import cnf;

export module dpll;

namespace sat {

// Solving using basic DPLL algorithm.
export std::optional<std::vector<bool>> solve(CNF& cnf) {
  // Step 1: choose random literal and assign true to it.
  auto selected_literal = cnf.select();
  cnf.dump();
  // cnf.set(chosen_literal, true);
  // cnf.dump();
  // Setup 2: unit propagation

  return std::nullopt;
}

} // end namespace sat
