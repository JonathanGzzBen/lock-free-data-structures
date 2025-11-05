#include <iostream>

#include "stack.cpp"

auto main() -> int {
  std::cout << "Hello, World\n";

  lfds::Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);

  for (int i = 0; i < 4; i++) {
    auto popped = stack.pop();
    if (popped) {
      std::cout << "Popped: " << *popped << "\n";
    }
  }
  return 0;
}
