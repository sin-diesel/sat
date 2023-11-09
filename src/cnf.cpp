module;

#include <iostream>
#include <vector>
#include <format>
#include <stdexcept>
#include <tuple>
#include <cstdint>
#include <algorithm>
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

  void set(variable_id_t variable_id, state new_state) {
    for (auto &clause: clauses_) {
      if (!clause.contains(variable_id)) {
        throw std::runtime_error("Attempting to insert set variable that does not exist.");
      }
      literal_t changed_variable = clause.at(variable_id);
      clause.insert_or_assign(variable_id, std::make_pair(changed_variable.first, new_state));
    }
  }

  clause_t getClause(std::size_t idx) { return clauses_[idx]; };
  // TODO: pass literal selection function as parameter
  variable_id_t select() {
    for (auto &clause: clauses_) {
      for (auto &literal: clause) {
        if (literal.second.second == state::UNASSIGNED) {
          return literal.first;
        }
      }
    }
    throw std::runtime_error("Could not select literal.");
  }

  std::vector<clause_t>::iterator removeClausesWithPureLiteral(variable_id_t id) {
    return clauses_.erase(std::remove_if(clauses_.begin(), clauses_.end(), [=](const clause_t& x) { return x.contains(id); }), clauses_.end());
  }

  std::vector<clause_t>::iterator eraseClause(std::vector<clause_t>::iterator it) {
    return clauses_.erase(it);
  }

  std::size_t size() { return clauses_.size(); };

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

