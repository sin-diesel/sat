module;

#include <iostream>
#include <vector>
#include <format>
#include <stdexcept>
#include <unordered_map>

export module cnf;

using literal_t = int64_t;
using clause_t = std::vector<literal_t>;
using cnf_t = std::vector<clause_t>;

constexpr int clause_size = 3;

namespace sat {

bool valid(const cnf_t cnf);

export class CNF {
  cnf_t m_value;
  std::unordered_map<literal_t, bool> m_literal_values;
public:
  CNF(cnf_t cnf) {
    if (!valid(cnf)) {
      throw std::runtime_error("Invalid input.");
    }
    m_value = cnf;
    for (const auto &clause: m_value) {
      for (const auto &literal: clause) {
        if (!m_literal_values.contains(literal)) {
          m_literal_values.insert({literal, false});
        }
      }
    }
  }
  void dump() const;
  void dumpValues() const;
};

bool valid(cnf_t cnf) {
  for (const auto &clause: cnf) {
    if (clause.size() != clause_size) {
      std::cerr << std::format("ERROR: clause does not contain exactly {} elements.", clause_size) << std::endl;
      return false;
    }
  }
  return true;
}

void CNF::dump() const {
  for (const auto &clause: m_value) {
    std::cout << "(";
    for (const auto &literal: clause) {
      if (&literal != &clause[0]) {
        std::cout << "|" << literal;
      } else {
        std::cout << literal;
      }
    }
    std::cout << ") ";
  }
  std::cout << std::endl;
}

void CNF::dumpValues() const {
  for (const auto &it: m_literal_values) {
    std::cout << it.first << ": " << it.second << std::endl;
  }
}

} // end namspace cnf

