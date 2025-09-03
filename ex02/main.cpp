#include "./PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <iostream>
#include <ratio>
#include <string>

template <typename T> static bool hasDuplicates(T container) {
  std::sort(container.begin(), container.end());
  return std::adjacent_find(container.begin(), container.end()) !=
         container.end();
}

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

  if (hasDuplicates(vectorMerge)) {
    std::cerr << "Duplicates found in the sequence" << std::endl;
    return -4;
  }

  auto startVector = std::chrono::high_resolution_clock::now();
  pMerge::merge(vectorMerge);
  auto endVector = std::chrono::high_resolution_clock::now();
  auto vectorTime =
      std::chrono::duration<double, std::micro>(endVector - startVector);
  std::cout << "The time that it took the vector container is: "
            << vectorTime.count() << " microseconds." << std::endl;

  auto start = std::chrono::high_resolution_clock::now();
  pMerge::merge(dequeMerge);
  auto end = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration<double, std::micro>(end - start);
  std::cout << "The time that it took the deque container is: " << time.count()
            << " microseconds." << std::endl;

  return 0;
}
