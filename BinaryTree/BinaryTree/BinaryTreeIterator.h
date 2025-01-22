#pragma once

#include <stack>
#include <vector>

template<typename T>
class BinaryTreePreOrderConstIterator{
public:

    inline BinaryTreePreOrderConstIterator(const T* ptr)
        : _Ptr{ const_cast<T*>(ptr) }
    {
        m_index = 0;
        auto node = ptr;
        m_preOrderTraversalArray.push_back(node);
        if (node) {
            if (node->rightNode) { m_stack.push(node->rightNode); }
            if (node->leftNode) { m_stack.push(node->leftNode); }
        }
    }

    inline BinaryTreePreOrderConstIterator& operator=(const BinaryTreePreOrderConstIterator&) noexcept = default;

    inline const T& operator*() const {
        return *_Ptr;
    }

    inline const T* operator->() const {
        return _Ptr;
    }

    inline BinaryTreePreOrderConstIterator& last() noexcept {

        while (!m_stack.empty())
        {
            auto node = m_stack.top();
            m_preOrderTraversalArray.push_back(node);
            m_stack.pop();
            if (node->rightNode) { m_stack.push(node->rightNode); }
            if (node->leftNode) { m_stack.push(node->leftNode); }
            m_index ++;
        }

        _Ptr = const_cast<T*> (m_preOrderTraversalArray[m_index]);

        return *this;
    }


    inline BinaryTreePreOrderConstIterator& operator++() noexcept {

        if (m_stack.empty() && (m_index >= m_preOrderTraversalArray.size())) 
        {
            _Ptr = nullptr;
            return *this;
        }

        m_index += 1;
        if (m_index >= m_preOrderTraversalArray.size()) {

            if (m_stack.empty()) {
                m_index = m_preOrderTraversalArray.size();
                _Ptr = nullptr;
                return *this;
            }
            auto node = m_stack.top();
            m_preOrderTraversalArray.push_back(node);
            m_stack.pop();
            if (node->rightNode) { m_stack.push(node->rightNode); }
            if (node->leftNode) { m_stack.push(node->leftNode); }
        }
        _Ptr = const_cast<T*> (m_preOrderTraversalArray[m_index]);
    
        return *this;
    }

    inline BinaryTreePreOrderConstIterator operator++(int) noexcept {
        BinaryTreePreOrderConstIterator _Tmp = *this;
        ++* this;
        if (_Ptr == nullptr) { 
            return nullIterator(); 
        }
        return _Tmp;
    }

    inline BinaryTreePreOrderConstIterator& operator--() noexcept
    {
        m_index -= 1;
        if (m_stack.empty() && (m_index >= m_preOrderTraversalArray.size()))
        {
            m_index = -1;
            _Ptr = nullptr;
            return *this;
        }

        if (m_index < 0) {
            m_index = -1;
            _Ptr = nullptr;
            return *this;
        }
        if(m_index < m_preOrderTraversalArray.size()){
            _Ptr = const_cast<T*> (m_preOrderTraversalArray[m_index]);
            
        }

        return *this;

    }

    inline BinaryTreePreOrderConstIterator operator--(int) noexcept {
        BinaryTreePreOrderConstIterator _Tmp = *this;
        --* this;
        if (_Ptr == nullptr) {
            return nullIterator();
        }

        return _Tmp;
    }

    
    inline bool operator==(const BinaryTreePreOrderConstIterator& _Right) const noexcept {
        return _Ptr == _Right._Ptr;
    }

    inline bool operator!=(const BinaryTreePreOrderConstIterator& _Right) const noexcept {
        return !(*this == _Right);
    }

    inline bool operator>=(const BinaryTreePreOrderConstIterator& _Right) const noexcept {
        return (this->m_index >= _Right.m_index);
    }

    static BinaryTreePreOrderConstIterator& nullIterator() {
        static BinaryTreePreOrderConstIterator<T> it(nullptr);
        return it;
    }

    
private:

    T* _Ptr = nullptr; // pointer to element in Tree
    int m_index = -1;
    std::stack<const T*>  m_stack;
    std::vector<const T*> m_preOrderTraversalArray;

};

