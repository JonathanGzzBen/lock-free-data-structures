#include <iostream>

#include "queue.cpp"

auto main() -> int {
  std::cout << "Hello, World\n";

  lfds::Queue<int> queue;
  queue.push(1);
  queue.push(2);
  queue.push(3);
  auto popped = queue.pop();
  std::cout << "Popped: " << popped << "\n";
  return 0;
}
