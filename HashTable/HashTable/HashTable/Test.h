#pragma once

#include "HashTable.h"
#include "OpenAddressingHashTable.h"

inline uint64_t hashFunctionStr(const std::string &str){

    int val = 0;

    for (int i = 0; i < str.size(); ++i) {
        val += str[i];
    }

    return val;
}


namespace TEST_HASH_TABLE
{

void test_hash_table_REMOVE_1(){
    std::cout << __FUNCTION__ << std::endl;

    HashTable<std::string> table(20, hashFunctionStr);
    table.insert("abc");
    table.insert("bca");
    table.insert("ddddd");
    table.insert("arman");
    table.insert("sadasdsad");
    table.insert("raanm");
    table.insert("raansm");
    table.insert("dsfdsfdsdsf");
    table.insert("ranma");
    table.insert("raaedfewfnm");
    table.insert("wqeqed");
    table.insert("qweqwe");
    table.insert("raqanm");
    table.insert("dsfdwsfdsdsf");
    table.insert("raanwm");

    HashTable<std::string> table2(table);

    std::string remove_key = "raanm";
    std::cout << std::endl << " REMOVING value {" << remove_key << "}" << std::endl;
    table2.remove(remove_key);
    HashTable<std::string>::printDiff(table, table2, remove_key);
    table.remove(remove_key);
    remove_key = "arman";
    std::cout << std::endl << " REMOVING value {" << remove_key << "}" << std::endl;
    table2.remove(remove_key);
    HashTable<std::string>::printDiff(table, table2, remove_key);
    table.remove(remove_key);

}

void test_hash_table_SEARCH(){
    std::cout << __FUNCTION__ << std::endl;

    OpenAddressingHashTable<std::string> table(20, hashFunctionStr);
    table.setRehashLoadFactor(.69);
    table.insert("accompany");
    table.insert("accident");
    table.insert("access");
    table.insert("accept");
    table.insert("academic");
    table.insert("abuse");
    table.insert("absorb");
    table.insert("absolutely");
    table.insert("absolute");
    table.insert("absence");
    table.insert("abroad");
    table.insert("braoad");
    table.insert("baorad");

    std::string searc_key = "absolutely";
    std::cout << "Searching {" << searc_key << "} \n" ;

    int attempts = -1;
    int index = table.search(searc_key, &attempts);
    std::cout << " index = " << index << ",  attempts = " << attempts << " " << std::endl;

    table.print();
    std::cout << std::endl;
}

void test_hash_table_REHASH(){
    std::cout << __FUNCTION__ << std::endl;

    OpenAddressingHashTable<std::string> table(20, hashFunctionStr);
    table.setRehashLoadFactor(.69);
    table.insert("accompany");
    table.insert("accident");
    table.insert("access");
    table.insert("accept");
    table.insert("academic");
    table.insert("abuse");
    table.insert("absorb");
    table.insert("absolutely");
    table.insert("absolute");
    table.insert("absence");
    table.insert("abroad");
    table.insert("braoad");
    table.insert("baorad");

    OpenAddressingHashTable<std::string> tableOrigin(table);

    table.insert("above"); // calls Rehash
    table.insert("about");
    table.insert("abortion");
    table.insert("able");
    table.insert("ability");
    table.insert("abandon");


    OpenAddressingHashTable<std::string>::printDiff(tableOrigin, table, "");
    std::cout << std::endl;
}

void test_all(){
    test_hash_table_REMOVE_1();
    test_hash_table_SEARCH();
    test_hash_table_REHASH();
}

};


