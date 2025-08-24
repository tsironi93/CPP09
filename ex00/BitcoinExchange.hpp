#pragma once

#include <string>

#define BIG_NUMBER 1000

class bitcoinExchange {

private:
  bitcoinExchange() = delete;
  bitcoinExchange(const bitcoinExchange &other) = delete;
  bitcoinExchange &operator=(const bitcoinExchange &other) = delete;
  bitcoinExchange(const std::string &str);
  ~bitcoinExchange();

  std::string _date;
  double _value;

public:
  static void exchange(const std::string &string);
};
