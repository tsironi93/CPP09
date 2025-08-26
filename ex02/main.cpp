#include "./PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <ostream>
#include <string>

int main(int ac, char **av) {

  if (ac < 4) {
    std::cerr << "Required a sequence of numbers more than 3" << std::endl;
    return -1;
  }

  std::vector<std::string> argv;

  for (int i = 1; av[i]; ++i) {
    argv.push_back(av[i]);
  }

  std::vector<unsigned long> vectorMerge;
  std::deque<unsigned long> dequeMerge;

  for (auto it = argv.begin(); it != argv.end(); ++it) {
    if (!std::all_of(it->begin(), it->end(), ::isdigit)) {
      std::cout << "Characters found other than digits";
      return -2;
    }
    try {
      vectorMerge.push_back(std::stoul(*it));
      dequeMerge.push_back(std::stoul(*it));
    } catch (...) {
      std::cerr << "Number exeeds unsigned long... Malaka!!!" << std::endl;
      return -3;
    }
  }

  // ================Before==========================================
  std::cout << "Before:\t";
  for (auto it = argv.begin(); it != argv.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  pMerge::merge(vectorMerge);
  // pMerge::merge(dequeMerge);

  return 0;
}
