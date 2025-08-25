#include <string>

class rpn {
private:
  rpn() = delete;
  rpn(const std::string &str);
  rpn(const rpn &other) = delete;
  rpn operator=(const rpn &other) = delete;
  ~rpn();

public:
  static void Do(const std::string &str);
};
