#include "include/String.h"
#include <cassert>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <utility>

// Constructors
String::String()
    : m_size(0)
    , m_capacity(10)
    , m_string(new char[m_capacity])
{
    m_string[m_size++] = '\0';
    invariant();
}

String::String(const String& rhs)
    : m_size(rhs.m_size)
    , m_capacity(rhs.capacity())
    , m_string(new char[m_capacity])
{
    for (size_t i = 0; i < m_size; i++)
        m_string[i] = rhs[i];
    invariant();
}

String::String(String&& rhs)
    : m_size(0)
    , m_capacity(0)
    , m_string(nullptr)
{
    this->swap(rhs);
}

String::String(const char* cstr)
    : m_size(0)
    , m_capacity(0)
{
    const char* c_ptr = cstr;
    while (*c_ptr != '\0') {
        m_size++;
        m_capacity++;
        c_ptr++;
    }
    m_size++;
    m_string = new char[++m_capacity];
    for (size_t i = 0; i < m_size; i++)
        m_string[i] = cstr[i];
    invariant();
}

// Functions
int String::size() const { return m_size - 1; }

int String::capacity() const { return m_capacity; }

void String::push_back(char c)
{
    if (m_size >= m_capacity)
        reserve(m_size * 2);
    m_string[m_size++] = c;
    std::swap(m_string[m_size - 2], m_string[m_size - 1]);
}

char& String::at(size_t i)
{
    if (i >= size())
        throw std::out_of_range("No char exists at chosen index");
    else
        return m_string[i];
}

const char& String::at(size_t i) const
{
    if (i >= size())
        throw std::out_of_range("No char exists at chosen index");
    else
        return m_string[i];
}

void String::reserve(size_t i)
{
    if (i > m_capacity) {
        char* temp = new char[i];
        for (size_t j = 0; j < m_size; j++)
            temp[j] = m_string[j];
        delete[] m_string;
        m_string = temp;
        m_capacity = i;
    }
    invariant();
}

const char* String::data() const { return m_string; }

void String::shrink_to_fit()
{
    char* dest = new char[m_size];
    std::memcpy(dest, m_string, m_size);
    m_capacity = m_size;
    delete[] m_string;
    m_string = dest;
}

void String::resize(size_t n)
{
    char* dest = new char[n];
    std::memcpy(dest, m_string, n);
    delete[] m_string;
    m_capacity = n;
    if (n > m_size) {
        for (size_t i = m_size; i < m_capacity; i++) {
            dest[i] = char();
        }
    }
    dest[m_capacity - 1] = '\0';
    m_size = n;
    m_string = dest;
}

// Operators
String& String::operator+=(const String& rhs)
{
    reserve(m_capacity + rhs.m_size);
    size_t temp_size = rhs.m_size;
    m_size--;
    for (size_t i = 0; i < temp_size; i++)
        m_string[m_size++] = rhs[i];
    m_string[m_size - 1] = '\0';
    invariant();
    return *this;
}

String String::operator+(const String& rhs)
{
    String temp;
    temp += *this;
    temp += rhs;
    return temp;
}

char& String::operator[](int i) { return m_string[i]; }

const char& String::operator[](int i) const { return m_string[i]; }

String& String::operator=(const String& rhs)
{
    if (rhs == *this)
        return *this;
    m_size = rhs.m_size;
    m_capacity = rhs.capacity();
    delete[] m_string;
    m_string = new char[m_capacity];
    for (size_t i = 0; i < m_size; i++)
        m_string[i] = rhs[i];
    invariant();
    return *this;
}

String& String::operator=(String&& rhs)
{
    this->swap(rhs);
    return *this;
}

bool operator==(const String& lhs, const String& rhs)
{
    if (lhs.size() != rhs.size())
        return false;
    for (int i = 0; i < lhs.size(); i++) {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& out, const String& rhs)
{
    for (int i = 0; i < rhs.size(); ++i)
        out << rhs[i];
    return out;
}

bool operator!=(const String& lhs, const String& rhs) { return !(lhs == rhs); }

String::operator bool() { return m_size > 1; }

// Operators
void String::invariant() const
{
    assert(m_size >= 0);
    assert(m_capacity >= 0);
    assert(m_size <= m_capacity);
}

void String::swap(String& rhs)
{
    std::swap(this->m_size, rhs.m_size);
    std::swap(this->m_capacity, rhs.m_capacity);
    std::swap(this->m_string, rhs.m_string);
}

// Destructor
String::~String()
{
    invariant();
    if (m_string != nullptr) {
        delete[] m_string;
    }
    m_string = nullptr;
}

// for iterators
String::iterator String::begin()
{
    return iterator(&m_string[0]);
}

String::iterator String::end()
{
    return iterator(&m_string[size()]);
}

String::reverse_iterator String::rbegin()
{
    return reverse_iterator(&m_string[size()-1]);
}

String::reverse_iterator String::rend()
{
    return reverse_iterator(&m_string[-1]);
}

String::const_iterator String::cbegin()
{
    return const_iterator(&m_string[0]);
}

String::const_iterator String::cend()
{
    return const_iterator(&m_string[size()]);
}

String::const_reverse_iterator String::crbegin()
{
    return const_reverse_iterator(&m_string[size()-1]);
}

String::const_reverse_iterator String::crend()
{
    return const_reverse_iterator(&m_string[-1]);
}
