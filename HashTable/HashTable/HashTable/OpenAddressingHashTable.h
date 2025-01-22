#pragma once

#include <iostream>
#include <iomanip>
#include <optional>
#include <vector>
#include <string>


template <typename T>
class OpenAddressingHashTable
{
public:

    OpenAddressingHashTable(int size, uint64_t(*f)(const T&))
    {
        m_table.resize(size);
        m_f = f;
    }

    size_t size() const { return m_table.size();}

    std::optional<T> at(size_t index) const
    {
        if (index >= m_table.size())
        {
            return std::nullopt;
        }

        if(m_table[index].second ){

            return m_table[index].first;
        }
        return std::nullopt;
    }

    uint64_t hashIndexOfValue(const T& t) const{
        auto _hash = m_f(t);
        int index = _hash % m_table.size();
        return index;
    }

    float loadFactor(){
        return (float) m_loadCount / (float) m_table.size();
    }

    void insert(const T& t)
    {
        auto hash = m_f(t);
        size_t index = hash % m_table.size();

        size_t root_index = index;
        while(m_table[index].second){
            // occupied, find closest cell
            index ++;
            if(index == m_table.size()){
                index = 0;
            }
            else if(index == root_index){
                // loop
                std::cout << " error Loop one cycle and not found " << hash << std::endl;
                return;
            }
        }
        m_table[index].first = t;
        m_table[index].second = true;
        m_loadCount ++;

        // check for rehash
        if(loadFactor() >= m_rehashLoadFactor){
            std::cout << "Rehash after inserting {" << t << "}\n\n";

            normalRehash();

        }

    }

    void normalRehash(){

        std::vector<std::pair<T, bool> > newTable;
        newTable.resize(m_table.size() * m_scaleFactor);
        for (int i = 0; i < m_table.size(); ++i) {
            if(!m_table[i].second){continue;}
            auto hash = m_f(m_table[i].first);
            int index = hash % newTable.size();

            while(newTable[index].second){
                // occupied, find closest cell
                index ++;
            }
            newTable[index].first = m_table[i].first;
            newTable[index].second = true;

        }

        m_table.clear();
        m_table = newTable;
    }

    int search(const T& t, int* p_attempts)
    {
        auto hash = m_f(t);
        int index = hash % m_table.size();
        int attempts = 1;
        while(m_table[index].second){
            // occupied, find closest cell
            if(m_table[index].first == t){
                if(p_attempts){ *p_attempts = attempts;}
                return index;
            }
            index ++;
            attempts++;
        }

        return -1;
    }

    void remove(const T& t)
    {
        auto hash = m_f(t);
        int root_index = hash % m_table.size();
        // find and remove
        if(! m_table[root_index].second){
            std::cout << "Does not contain!! " << std::endl;
            return;
        }

        // find index

        int i = root_index;
        int found_i = -1;

        while(m_table[i].second){
            if(m_table[i].first == t){
                // found, "remove"
                found_i = i;
                m_table[i].second = false;
                m_loadCount--;
                break;
            }

            i++;
            if(i == m_table.size()){
                i = 0;
            }
            else if(i == root_index){
                // loop
                std::cout << " error Loop one cycle and not found " << hash << std::endl;
                return;
            }
        }

        if(found_i == -1){
            std::cout << " error " << hash << std::endl;
            return;
        }

        i = found_i + 1;
        if(i == m_table.size()){
            i = 0;
        }
        else if(i == root_index){
            // loop
            std::cout << " error Loop one cycle and not found " << hash << std::endl;
            return;
        }

        while(m_table[i].second){
            m_table[i].second = false;
            m_loadCount--;
            insert(m_table[i].first);
            i++;
            if(i == m_table.size()){
                i = 0;
            }
            else if(i == root_index){
                // loop
                std::cout << " error Loop one cycle and not found " << hash << std::endl;
                return;
            }
        }


    }

    void print(){
        for (int i = 0; i < m_table.size(); ++i) {
            if(!m_table[i].second){
                std::cout << "[" << i << "]" << std::endl;
            }
            else{
                auto hash = m_f(m_table[i].first);
                int index = hash % m_table.size();

                std::cout  << "[" << i << "]  " << m_table[i].first << "[" << index << "]";
                std::cout << std::endl;

            }
        }

        std::cout << " loadFactor " << loadFactor() << std::endl;
    }

    void setRehashLoadFactor(float newRehashLoadFactor){
        if(newRehashLoadFactor > 0.25 && newRehashLoadFactor < 1 ){
            m_rehashLoadFactor = newRehashLoadFactor;
        }
    }

    static void printDiff(const OpenAddressingHashTable<T>& t1, const OpenAddressingHashTable<T>& t2, const std::string& highlightText){

        int s1 = t1.size();
        int s2 = t2.size();

        bool do_highlight = false;

        int s = std::min(s1, s2);
        for (size_t i = 0; i < s; ++i) {
            do_highlight = (!(highlightText.empty())
                && t1.at(i).has_value()
                && (highlightText == t1.at(i)));

            std::string str;
            if(do_highlight){ str += "*-> ";}
            if(t1.at(i).has_value()){
                str += t1.at(i).value();
                str += "(" +  std::to_string( t1.hashIndexOfValue(t1.at(i).value())) + ")";
            }

            std::string str2;
            if(t2.at(i).has_value()){
                str2 += t2.at(i).value();
                str2 += "(" +  std::to_string( t2.hashIndexOfValue(t2.at(i).value())) + ")";
            }

            std::cout << std::right << std::setw(20)
                << str << std::right << " [" << std::setw(2) << i << "]" ;

            std::cout << std::right << std::setw(20)
                      << str2 << std::right << " [" << std::setw(2) << i << "]" ;

            std::cout << std::endl;

        }

        for (size_t i = s; i < s2; ++i) {
            do_highlight = (!(highlightText.empty())
                            && t1.at(i).has_value()
                            && (highlightText == t1.at(i)));


            std::string str2;
            if(t2.at(i).has_value()){
                str2 += t2.at(i).value();
                str2 += "(" +  std::to_string( t2.hashIndexOfValue(t2.at(i).value())) + ")";
            }

            std::cout << std::right << std::setw(25) << "";

            std::cout << std::right << std::setw(20)
                      << str2 << std::right << " [" << std::setw(2) << i << "]" ;

            std::cout << std::endl;

        }

    }

private:
    float m_scaleFactor = 1.5;
    float m_rehashLoadFactor = .7;
    std::vector<std::pair<T, bool> > m_table;
    size_t m_loadCount = 0;
    uint64_t(*m_f)(const T&);
};



