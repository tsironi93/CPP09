#include "./BitcoinExchange.hpp"
#include <list>
#include <stdexcept>
#include <string>

bitcoinExchange::bitcoinExchange(std::string &str) {
  if (str == "date | value")
    return;
  if (str.find('|') == std::string::npos ||
      str.find('|') != str.find_last_of('|')) {
    throw std::runtime_error("No value in the line");
    return;
  }
  std::list<std::pair<int, std::string>> hello;
}

bitcoinExchange::~bitcoinExchange() {}

// void bitcoinExchange::exchange(std::string &string) {}
