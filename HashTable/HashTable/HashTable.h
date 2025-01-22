#pragma once

#include <iomanip>
#include <iostream>
#include <optional>
#include <vector>
#include <string>


template <typename T>
class Node{

public:
    explicit Node(const T& t){
        _t = t;
    }

    Node() = delete;

    void insert(const T& t){
        Node* node = this;
        while (node->next != nullptr) {
            node = node->next;
        }
        node->next = new Node(t);
    }

    void print(){
        if(!this){
            std::cout << " nullptr ";
        }
        else{
            Node* n = this;
            while(n){
                std::cout << "[" << n->_t << "] ";
                n = n->next;
            }

        }
    }

    void printAndTag(const T& tag) const{
        if(!this){
            std::cout << " nullptr ";
        }
        else{
            const Node* n = this;
            while(n){
                if(n->_t == tag){
                    std::cout << " -> {" << n->_t << "}";
                }
                else{
                    std::cout << " -> " << n->_t;
                }
                n = n->next;
            }
        }
    }

    T _t;
    Node* next = nullptr;
};

template <typename T>
class HashTable
{
public:

    HashTable(int size, uint64_t(*f)(const T&))
    {
        m_table.resize(size, nullptr);
        m_f = f;
    }

    HashTable(const HashTable& other)
        : m_scaleFactor{other.m_scaleFactor},
        m_rehashLoadFactor{other.m_rehashLoadFactor},
        m_f{other.m_f},
        m_loadCount{other.m_loadCount}
    {
        m_table.resize(other.size());
        for (int i = 0; i < other.size(); ++i) {
            if(other.at(i).has_value()){
                auto node = other.at(i).value();
                insert(node->_t);
                m_loadCount++;
                while(node->next){
                    node = node->next;
                    m_loadCount++;
                    insert(node->_t);
                }
            }

        }
        //        std::vector<Node<T>*> m_table;

    }

    size_t size() const { return m_table.size();}

    std::optional<const Node<T>*> at(size_t index) const
    {
        if (index >= m_table.size() || !m_table[index])
        {
            return std::nullopt;
        }

        return m_table[index];
    }

    uint64_t hashIndexOfValue(const T& t) const{
        auto _hash = m_f(t);
        int index = _hash % m_table.size();
        return index;
    }


    void insert(const T& t)
    {
        auto hash = m_f(t);
        int index = hash % m_table.size();

        if(m_table[index]){
            m_table[index]->insert(t);
            m_loadCount++;
        }
        else{
            m_table[index] = new Node<T>(t);
            m_loadCount++;
        }
    }


    void remove(const T& t)
    {
        auto hash = m_f(t);
        int root_index = hash % m_table.size();
        // find and remove
        if(! m_table[root_index]){
            std::cout << "Does not contain!! " << std::endl;
            return;
        }


        Node<T>* ptr = m_table[root_index];
        Node<T>* ptr_parent = nullptr;

        while (ptr) {
            if ((ptr)->_t == t) {
                // found, "remove"
                m_loadCount--;
                if (!ptr_parent) {
                    m_table[root_index] = (ptr)->next;
                    (ptr)->next = nullptr;
                    delete ptr;
                }
                else {
                    // has parent
                    (ptr_parent)->next = (ptr)->next;
                    (ptr)->next = nullptr;
                    delete ptr;
                }
                break;
            }
            ptr_parent = ptr;
            ptr = (ptr)->next;

        }

        //Node<T>** ptr = &m_table[root_index];
        //Node<T>** ptr_parent = nullptr;

        //while(*ptr){
        //    if((*ptr)->_t == t){
        //        // found, "remove"
        //        m_loadCount--;
        //        if(!ptr_parent){
        //            auto tmp = *ptr;
        //            *ptr = (*ptr)->next;
        //            tmp->next = nullptr;
        //            delete tmp;
        //        }
        //        else{
        //            // has parent
        //            (*ptr_parent)->next = (*ptr)->next;
        //            (*ptr)->next = nullptr;
        //            delete *ptr;
        //        }
        //        break;
        //    }
        //    ptr_parent = ptr;
        //    *ptr = (*ptr)->next;

        //}
    
    }

    void print(){
        for (int i = 0; i < m_table.size(); ++i) {
            if(!m_table[i]){
                std::cout << "[" << i << "]" << std::endl;
            }
            else{
                std::cout << "[" << i << "]  " ;
                m_table[i]->print();
                std::cout << std::endl;

            }
        }
    }

    void printAndTag(const T& tag) const{
        for (int i = 0; i < m_table.size(); ++i) {
            if(!m_table[i]){
                std::cout << "[" << i << "]" << std::endl;
            }
            else{
                std::cout << "[" << i << "]  " ;
                m_table[i]->printAndTag(tag);
                std::cout << std::endl;
            }
        }
    }

    static void printDiff(const HashTable<T>& t1, const HashTable<T>& t2, const std::string& tag){
        size_t s1 = t1.size();
        size_t s2 = t2.size();
        size_t s = std::min(s1, s2);

        const size_t offset = 80;

        for (size_t i = 0; i < s; ++i) {
            std::string line = "";
            line  += "["  + std::to_string(i) + "]";

            if(t1.at(i).has_value()){
                const Node<T>* n = t1.at(i).value();
                while(n){
                    if(n->_t == tag){
                        line  += " -> {" + n->_t + "}";
                    }
                    else{
                        line  += " -> " + n->_t;
                    }
                    n = n->next;
                }
            }

            int w = 10;
            std::cout<< line;
            if(line.size() < offset){
                w =  offset - line.size();
            }

            std::cout<< std::setw(w) << std::setfill( i%2==0 ? '.' : ' ') << "[" + std::to_string( i) + "] " ;

            line = "";

            if(t2.at(i).has_value()){
                const Node<T>* n = t2.at(i).value();
                while(n){
                    if(n->_t == tag){
                        line  += " -> {" + n->_t + "}";
                    }
                    else{
                        line  += " -> " + n->_t;
                    }
                    n = n->next;
                }
            }
            w = 10;
            std::cout<< line;
            if(line.size() < offset){
                w =  offset - line.size();
            }

            std::cout<< std::setw(w) << std::setfill( i%2==0 ? '.' : ' ') << " ";
            std::cout << std::endl;
        }
    }

private:
    float m_scaleFactor = 1.5;
    float m_rehashLoadFactor = .7;
    std::vector<Node<T>*> m_table;
    size_t m_loadCount = 0;
    uint64_t(*m_f)(const T&);

};

