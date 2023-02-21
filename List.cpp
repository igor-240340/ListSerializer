#include <iostream>
#include <string>

#include "List.h"

List::~List() {
    Clear();
}

void List::Clear() {
    if (count == 0)
        return;

    indexToNode.clear();

    tail = nullptr;

    // Удаляем объекты начиная с головы и до последнего элемента.
    ListNode* cur;
    while (head != nullptr) {
        cur = head;
        head = head->next;
        delete cur;
    };

    count = 0;
}

ListNode* List::Add(const ListNode& node) {
    ListNode* newItem = new ListNode;
    newItem->data = node.data;

    if (count == 0)
        head = tail = newItem;
    else {
        tail->next = newItem;
        newItem->prev = tail;
        tail = newItem;
    }

    indexToNode.insert(std::pair<int, ListNode*>(count, newItem));
    count++;

    return newItem;
}

// O(N)
void List::Serialize(FILE* file) {
    // В файле элемент rand будет представлен своим индексом в списке.
    std::map<ListNode*, int> nodeToIndex;
    for (auto const& i : indexToNode)
        nodeToIndex.insert(std::pair<ListNode*, int>(i.second, i.first));

    ListNode* cur = head;
    while (cur != nullptr) {
        int randIndex = cur->rand == nullptr ? -1 : nodeToIndex[cur->rand];
        fwrite(&randIndex, sizeof(randIndex), 1, file); // Пишем в файл число в 4 байтах.
        fwrite(cur->data.c_str(), cur->data.length() + 1, 1, file); // Пишем следом строку вместе с \0.

        cur = cur->next;
    };
}

// O(N)
// Сейчас предполагается, что эта функция будет вызвана только для нового (то есть для совершенно пустого) списка.
// Читает файл последовательно и один раз.
void List::Deserialize(FILE* file) {
    int randIndex;
    char c;
    std::string s;
    ListNode n;
    std::map<ListNode*, int> nodeToRandIndex;
    
    // Считываем индекс для rand.
    while (fread(&randIndex, sizeof(randIndex), 1, file) == 1) {
        // Затем посимвольно читаем поле data пока не дойдём до \0.
        s = "";
        while (fread(&c, sizeof(c), 1, file) == 1) {
            if (c == '\0') {
                n.data = s;
                ListNode* newNode = Add(n);
                nodeToRandIndex.insert(std::pair<ListNode*, int>(newNode, randIndex));

                break;
            }

            s += c;
        }
    }

    // Восстанавливаем связи между узлами по полю rand.
    ListNode* cur = head;
    while (cur != nullptr) {
        int randIndex = nodeToRandIndex[cur];
        cur->rand = randIndex == -1 ? nullptr : indexToNode[randIndex];
        cur = cur->next;
    };
}

ListNode* List::operator[](int index) {
    return indexToNode[index];
}
