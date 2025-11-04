#include <atomic>
namespace lfds {

template <typename T>
class Queue {
  struct Node {
    T data;
    Node* next;
  };

 private:
  std::atomic<Node> tail_;

 public:
  auto push(T&& item) -> void;
  auto pop() -> T;
};

template <typename T>
auto Queue<T>::push(T&& item) -> void {
  auto tail = tail_.load();
  auto new_node = Node{.data = item, .next = &tail};
  tail_.store(new_node);
}

template <typename T>
auto Queue<T>::pop() -> T {
  Node old_tail = tail_.load();
  Node new_tail = *old_tail.next;
  tail_.store(new_tail);
  return old_tail.data;
}

}  // namespace lfds
