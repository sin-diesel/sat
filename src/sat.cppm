
export module sat;

import <vector>;
import <iostream>;

export class CNF {
  std::vector<std::vector<int>> m_value;
public:
  void dump() const;
}

CNF::dump() {
  for (const auto &element: m_value) {
    std::cout << "(";
    for (const auto &conjuctive: element) {
      std::cout << element << ",";
    }
    std::cout << ")" << std::endl;
  }
}
