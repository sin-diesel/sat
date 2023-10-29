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


// Solving using basic DPLL algorithm.
export std::optional<std::vector<bool>> solve(CNF& cnf) {
  // Step 1: choose random literal and assign true to it.
  select_literal(cnf);
  // Setup 2: unit propagation
  // unit_propagate(cnf);

  return std::nullopt;
}

} // end namespace sat
