#include "./PmergeMe.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
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

  printDebugs(main, "Main chain");
  printDebugs(pending, "Pending chain");

  static size_t numComparisons;
  int counter = 1;
  while (pending.size() != 0) {

    size_t startingBounds = 2 * n - 1;
    size_t endingBounds = pending.size() - 1;

    for (size_t k = startingBounds; k <= main.size(); k += n) {

      size_t insert_index = (Jnum - counter) * n - 1;

      if (insert_index > pending.size() || pending.size() == 0) {
        break;
      }

      std::cout << "pending < main : " << pending[insert_index] << " < "
                << main[k] << std::endl;

      if (main[k] > main[endingBounds]) {
        main.insert(main.begin() + k + 1,
                    pending.begin() + insert_index - n + 1,
                    pending.begin() + insert_index + 1);
        pending.erase(pending.begin() + insert_index - n + 1,
                      pending.begin() + insert_index + 1);
        printDebugs(main, "Insersion");
        printDebugs(pending, "Erasing");
        endingBounds = k + 1;
      } else if (pending[insert_index] < main[k]) {
        numComparisons++;
        main.insert(main.begin() + k - n + 1,
                    pending.begin() + insert_index - n + 1,
                    pending.begin() + insert_index + 1);
        pending.erase(pending.begin() + insert_index - n + 1,
                      pending.begin() + insert_index + 1);
        printDebugs(main, "Insersion");
        printDebugs(pending, "Erasing");
        endingBounds = k + 1;
      }
    }
    counter++;
  }

  int nonPartisipating = container.size() % n;
  while (nonPartisipating--) {
    main.push_back(container[container.size() - nonPartisipating]);
    container.clear();
    std::copy(main.begin(), main.end(), container.begin());
  }
  std::cout << "malaaaaaaaaaaaaaaaaaaaaaaaaakaaa\n"
            << "Number of Comparisons is : " << numComparisons << std::endl;
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
