#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* mergeKLists(std::vector<ListNode*>& lists) {
    auto comp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;
    };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comp)> minHeap(comp);

    for (ListNode* list : lists) {
        if (list) {
            minHeap.push(list);
        }
    }

    ListNode dummy;
    ListNode* current = &dummy;

    while (!minHeap.empty()) {
        ListNode* minNode = minHeap.top();
        minHeap.pop();

        current->next = minNode;
        current = current->next;

        if (minNode->next) {
            minHeap.push(minNode->next);
        }
    }

    return dummy.next;
}

void printList(ListNode* head) {
    while (head) {
        std::cout << head->val;
        if (head->next) {
            std::cout << "->";
        }
        head = head->next;
    }
    std::cout << std::endl;
}

int main() {
    // Input: [[1,4,5],[1,3,4],[2,6]]
    std::vector<ListNode*> lists;
    lists.emplace_back(new ListNode(1, new ListNode(4, new ListNode(5, nullptr))));
    lists.emplace_back(new ListNode(1, new ListNode(3, new ListNode(4, nullptr))));
    lists.emplace_back(new ListNode(2, new ListNode(6, nullptr)));

    ListNode* mergedList = mergeKLists(lists);

    // Output: 1->1->2->3->4->4->5->6
    printList(mergedList);

    ListNode* temp;
    while (mergedList) {
        temp = mergedList;
        mergedList = mergedList->next;
        delete temp;
    }

    return 0;
}