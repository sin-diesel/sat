module;

#include <iostream>
#include <vector>
#include <set>
#include <format>
#include <stdexcept>
#include <unordered_map>

export module cnf;

enum class state {
  FALSE = 0,
  TRUE = 1,
  UNASSIGNED = 3
};

using literal_t = int64_t;
using clause_t = std::unordered_map<literal_t, state>;
using cnf_t = std::vector<std::vector<literal_t>>;

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

export class CNF {
  std::vector<clause_t> m_clauses;
  std::vector<literal_t> m_literals;
public:
  CNF(cnf_t cnf);
  // void set(literal_t literal, bool value) {
  //   if (!m_clauses.contains(literal)) {
  //     throw std::runtime_error("Attempted to set nonexistent literal.");
  //   }
  //   m_literal_values.insert_or_assign(literal, value);
  // }
  // TODO: pass literal selection function as parameter
  literal_t select() {
    for (auto &clause: m_clauses) {
      for (auto &kv: clause) {
        if (kv.second == state::UNASSIGNED) {
           return kv.first;
        }
      }
    }
  }
  void dump() const;
};

CNF::CNF(cnf_t cnf) {
  if (!valid(cnf)) {
    throw std::runtime_error("Invalid input.");
  }
  for (std::size_t idx = 0; idx < cnf.size(); ++idx) {
    m_clauses.emplace_back();
    for (const auto &literal: cnf[idx]) {
      if (m_clauses[idx].contains(literal)) {
        throw std::runtime_error("Clause contains duplicate literals.");
      } else {
        m_clauses[idx].insert({literal, state::UNASSIGNED});
        m_literals.push_back(literal);
      }
    }

  }
}

void CNF::dump() const {
  std::cout << "{";
  for (const auto &clause: m_clauses) {
    std::cout << "{";
    for (auto it = clause.begin(), end = clause.end(); it != end; ++it) {
        if (std::next(it) != clause.end()) {
          std::cout << (*it).first << "|";
        } else {
          std::cout << (*it).first;
        }
    }
    std::cout << "}";
  }
  std::cout << "}" << std::endl;
}

} // end namspace cnf

