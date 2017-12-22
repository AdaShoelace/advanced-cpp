#ifndef MY_STRING
#define MY_STRING

#include <iostream>

class String
{
private:
  int m_size;
  int m_capacity;
  char* m_string;
  void invariant() const;
public:
  String();
  String(const String& rhs);
  String(const char* cstr);

  int size() const;
  int capacity() const;
  void push_back(char c);
  char& at(int i);
  const char& at(int i) const;
  char* ConvertToChars() const;
  void reserve(int i);

  String& operator+=(const String& rhs);
  String operator+(const String& rhs);
  char& operator[](int i);
  const char& operator[](int i) const;
  String& operator=(const String& rhs);
  friend bool operator==(const String& lhs, const String& rhs);
  friend std::ostream& operator<<(std::ostream& out, const String& rhs);

  ~String();
};

#endif
