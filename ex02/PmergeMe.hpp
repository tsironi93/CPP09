#pragma once

#include <deque>
#include <type_traits>
#include <vector>

class pMerge {
private:
  pMerge() = delete;
  ~pMerge() = delete;
  pMerge(int container) = delete;
  pMerge(const pMerge &other) = delete;
  pMerge &operator=(const pMerge &other) = delete;

public:
  template <typename T>
  static typename std::enable_if<
      std::is_same<T, std::vector<unsigned long>>::value ||
          std::is_same<T, std::deque<unsigned long>>::value,
      void>::type
  merge(T container);
};
