#include "./BitcoinExchange.hpp"
#include <cctype>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <stdexcept>
#include <string>
#include <utility>

std::string trim(const std::string &s) {
  size_t start = s.find_first_not_of(" \t");
  size_t end = s.find_last_not_of(" \t");
  return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

bitcoinExchange::bitcoinExchange(const std::string &str) {
  if (str == "date | value")
    return;

  size_t pipePos = str.find('|');
  if (pipePos == std::string::npos || str.find_last_of('|') != pipePos) {
    throw std::runtime_error(
        "Error: Invalid format. Missing or having multiple pipes");
  }

  std::string date = trim(str.substr(0, pipePos));
  std::string value = trim(str.substr(pipePos + 1));

  std::regex dateRegex("^\\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12]\\d|3[01])$");
  if (!std::regex_match(date, dateRegex)) {
    throw std::runtime_error("Error: Invalid date format");
  }

  if (value.empty())
    throw std::runtime_error("No value in the line");

  char *end;
  double dvalue = std::strtod(value.c_str(), &end);
  if (*end != '\0') {
    throw std::runtime_error("Error: Not a valid number");
  }

  if (dvalue < 0)
    throw std::runtime_error("Error: Not a positive number");
  else if (dvalue > BIG_NUMBER)
    throw std::runtime_error("Error: too large of a number");

  // std::cout << "Result: " << date << " and " << value << std::endl;
  _date = date;
  _value = dvalue;
}

bitcoinExchange::~bitcoinExchange() {}

void bitcoinExchange::exchange(const std::string &string) {

  std::ifstream fd("./data.csv");
  if (!fd) {
    std::perror("Error opening the csv file");
    return;
  }

  std::list<std::pair<std::string, double>> csv;
  std::string line;
  char *end;
  std::string csvDate;
  std::string csvValueStr;
  double csvValue;
  size_t commaPos;

  while (std::getline(fd, line)) {
    commaPos = line.find(',');

    if (commaPos == std::string::npos) {
      continue;
    }

    csvDate = line.substr(0, commaPos);
    csvValueStr = line.substr(commaPos + 1);
    csvValue = std::strtod(csvValueStr.c_str(), &end);
    if (*end != '\0')
      continue;

    csv.emplace_back(csvDate, csvValue);
  }
  fd.close();

  try {
    bitcoinExchange a(string);

    for (auto it = csv.begin(); it != csv.end(); ++it) {
      if (a._date == it->first) {
        std::cout << a._date << " => " << a._value << " = "
                  << a._value * it->second << std::endl;
        break;
      } else if (a._date < it->first) {
        if (it == csv.begin()) {
          std::cout << "Error: no earlier date available" << std::endl;
          break;
        }
        auto prev = std::prev(it);
        std::cout << a._date << " => " << a._value << " = "
                  << a._value * prev->second << std::endl;
        break;
      }
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
