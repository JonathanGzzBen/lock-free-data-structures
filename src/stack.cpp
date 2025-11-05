#include <atomic>
#include <memory>
#include <optional>

namespace lfds {

template <typename T>
class Stack {
  struct Node {
    T data;
    std::shared_ptr<Node> next;
  };

 private:
  std::atomic<std::shared_ptr<Node>> top_;

 public:
  Stack();
  auto push(T item) -> void;
  auto pop() -> std::optional<T>;
};

template <typename T>
Stack<T>::Stack() {
  top_.store(nullptr, std::memory_order_relaxed);
}

template <typename T>
auto Stack<T>::push(T item) -> void {
  auto new_node = std::make_shared<Node>(std::move(item),
                                         top_.load(std::memory_order_relaxed));
  while (!top_.compare_exchange_weak(new_node->next, new_node,
                                     std::memory_order_release,
                                     std::memory_order_acquire)) {
    // Empty
  }
}

template <typename T>
auto Stack<T>::pop() -> std::optional<T> {
  auto old_top = top_.load(std::memory_order_relaxed);
  while (old_top && !top_.compare_exchange_weak(old_top, old_top->next,
                                                std::memory_order_acquire,
                                                std::memory_order_acquire)) {
    // Empty
  }
  if (!old_top) return std::nullopt;
  return std::move(old_top->data);
}
}  // namespace lfds
