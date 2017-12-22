#include <iostream>
#include <stdexcept>
#include <cassert>
#include "String.h"

//Constructors
String::String()
{
	m_size = 0;
	m_capacity = 10;
	m_string = new char[m_capacity];
	invariant();
}
String::String(const String& rhs)
{
	m_size = rhs.size();
	m_capacity = rhs.capacity();
	m_string = new char[m_capacity];
	for (int i = 0; i < m_size; i++) m_string[i] = rhs[i];
	invariant();
}
String::String(const char* cstr)
{
	m_size = 0;
	m_capacity = 0;
	const char* c_ptr = cstr;
	while (*c_ptr != '\0')
	{
		m_size++;
		m_capacity++;
		c_ptr++;
	}
	m_string = new char[m_capacity];
	for (int i = 0; i < m_size; i++) m_string[i] = cstr[i];
	invariant();
}
//Functions
int String::size() const
{
	return m_size;
}
int String::capacity() const
{
	return m_capacity;
}
void String::push_back(char c)
{
	if (m_size >= m_capacity) reserve(m_size*2);
	m_string[m_size++] = c;
}
char& String::at(int i)
{
	if (i >= m_size) throw std::out_of_range("No char exists at chosen index");
	else return m_string[i];
}
const char& String::at(int i) const
{
	if (i >= m_size) throw std::out_of_range("No char exists at chosen index");
	else return m_string[i];
}
char* String::ConvertToChars() const
{
	char* temp = new char[m_size + 1];
	for (int i = 0; i < m_size; i++) temp[i] = m_string[i];
	temp[m_size] = '\0';
	return temp;
}
void String::reserve(int i)
{
	if (i > m_capacity)
	{
		char* temp = new char[i];
		for (int j = 0; j < m_size; j++) temp[j] = m_string[j];
		delete[] m_string;
		m_string = temp;
		m_capacity = i;
	}
	invariant();
}
//Operators
String& String::operator+=(const String& rhs)
{
	reserve(m_capacity + rhs.capacity());
	for (int i = 0; i < rhs.size(); i++) m_string[m_size++] = rhs.at(i);
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
char& String::operator[](int i)
{
	return m_string[i];
}
const char& String::operator[](int i) const
{
	return m_string[i];
}
String& String::operator=(const String& rhs)
{
	m_size = rhs.size();
	m_capacity = rhs.capacity();
	delete[] m_string;
	m_string = new char[m_capacity];
	for (int i = 0; i < m_size; i++) m_string[i] = rhs[i];
	invariant();
	return *this;
}
bool operator==(const String& lhs, const String& rhs)
{
	if (lhs.m_string == rhs.m_string) return true;
	else return false;
}
std::ostream& operator<<(std::ostream& out, const String& rhs)
{
	for (int i = 0; i < rhs.size(); ++i) out << rhs[i];
	return out;
}
void String::invariant() const
{
	assert(m_size >= 0);
	assert(m_capacity >= 0);
	assert(m_size <= m_capacity);
	assert(m_string != nullptr);
}
//Destructor
String::~String()
{
	invariant();
	delete[] m_string;
	m_string = nullptr;
}
