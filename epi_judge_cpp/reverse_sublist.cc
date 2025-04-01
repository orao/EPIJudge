#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  if (start >= finish) return L;

  // Note: Move the `head` pointer to the starting point
  std::shared_ptr<ListNode<int>>* head = &L;
  for (int i = 0; i < start - 1; ++i) {
    if (*head == nullptr) return L;
    head = &(*head)->next;
  }
  // Note: the node that `head` points to, eventually becomes the `last` node of the reeversed sublist, so it needs not be updated after this, it is always last.
  std::shared_ptr<ListNode<int>> last = *head;
  if (last == nullptr) return L;

  // Note: Until we reach the finish, keep taking the node after the `last` and inserting it at `head`, while attaching the remainder of the list to `last`.
  while (start++ < finish) {
    std::shared_ptr<ListNode<int>> current = last->next;

    if (current == nullptr) {
      return L;
    }

    last->next = current->next;
    current->next = *head;
    *head = current;
  }

  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
