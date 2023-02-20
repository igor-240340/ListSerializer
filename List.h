#pragma once

#include <map>

struct ListNode {
    ListNode* prev = nullptr;
    ListNode* next = nullptr;

    ListNode* rand = nullptr;
    std::string data;
};

class List
{
public:
    ListNode* Add(const ListNode& node);

    void Serialize(FILE* file);
    void Deserialize(FILE* file);

    int Length() const { return count; }

    ListNode* operator[] (int index);

    ~List();
    void Clear();

private:
    int count = 0;

    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    std::map<int, ListNode*> indexToNode;
};
