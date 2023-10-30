module;

#include <iostream>
#include <vector>
#include <format>
#include <stdexcept>
#include <unordered_map>

export module cnf;

export enum class state {
  FALSE = 0,
  TRUE = 1,
  UNASSIGNED = 3
};

export using literal_t = int64_t;
export using clause_t = std::unordered_map<literal_t, state>;
export using cnf_t = std::vector<std::vector<literal_t>>;

export constexpr int default_clause_size = 3;

namespace sat {

bool valid(const std::vector<std::vector<literal_t>> cnf) {
  for (const auto &clause: cnf) {
    if (clause.size() != default_clause_size) {
      std::cerr << std::format("ERROR: clause does not contain exactly {} elements.", default_clause_size) << std::endl;
      return false;
    }
  }
  return true;
}

export bool is_negated(literal_t literal_value) {
  return (literal_value < 0) ? true : false;
}

export class CNF {
  std::vector<clause_t> m_clauses;
  std::vector<literal_t> m_literals;
public:
  CNF(cnf_t cnf);
  void set(literal_t literal, state new_state) {
    for (auto &clause: m_clauses) {
      if (clause.contains(literal)) {
        clause.insert_or_assign(literal, new_state);
      }
    }
  }
  // TODO: pass literal selection function as parameter
  literal_t select() {
    for (auto &clause: m_clauses) {
      for (auto &kv: clause) {
        if (kv.second == state::UNASSIGNED) {
           return kv.first;
        }
      }
    }
    throw std::runtime_error("Could not select literal.");
  }

  clause_t& getClause(std::size_t idx) { return m_clauses[idx]; };

  std::vector<clause_t>::iterator begin() { return m_clauses.begin(); };
  std::vector<clause_t>::iterator end() { return m_clauses.end(); };

  void dump() const;
};

CNF::CNF(cnf_t cnf) {
  if (!valid(cnf)) {
    throw std::runtime_error("Invalid input.");
  }
  for (std::size_t idx = 0; idx < cnf.size(); ++idx) {
    m_clauses.emplace_back();
    for (const auto &literal: cnf[idx]) {
      auto abs_literal = std::abs(literal);
      if (m_clauses[idx].contains(abs_literal)) {
        throw std::runtime_error("Clause contains duplicate literals.");
      } else {
        m_clauses[idx].insert({abs_literal, state::UNASSIGNED});
        m_literals.push_back(abs_literal);
      }
    }

  }
}

void CNF::dump() const {
  std::cout << "{";
  for (const auto &clause: m_clauses) {
    std::cout << "{";
    for (auto it = clause.begin(), end = clause.end(); it != end; ++it) {
        std::cout << (*it).first << " ";
        std::cout << "state: " << static_cast<int>((*it).second);
        if (std::next(it) != clause.end()) {
          std::cout << "|";
        }
    }
    std::cout << "}";
  }
  std::cout << "}" << std::endl;
}

} // end namspace cnf

