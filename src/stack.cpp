#include <atomic>
namespace lfds {

template <typename T>
class Stack {
  struct Node {
    T data;
    Node* next;
  };

 private:
  std::atomic<Node*> top_;

 public:
  Stack();
  auto push(T&& item) -> void;
  auto pop() -> T;
};

template <typename T>
Stack<T>::Stack() {
  top_.store(nullptr);
}

template <typename T>
auto Stack<T>::push(T&& item) -> void {
  auto new_node = new Node{.data = std::move(item),
                           .next = top_.load(std::memory_order_relaxed)};
  while (!top_.compare_exchange_weak(new_node->next, new_node,
                                     std::memory_order_release,
                                     std::memory_order_acquire)) {
    // Empty
  }
}

template <typename T>
auto Stack<T>::pop() -> T {
  auto old_top = top_.load(std::memory_order_relaxed);
  while (old_top && !top_.compare_exchange_weak(old_top, old_top->next,
                                                std::memory_order_acquire,
                                                std::memory_order_acquire)) {
    // Empty
  }
  // Pending memory free
  return old_top ? std::move(old_top->data) : T{};
}

}  // namespace lfds
