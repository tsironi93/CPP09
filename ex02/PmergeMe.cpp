#include "./PmergeMe.hpp"
#include <iostream>
#include <string>
#include <utility>

template <typename T>
static void printDebugs(T container, const std::string debug) {

  std::cout << "\n\n========================" << debug
            << "========================" << std::endl;
  for (auto it = container.begin(); it != container.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename T> static void jacob(T container, unsigned long n) {

  if (n > container.size()) {
    return;
  }

  int i = 0;
  for (auto it = container.begin(); it != container.end(); ++it) {
    if (i % n == n - 1 && *(it - n / 2) > *it) {
      for (unsigned long temp = i; temp > i - n / 2; --temp) {
        std::swap(container[temp], container[temp - n / 2]);
      }
    }
    ++i;
  }
  n = n << 1;
  printDebugs(container, "groups of " + std::to_string(n / 2));
  jacob(container, n);
}

template <>
void pMerge::merge<std::vector<unsigned long>>(
    std::vector<unsigned long> container) {
  std::cout << "Merging std::vector<unsigned int> of size: " << container.size()
            << std::endl;
  printDebugs(container, "BEGIN");
  // Merge sort logic
  jacob(container, 2);
}

template <>
void pMerge::merge<std::deque<unsigned long>>(
    std::deque<unsigned long> container) {
  std::cout << "Merging std::deque<unsigned int> of size: " << container.size()
            << std::endl;
  printDebugs(container, "BEGIN");
  // Merge sort logic
  jacob(container, 2);
}
