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

  std::cout << "========================" << debug
            << "========================" << std::endl;
  for (auto it = container.begin(); it != container.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

static int jacobNumber(int n) {
  return std::round((std::pow(2, n + 1) + std::pow(-1, n)) / 3);
}

template <typename T> static void jacob(T &container, unsigned long n) {

  if (n > container.size()) {
    printDebugs(container, "Final After req down");
    return;
  }

  if (n != 1) {
    size_t size = container.size();
    for (size_t i = n - 1; i < size; i += n) {
      std::cout << "Comparisons : " << container[i] << " > "
                << container[i - n / 2] << std::endl;
      if (i % n == n - 1 && container[i - n / 2] > container[i]) {
        for (unsigned long temp = i; temp > i - n / 2; --temp) {
          std::swap(container[temp], container[temp - n / 2]);
        }
      }
    }
  }

  n = n << 1;

  printDebugs(container, "groups of " + std::to_string(n / 2));
  jacob(container, n);

  if (n > container.size()) {
    return;
  }

  n = n >> 1;
  int jacobIndex = 2;
  int Jnum = jacobNumber(jacobIndex);
  // std::cout << "\nJacob number is: " << Jnum << std::endl;

  std::vector<unsigned long> main;
  std::vector<unsigned long> pending;

  // std::cout << "\nGroup size is: " << n << std::endl;

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

  // int numBGroups = (pending.size() / n);
  // std::cout << "\nSize / n is: " << numBGroups << std::endl;

  printDebugs(main, "Main chain");
  printDebugs(pending, "Pending chain");

  static size_t numComparisons;
  int counter = 1;
  size_t startingBounds = n - 1;
  size_t endingBounds = main.size() - 1;
  size_t insert_index;
  while (pending.size() != 0) {

    size_t jprev = Jnum;
    long int temp = (Jnum - counter) * n - 1;
    // std::cout << "temp is = " << temp << std::endl;
    if (temp < 0) {
      counter = 0 + jprev;
      Jnum = jacobNumber(++jacobIndex);
      insert_index = (Jnum - counter) * n - 1;
      endingBounds = main.size() - 1;

      while (insert_index >= pending.size()) {
        counter++;
        insert_index = (Jnum - counter) * n - 1;
      }

    } else {
      insert_index = temp;
    }

    // std::cout << "Temp after = " << insert_index << std::endl;

    for (size_t k = startingBounds; k <= main.size(); k += n) {

      if (insert_index >= pending.size() || pending.size() == 0) {
        break;
      }

      std::cout << "pending < main : " << pending[insert_index] << " < "
                << main[k] << std::endl;

      numComparisons++;
      if (pending[insert_index] < main[k]) {
        if (n != 1) {
          main.insert(main.begin() + k - n + 1,
                      pending.begin() + insert_index - n + 1,
                      pending.begin() + insert_index + 1);
          pending.erase(pending.begin() + insert_index - n + 1,
                        pending.begin() + insert_index + 1);
          endingBounds = k + n;
        } else {
          main.insert(main.begin() + k - n + 1, pending[insert_index]);
          pending.erase(pending.begin() + insert_index);
        }
        printDebugs(main, "Insersion after Comparisons");
        printDebugs(pending, "Erasing after Comparisons");
        break;
      } else if (main[k] == main[endingBounds] &&
                 endingBounds != main.size() - 1) {
        // std::cout << "=======No Comparisons Zone===========" << std::endl;
        if (n != 1) {
          main.insert(main.begin() + k + 1,
                      pending.begin() + insert_index - n + 1,
                      pending.begin() + insert_index + 1);
          pending.erase(pending.begin() + insert_index - n + 1,
                        pending.begin() + insert_index + 1);
          endingBounds = k;
        } else {
          main.insert(main.begin() + k + 1, main[k]);
          pending.erase(pending.begin() + k);
        }
        printDebugs(main, "Auto Insersion");
        printDebugs(pending, "Auto Erasing");
        break;
      } else if (k == main.size() - 1) {
        main.insert(main.end(), pending.begin() + insert_index - n + 1,
                    pending.begin() + 1);
        pending.erase(pending.begin() + insert_index - n + 1,
                      pending.begin() + insert_index + 1);
        endingBounds = k;
      }

      std::cout << "Ending Bounds Number: " << main[endingBounds] << std::endl;
    }
    counter++;
  }

  int nonPartisipating = container.size() % n;
  if (n != 1 || nonPartisipating != 0) {
    while (nonPartisipating--) {
      main.push_back(container[container.size() - nonPartisipating - 1]);
    }
  }
  container.clear();
  container.insert(container.end(), main.begin(), main.end());
  main.clear();
  pending.clear();
  std::cout << "malaaaaaaaaaaaaaaaaaaaaaaaaakaaa\n"
            << "Number of Comparisons is : " << numComparisons << std::endl;
  printDebugs(container, "Reqursion up groups of" + std::to_string(n));
  std::cout << "groups of " << n << std::endl;
}

template <>
void pMerge::merge<std::vector<unsigned long>>(
    std::vector<unsigned long> container) {
  std::cout << "Merging std::vector<unsigned int> of size: " << container.size()
            << std::endl;
  printDebugs(container, "BEGIN");
  // Merge sort logic
  jacob(container, 1);
  std::cout << std::is_sorted(container.begin(), container.end()) << std::endl;
}

template <>
void pMerge::merge<std::deque<unsigned long>>(
    std::deque<unsigned long> container) {
  std::cout << "Merging std::deque<unsigned int> of size: " << container.size()
            << std::endl;
  printDebugs(container, "BEGIN");
  // Merge sort logic
  jacob(container, 1);
  std::cout << std::is_sorted(container.begin(), container.end()) << std::endl;
}

// ./PmergeMe 11 2 17 0 16 8 6 15 10 3  1  18 9 14   19 12 5 4 20 13 7
