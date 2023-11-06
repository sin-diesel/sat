module;

#include <iostream>
#include <vector>
#include <format>
#include <stdexcept>
#include <tuple>
#include <cstdint>
#include <unordered_map>

export module cnf;

export enum class state {
  FALSE = 0,
  TRUE = 1,
  UNASSIGNED = 3
};

export using variable_id_t = std::uint64_t;
export using variable_value_t = std::int64_t;
export using variable_t = std::int64_t;
export using literal_t = std::pair<variable_value_t, state>;
export using clause_t = std::unordered_map<variable_id_t, literal_t>;
export using cnf_t = std::vector<std::vector<variable_t>>;

export constexpr int default_clause_size = 3;

namespace sat {

bool valid(const cnf_t cnf) {
  for (const auto &clause: cnf) {
    if (clause.size() != default_clause_size) {
      std::cerr << std::format("ERROR: clause does not contain exactly {} elements.", default_clause_size) << std::endl;
      return false;
    }
  }
  return true;
}

export class CNF {
  std::vector<clause_t> clauses_;
public:
  CNF(cnf_t cnf);
  // void set(literal_t literal, state new_state) {
  //   for (auto &clause: clauses) {
  //     if (clause.contains(literal)) {
  //       clause.insert_or_assign(literal, new_state);
  //     }
  //   }
  // }
  // TODO: pass literal selection function as parameter
  // literal_t select() {
  //   for (auto &clause: clauses) {
  //     for (auto &literal: clause) {
  //       if (literal.second == state::UNASSIGNED) {
  //          return literal.first;
  //       }
  //     }
  //   }
  //   throw std::runtime_error("Could not select literal.");
  // }
  std::vector<clause_t>::iterator begin() { return clauses_.begin(); }
  std::vector<clause_t>::iterator end() { return clauses_.end(); }
  void dump() const;
};

CNF::CNF(cnf_t cnf) {
  if (!valid(cnf)) {
    throw std::runtime_error("Invalid input.");
  }
  for (std::size_t idx = 0; idx < cnf.size(); ++idx) {
    clauses_.emplace_back();
    for (const variable_value_t &literal: cnf[idx]) {
      variable_id_t literal_id = std::abs(literal);
      if (clauses_[idx].contains(literal_id)) {
        throw std::runtime_error("Clause contains duplicate literals.");
      } else {
        clauses_[idx].insert(std::make_pair(literal_id, std::make_pair(literal, state::UNASSIGNED)));
      }
    }

  }
}

void CNF::dump() const {
  std::cout << "{" << std::endl;
  for (const clause_t &clause: clauses_) {
    std::cout << "{" << std::endl;
    for (auto it = clause.begin(), end = clause.end(); it != end; ++it) {
        std::cout << "id: " << (*it).first << " ";
        std::cout << "value: " << (*it).second.first << " ";
        std::cout << "state: " << static_cast<int>((*it).second.second);
        std::cout << std::endl;
    }
    std::cout << "}" << std::endl;
  }
  std::cout << "}" << std::endl;
}

} // end namspace cnf