namespace TEST_OPEN_ADDRESSING_HASH_TABLE
{

void test_open_addressing_hash_table_REMOVE_1(){
    std::cout << __FUNCTION__ << std::endl;

    OpenAddressingHashTable<std::string> table(20, hashFunctionStr);
    table.setRehashLoadFactor(.99);
    table.insert("abc");
    table.insert("bca");
    table.insert("ddddd");
    table.insert("arman");
    table.insert("sadasdsad");
    table.insert("raanm");
    table.insert("raansm");
    table.insert("dsfdsfdsdsf");
    table.insert("ranma");
    table.insert("raaedfewfnm");
    table.insert("wqeqed");
    table.insert("qweqwe");
    table.insert("raqanm");
    table.insert("dsfdwsfdsdsf");
    table.insert("raanwm");


    OpenAddressingHashTable<std::string> table_copy(table);

    std::string remove_key = "raanm";
    std::cout << "Removing {" << remove_key << "} " << std::endl;
    std::cout << std::setw(25) << std::right << "Initial table"
              << std::setw(25) << std::right << "Modified table"  << std::endl << std::endl;
    table_copy.remove(remove_key);

    OpenAddressingHashTable<std::string>::printDiff(table,  table_copy, remove_key);
    std::cout << std::endl;
}

void test_open_addressing_hash_table_REMOVE_2(){
    std::cout << __FUNCTION__ << std::endl;

    OpenAddressingHashTable<std::string> table(20, hashFunctionStr);
    table.setRehashLoadFactor(.99);
    table.insert("accompany");
    table.insert("accident");
    table.insert("access");
    table.insert("accept");
    table.insert("academic");
    table.insert("abuse");
    table.insert("absorb");
    table.insert("absolutely");
    table.insert("absolute");
    table.insert("absence");
    table.insert("abroad");
    table.insert("braoad");
    table.insert("baorad");
    table.insert("above");
    table.insert("about");
    table.insert("abortion");
    table.insert("able");
    table.insert("ability");
    table.insert("abandon");


    OpenAddressingHashTable<std::string> table_copy(table);

    std::string remove_key = "absolute";
    std::cout << "Removing {" << remove_key << "} " << std::endl;
    std::cout << std::setw(25) << std::right << "Initial table"
              << std::setw(25) << std::right << "Modified table"  << std::endl << std::endl;
    table_copy.remove(remove_key);

    OpenAddressingHashTable<std::string>::printDiff(table,  table_copy, remove_key);
    std::cout << std::endl;
}

void test_open_addressing_hash_table_REHASH(){
    std::cout << __FUNCTION__ << std::endl;

    OpenAddressingHashTable<std::string> table(20, hashFunctionStr);
    table.setRehashLoadFactor(.69);
    table.insert("accompany");
    table.insert("accident");
    table.insert("access");
    table.insert("accept");
    table.insert("academic");
    table.insert("abuse");
    table.insert("absorb");
    table.insert("absolutely");
    table.insert("absolute");
    table.insert("absence");
    table.insert("abroad");
    table.insert("braoad");
    table.insert("baorad");

    OpenAddressingHashTable<std::string> tableOrigin(table);

    table.insert("above"); // calls Rehash
    table.insert("about");
    table.insert("abortion");
    table.insert("able");
    table.insert("ability");
    table.insert("abandon");


    OpenAddressingHashTable<std::string>::printDiff(tableOrigin, table, "");
    std::cout << std::endl;
}

void test_open_addressing_hash_table_SEARCH(){
    std::cout << __FUNCTION__ << std::endl;

    OpenAddressingHashTable<std::string> table(20, hashFunctionStr);
    table.setRehashLoadFactor(.69);
    table.insert("accompany");
    table.insert("accident");
    table.insert("access");
    table.insert("accept");
    table.insert("academic");
    table.insert("abuse");
    table.insert("absorb");
    table.insert("absolutely");
    table.insert("absolute");
    table.insert("absence");
    table.insert("abroad");
    table.insert("braoad");
    table.insert("baorad");

    std::string searc_key = "absolutely";
    std::cout << "Searching {" << searc_key << "} \n" ;

    int attempts = -1;
    int index = table.search(searc_key, &attempts);
    std::cout << " index = " << index << ",  attempts = " << attempts << " " << std::endl;

    table.print();
    std::cout << std::endl;
}


void test_all(){
    test_open_addressing_hash_table_REMOVE_1();
    test_open_addressing_hash_table_REMOVE_2();
    test_open_addressing_hash_table_REHASH();
    test_open_addressing_hash_table_SEARCH();
}

};
