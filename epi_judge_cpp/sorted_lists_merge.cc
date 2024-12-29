#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  shared_ptr<ListNode<int>> R;
  ListNode<int>* p1 = L1.get();
  ListNode<int>* p2 = L2.get();
  shared_ptr<ListNode<int>>* pR = &R;

  // Take the smaller from one of the lists while both have elements
  while (p1 != nullptr && p2 != nullptr) {
    ListNode<int>*& rConsumed = p1->data < p2->data ? p1 : p2;
    
    *pR = make_shared<ListNode<int>>(rConsumed->data);
    pR = &(*pR)->next;
    rConsumed = rConsumed->next.get();
  }
  // we've consumed everything from one list, now just drain the other
  while (p1 != nullptr) {
    *pR = make_shared<ListNode<int>>(p1->data);
    pR = &(*pR)->next;
    p1 = p1->next.get();
  }
  while (p2 != nullptr) {
    *pR = make_shared<ListNode<int>>(p2->data);
    pR = &(*pR)->next;
    p2 = p2->next.get();
  }

  return R;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
