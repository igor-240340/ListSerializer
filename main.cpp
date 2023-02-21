#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "List.h"

static const std::string FILE_NAME = "list.bin";

static void FillList(List& list, int count);
static void MakeRandomLinksBetweenNodes(List& list);
static void SerializeToFile(List& list, std::string fileName = FILE_NAME);
static void DeserializeFromFile(List& list, std::string fileName = FILE_NAME);
static void PrintList(List& list, std::string headerText);

void main()
{
    List listOut;
    FillList(listOut, 10);
    MakeRandomLinksBetweenNodes(listOut);
    SerializeToFile(listOut);
    PrintList(listOut, "Source list");

    List listIn;
    DeserializeFromFile(listIn);
    PrintList(listIn, "Restored list");
}

void FillList(List& list, int count) {
    ListNode n;
    for (int i = 0; i < count; i++) {
        n.data = "node " + std::to_string(i);
        list.Add(n);
    }
}

void MakeRandomLinksBetweenNodes(List& list) {
    std::srand(std::time(nullptr));

    int listLen = list.Length();

    for (int i = 0; i < listLen; i++) {
        // Индекс, выходящий за пределы списка, обозначает nullptr.
        int randIndex = std::rand() % (listLen + 1);
        list[i]->rand = randIndex >= listLen ? nullptr : list[randIndex];
    }
}

void SerializeToFile(List& list, std::string fileName) {
    FILE* file;
    if (fopen_s(&file, fileName.c_str(), "wb") != 0) {
        std::cout << "Can't open file " << fileName.c_str() << std::endl;
        exit(1);
    }

    list.Serialize(file);

    fclose(file);
}

void DeserializeFromFile(List& list, std::string fileName) {
    FILE* file;
    if (fopen_s(&file, fileName.c_str(), "rb") != 0) {
        std::cout << "Can't open file " << fileName.c_str() << std::endl;
        exit(1);
    }

    list.Deserialize(file);

    fclose(file);
}

void PrintList(List& list, std::string headerText) {
    std::cout << headerText << std::endl;

    for (int i = 0; i < list.Length(); i++) {
        ListNode* node = list[i];
        std::string nodeName = node->data;
        std::string randName = node->rand == nullptr ? "nullptr" : node->rand->data;

        std::cout << nodeName << " points to " << randName << std::endl;
    }

    std::cout << std::endl;
}
