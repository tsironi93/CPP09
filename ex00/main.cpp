#include "./BitcoinExchange.hpp"
#include <cerrno>
#include <cstdio>
#include <fstream>
#include <iostream>

int main(int ac, char *av[]) {

  if (ac != 2) {
    std::cerr << "This program takes as an single argument a file" << std::endl;
    return 1;
  }

  std::ifstream fd(av[1]);
  if (!fd) {
    std::perror("Error opening the file");
    return errno;
  }

  std::string line;
  while (std::getline(fd, line)) {
    bitcoinExchange::exchange(line);
  }

  fd.close();

  return 0;
}
