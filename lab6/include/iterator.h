#pragma once

#include <algorithm>
#include <iterator>

template <typename T> class forward_iterator : public std::iterator<std::random_access_iterator_tag, T> {
private:
    T* ptr;

public:
    forward_iterator(T* ptr = nullptr)
        : ptr(ptr)
    {
    }
    forward_iterator(const forward_iterator<T>& to_copy)
        : ptr(to_copy.ptr)
    {
    }

    forward_iterator& operator=(const forward_iterator<T>& to_assign) = default;

    T& operator*() { return *ptr; }

    forward_iterator<T>& operator++()
    {
        ptr++;
        return *this;
    }

    forward_iterator<T> operator++(int)
    {
        forward_iterator<T> temp(*this);
        ptr++;
        return temp;
    }

    forward_iterator<T>& operator--()
    {
        ptr--;
        return *this;
    }

    forward_iterator<T> operator--(int)
    {
        forward_iterator<T> temp(*this);
        ptr--;
        return temp;
    }

    forward_iterator<T>& operator+=(std::ptrdiff_t inp)
    {
        this->ptr += inp;
        return *this;
    }

    forward_iterator<T> operator+(std::ptrdiff_t inp) const
    {
        forward_iterator<T> temp(*this);
        return (temp.ptr += inp);
    }

    std::ptrdiff_t operator+(const forward_iterator<T>& it) { return (ptr + it.ptr); }

    forward_iterator<T>& operator-=(const std::ptrdiff_t& inp)
    {
        ptr -= inp;
        return *this;
    }

    forward_iterator<T> operator-(const std::ptrdiff_t& inp) const
    {
        forward_iterator<T> temp(*this);
        return (temp.ptr -= inp);
    }

    std::ptrdiff_t operator-(forward_iterator<T> it) const { return (ptr - it.ptr); }

    bool operator<(const forward_iterator<T>& it) { return (ptr < it.ptr); }

    T operator[](int index) { return *(ptr + index); }

    bool operator==(const forward_iterator<T>& it) { return (ptr == it.ptr); }

    bool operator!=(const forward_iterator<T>& it) { return (ptr != it.ptr); }
};

template <typename T> class backward_iterator : public std::iterator<std::random_access_iterator_tag, T> {
private:
    T* ptr;

public:
    backward_iterator(T* ptr = nullptr)
        : ptr(ptr)
    {
    }
    backward_iterator(const backward_iterator<T>& to_copy)
        : ptr(to_copy.ptr)
    {
    }

    backward_iterator& operator=(const backward_iterator<T>& to_assign) = default;

    T& operator*() { return *ptr; }

    backward_iterator<T>& operator++()
    {
        ptr--;
        return *this;
    }

    backward_iterator<T> operator++(int)
    {
        backward_iterator<T> temp(*this);
        ptr--;
        return temp;
    }

    backward_iterator<T>& operator--()
    {
        ptr++;
        return *this;
    }

    backward_iterator<T> operator--(int)
    {
        backward_iterator<T> temp(*this);
        ptr--;
        return temp;
    }

    backward_iterator<T>& operator+=(std::ptrdiff_t inp)
    {
        this->ptr -= inp;
        return *this;
    }

    backward_iterator<T> operator+(std::ptrdiff_t inp)
    {
        backward_iterator<T> temp(*this);
        return (temp += inp);
    }

    std::ptrdiff_t operator+(const backward_iterator<T>& it) { return (ptr + it.ptr); }

    backward_iterator<T>& operator-=(std::ptrdiff_t inp)
    {
        ptr += inp;
        return *this;
    }

    backward_iterator<T> operator-(std::ptrdiff_t inp) const
    {
        backward_iterator<T> temp(*this);
        return (temp -= inp);
    }

    std::ptrdiff_t operator-(backward_iterator<T> it) const { return (ptr - it.ptr); }

    bool operator<(const backward_iterator<T>& it) { return (ptr < it.ptr); }

    T operator[](int index) { return *(ptr - index); }

    bool operator==(const backward_iterator<T>& it) { return (ptr == it.ptr); }

    bool operator!=(const backward_iterator<T>& it) { return (ptr != it.ptr); }
};
