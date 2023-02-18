#pragma once

#include <iostream>
#include <map>
#include <stdio.h>
#include <list>

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

    int Count() const { return this->count; }

    ListNode* operator[] (int index);

private:
    ListNode* head = nullptr;
    ListNode* tail = nullptr;

    std::map<int, ListNode*> indexNodePair;

    int count = 0;
};
