#pragma once


#include "OpenAddressingHashTable.h"

inline uint64_t hashFunctionClastering(const std::string& str) {

    int val = 0;

    for (int i = 0; i < str.size(); ++i) {
        val += str[i]*i;
    }

    val = (7 * val + 13 * str.size());

    return val;
}

void run_assignment() {
    std::cout << __FUNCTION__ << std::endl;

    int table_size = 500;
    int data_size = 300;
    OpenAddressingHashTable<std::string> table(table_size, hashFunctionClastering);
    table.setRehashLoadFactor(.69);
    std::srand(std::time(0));
    for (size_t i = 0; i < data_size; i++)
    {
        int val = rand() % 100000;
        table.insert(std::to_string(val));
        table.printOneLine();
        std::cout << std::endl;
    }


}
