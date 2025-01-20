#pragma once







template <class C>
class BinaryTreeIterator 
{
public:
    using _Mybase = _Vector_const_iterator<C>;

#ifdef __cpp_lib_concepts
    using iterator_concept = contiguous_iterator_tag;
#endif // __cpp_lib_concepts
    using iterator_category = random_access_iterator_tag;
    using value_type = typename _Myvec::value_type;
    using difference_type = typename _Myvec::difference_type;
    using pointer = typename _Myvec::pointer;
    using reference = value_type&;

    using _Mybase::_Mybase;

    // TRANSITION, DevCom-1331017
    _CONSTEXPR20_CONTAINER _Vector_iterator& operator=(const _Vector_iterator&) noexcept = default;

    _NODISCARD _CONSTEXPR20_CONTAINER reference operator*() const noexcept {
        return const_cast<reference>(_Mybase::operator*());
    }

    _NODISCARD _CONSTEXPR20_CONTAINER pointer operator->() const noexcept {
#if _ITERATOR_DEBUG_LEVEL != 0
        const auto _Mycont = static_cast<const _Myvec*>(this->_Getcont());
        _STL_VERIFY(this->_Ptr, "can't dereference value-initialized vector iterator");
        _STL_VERIFY(_Mycont->_Myfirst <= this->_Ptr && this->_Ptr < _Mycont->_Mylast,
            "can't dereference out of range vector iterator");
#endif // _ITERATOR_DEBUG_LEVEL != 0

        return this->_Ptr;
    }

    _CONSTEXPR20_CONTAINER _Vector_iterator& operator++() noexcept {
        _Mybase::operator++();
        return *this;
    }

    _CONSTEXPR20_CONTAINER _Vector_iterator operator++(int) noexcept {
        _Vector_iterator _Tmp = *this;
        _Mybase::operator++();
        return _Tmp;
    }

    _CONSTEXPR20_CONTAINER _Vector_iterator& operator--() noexcept {
        _Mybase::operator--();
        return *this;
    }

    _CONSTEXPR20_CONTAINER _Vector_iterator operator--(int) noexcept {
        _Vector_iterator _Tmp = *this;
        _Mybase::operator--();
        return _Tmp;
    }

    _CONSTEXPR20_CONTAINER _Vector_iterator& operator+=(const difference_type _Off) noexcept {
        _Mybase::operator+=(_Off);
        return *this;
    }

    _NODISCARD _CONSTEXPR20_CONTAINER _Vector_iterator operator+(const difference_type _Off) const noexcept {
        _Vector_iterator _Tmp = *this;
        _Tmp += _Off; // TRANSITION, LLVM-49342
        return _Tmp;
    }

    _CONSTEXPR20_CONTAINER _Vector_iterator& operator-=(const difference_type _Off) noexcept {
        _Mybase::operator-=(_Off);
        return *this;
    }

    using _Mybase::operator-;

    _NODISCARD _CONSTEXPR20_CONTAINER _Vector_iterator operator-(const difference_type _Off) const noexcept {
        _Vector_iterator _Tmp = *this;
        _Tmp -= _Off; // TRANSITION, LLVM-49342
        return _Tmp;
    }

    _NODISCARD _CONSTEXPR20_CONTAINER reference operator[](const difference_type _Off) const noexcept {
        return const_cast<reference>(_Mybase::operator[](_Off));
    }

    using _Prevent_inheriting_unwrap = _Vector_iterator;

    _NODISCARD _CONSTEXPR20_CONTAINER value_type* _Unwrapped() const noexcept {
        return _Unfancy(this->_Ptr);
    }
};
