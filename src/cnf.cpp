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

namespace cnf {

const std::set<literal_t> allowed_literals({1, 2, 3, -1, -2, -3});

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
    for (const auto &literal: clause) {
      if (!allowed_literals.contains(literal)) {
        std::cerr << std::format("ERROR: detected invalid literal {}.", literal) << std::endl;
        return false;
      }
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
