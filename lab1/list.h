#pragma once

#include "link.h"



template <typename T>
class List : public Link<T> 
{
    
    public:
        List();
        T* first() const
        {
            return this->next(); 
        }

        T* last() const
        {
            return this->prev();     
        }

        T* pushFront(T* item)
        {
            this->insertAfter(item); 
            return item;
        }

        T* popFront()
        {
        
        }

        T* pushBack(T* item)
        {
            this->insertAfter(item);
            return item;
        }

        template<typename Arg>
            T* findFirst(const Arg& searchFor) { return findNext(searchFor); }

        friend std::ostream& operator<<(std::ostream& cout, List& list) 
        {
            return list.print(cout);
        }

        void check() const
        {
        
        }

    private:
        std::ostream& print(std::ostream& cout);
};

class Node : public Link<Node>
{
    public:
        Node(float val) : val(val) {}
        bool match(float rhs) { return val == rhs; }

    private:
        float val;
};
