#include "./RPN.hpp"
#include <iostream>

int main(int ac, char **av) {

  if (ac != 2) {
    std::cerr << "Requires just one argument" << std::endl;
    return -1;
  }

  rpn::Do(av[1]);

  return 0;
}
