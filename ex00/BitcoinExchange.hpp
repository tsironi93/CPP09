#pragma once

#include <string>

class bitcoinExchange {

private:
  bitcoinExchange() = delete;
  bitcoinExchange(const bitcoinExchange &other) = delete;
  bitcoinExchange &operator=(const bitcoinExchange &other) = delete;
  bitcoinExchange(std::string &str);
  ~bitcoinExchange();

public:
  static void exchange(std::string &string);
};
