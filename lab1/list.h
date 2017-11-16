#pragma once

#include "link.h"



template <typename T>
class List : public Link<T> 
{
    
    public:
        List();
        T* First() const
        {
            return this->next(); 
        }

        T* Last() const
        {
            return this->prev();     
        }

        T* PushFront(T* item)
        {
            this->insertAfter(item); 
            return item;
        }

        T* PopFront()
        {
        
        }

        T* PushBack(T* item)
        {
            this->insertAfter(item);
            return item;
        }

        template<typename Arg>
            T* FindFirst(const Arg& searchFor) { return findNext(searchFor); }

        friend std::ostream& operator<<(std::ostream& cout, List& list) 
        {
            return list.print(cout);
        }

        void Check() const
        {
        
        }

    private:
        std::ostream& print(std::ostream& cout);
};

class Node : public Link<Node>
{
    public:
        Node(float val) : val(val) {}
        bool Match(float rhs) { return val == rhs; }

    private:
        float val;
};
