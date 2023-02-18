#include <string>

#include "List.h"

ListNode* List::Add(const ListNode& node) {
    std::cout << "List::Insert" << std::endl;

    ListNode* newItem = new ListNode;
    newItem->data = node.data;
    newItem->rand = node.rand;

    if (count == 0) {
        head = newItem;
        tail = newItem;
    }
    else {
        tail->next = newItem;
        newItem->prev = tail;
        tail = newItem;
    }

    indexNodePair.insert(std::pair<int, ListNode*>(count, newItem));

    count++;

    return newItem;
}

void List::Serialize(FILE* file) {
    std::cout << "List::Serialize" << std::endl;

    std::map<ListNode*, int> nodeToIndex;

    ListNode* cur = head;
    int i = 0;
    while (cur != nullptr) {
        std::cout << cur->data << std::endl;

        nodeToIndex.insert(std::pair<ListNode*, int>(cur, i++));
        cur = cur->next;
    };

    cur = head;
    while (cur != nullptr) {
        int randIndex = cur->rand == nullptr ? -1 : nodeToIndex[cur->rand];
        fwrite(&randIndex, sizeof(randIndex), 1, file);
        fwrite(cur->data.c_str(), cur->data.length() + 1, 1, file);

        cur = cur->next;
    };
}

void List::Deserialize(FILE* file) {
    std::cout << "List::Deserialize" << std::endl;

    char c;
    std::string s;
    ListNode n;
    int randIndex;
    int i = 0;
    std::map<ListNode*, int> nodeToRandIndex;
    std::map<int, ListNode*> indexToNode;
    while (fread(&randIndex, sizeof(randIndex), 1, file) == 1) {
        while (fread(&c, sizeof(c), 1, file) == 1) {
            if (c == '\0') {
                std::cout << "node.data: " << s;
                std::cout << "node.rand: " << randIndex;

                n.data = s;
                ListNode* r = Add(n);
                nodeToRandIndex.insert(std::pair<ListNode*, int>(r, randIndex));
                indexToNode.insert(std::pair<int, ListNode*>(i, r));
                s = "";
                i++;

                break;
            }

            s += c;
        }
    }

    ListNode* cur = head;
    while (cur != nullptr) {
        int randIndex = nodeToRandIndex[cur];
        cur->rand = randIndex == -1 ? nullptr : indexToNode[randIndex];
        cur = cur->next;
    };
}

ListNode* List::operator[](int index) {
    return indexNodePair[index];
}
