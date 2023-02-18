#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "List.h"

ListNode* GetRandomNodeOrNull(List& list) {
    int i = std::rand() % (list.Count() + 1);
    return i >= list.Count() ? nullptr : list[i];
}

int main()
{
    std::srand(std::time(nullptr));

    List list;

    ListNode n;
    for (int i = 0; i < 10; i++) {
        n.data = "node " + std::to_string(i);

        if (list.Count() != 0)
            n.rand = GetRandomNodeOrNull(list);

        list.Add(n);
    }

    FILE* file;
    /*if (fopen_s(&file, "list.bin", "wb") != 0) {
        std::cout << "Can't open file list.bin." << std::endl;
        exit(1);
    }*/

    /*for (int i = 0; i < list.Count(); i++) {
        std::cout << list[i]->data << " points to " << (list[i]->rand != nullptr ? list[i]->rand->data : "nullptr") << std::endl;
    }*/

    //list.Serialize(file);

    //fclose(file);

    if (fopen_s(&file, "list.bin", "rb") != 0) {
        std::cout << "Can't open file list.bin." << std::endl;
        exit(1);
    }

    List listDes;
    listDes.Deserialize(file);

    for (int i = 0; i < listDes.Count(); i++) {
        std::cout << listDes[i]->data << " points to " << (listDes[i]->rand != nullptr ? listDes[i]->rand->data : "nullptr") << std::endl;
    }

    //std::cout << "";

    //std::string writeString = "Hello world!";
    //fwrite(writeString.c_str(), writeString.size() + 1, 1, file);


    //std::string readString;
    //fread(&readString, sizeof(readString), 1, file);

    //fclose(file);

    //std::cout << "readString " << readString << std::endl
}
