module;

#include <iostream>
#include <vector>
#include <format>
#include <set>
#include <stdexcept>

export module cnf;

using literal_t = int64_t;
using clause_t = std::vector<literal_t>;
using cnf_t = std::vector<clause_t>;

constexpr int clause_size = 3;

namespace cnf {

bool valid(const cnf_t cnf);

export class CNF {
  cnf_t m_value;
public:
  CNF(cnf_t cnf) {
    if (!valid(cnf)) {
      throw std::runtime_error("Invalid input.");
    }
    m_value = cnf;
  }
  void dump() const;
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

} // end namspace cnf
