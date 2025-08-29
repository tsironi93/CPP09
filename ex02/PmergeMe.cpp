#include "./PmergeMe.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T>
static void printDebugs(T container, const std::string debug) {

  std::cout << "\n\n========================" << debug
            << "========================" << std::endl;
  for (auto it = container.begin(); it != container.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

static int jacobNumber(int n) {
  return std::round((std::pow(2, n + 1) + std::pow(-1, n)) / 3);
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

  if (n > container.size()) {
    return;
  }

  n >>= 1;
  if (n * 3 > container.size()) {
    n >>= 1;
  }

  int jacobIndex = 2;
  int Jnum = jacobNumber(jacobIndex);
  std::cout << "\nJacob number is: " << Jnum << std::endl;

  std::vector<unsigned long> main;
  std::vector<unsigned long> pending;

  std::cout << "\nGroup size is: " << n << std::endl;

  bool stop = false;
  unsigned long j = 0;

  while (j < n * 2) {
    main.push_back(container[j++]);
  }

  while (j < container.size() - (container.size() % n)) {
    for (size_t k = 0; k < n && j < container.size(); ++k, ++j) {
      if (stop) {
        main.push_back(container[j]);
      } else {
        pending.push_back(container[j]);
      }
    }
    stop = !stop;
  }

  int numBGroups = (pending.size() / n);
  std::cout << "\nSize / n is: " << numBGroups << std::endl;

  while (Jnum <= numBGroups + 1) {
    for (auto it = main.begin() + n; it != main.end(); it += n) {
      if (pending[Jnum * n] < *it) {
        // append
      }
    }
    Jnum = jacobNumber(++jacobIndex);
  }

  // i = 0;
  // for (auto it = container.begin(); it != container.end(); ++it) {
  //   if (i % n == n - 1 && *(it - n / 2) > *it) {
  //     for (unsigned long temp = i; temp > i - n / 2; --temp) {
  //       std::swap(container[temp], container[temp - n / 2]);
  //     }
  //   }
  //   ++i;
  // }

  printDebugs(main, "Main chain");
  printDebugs(pending, "Pending chain");
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
