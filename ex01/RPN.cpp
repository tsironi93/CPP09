#include "./RPN.hpp"
#include <cctype>
#include <exception>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>

rpn::rpn(const std::string &str) {
  std::stack<int> rpnStack;
  std::istringstream tokens(str);
  std::string token;

  int result;
  while (tokens >> token) {
    if (token == "+" || token == "-" || token == "*" || token == "/") {
      if (rpnStack.size() < 2) {
        throw std::runtime_error("Wrong expression");
      }

      int right = rpnStack.top();
      rpnStack.pop();
      int left = rpnStack.top();
      rpnStack.pop();

      if (token == "+") {
        result = left + right;
      } else if (token == "-") {
        result = left - right;
      } else if (token == "*") {
        result = left * right;
      } else if (token == "/") {
        if (right == 0) {
          throw std::runtime_error("Division by zero is not a thing");
        }
        result = left / right;
      }
      rpnStack.push(result);
    } else {
      try {
        int num = std::stoi(token);
        rpnStack.push(num);
      } catch (...) {
        throw std::runtime_error("Error");
      }
    }
  }
  std::cout << result << std::endl;
}

rpn::~rpn() {}

void rpn::Do(const std::string &str) {
  try {
    rpn a(str);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
}
