module;

#include <iostream>
#include <vector>

export module sat;

using literal_t = int64_t;
using clause_t = std::vector<literal_t>;
using cnf_t = std::vector<clause_t>;

namespace sat {

export class CNF {
  cnf_t m_value;
public:
  CNF(cnf_t cnf) {
    m_value = cnf;
  }
  void dump() const;
};

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

} // end namspace sat
