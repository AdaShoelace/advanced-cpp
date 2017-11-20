#pragma once

#include "link.h"
#include <cassert>

template <typename T>
class List : public Link<T>
{

    public:
        List()
        {
            this->pNext = this;
            this->pPrev = this;
        }

        ~List()
        {
            auto temp = this->pNext;
            while(temp != this)
            {
                auto nl = temp->pNext;
                delete temp;
                temp = nl;
            }
        }

        const T* First() const
        {
            return this->Next();
        }

        const T* Last() const
        {
            return this->Prev();
        }

        T* First()
        {
            return this->Next();
        }

        T* Last()
        {
            return this->Prev();
        }

        T* PushFront(T* item)
        {
            this->InsertAfter(item);
            return item;
        }

        T* PushBack(T* item)
        {
            this->InsertBefore(item);
            return item;
        }

        T* PopFront()
        {
            if(this->pNext != this)
                return this->DeleteAfter();
            else
                return nullptr;
        }

        template<typename Arg>
            T* FindFirst(const Arg& searchFor) { return this->FindNext(searchFor); }

        friend std::ostream& operator<<(std::ostream& cout, List& list)
        {
            return list.print(cout);
        }

        void Check() const
        {
            const Link<T> *node = this, *nextNode = this->pNext;
            do {
                assert(node->pNext == nextNode && nextNode->pPrev == node);
                node = nextNode;
                nextNode = nextNode->pNext;
            } while (node != this);}

        bool Invariant()
        {
            assert(this->pNext->pPrev == this &&
                    this->pPrev->pNext == this);
            return true;
        }

    private:
        std::ostream& print(std::ostream& cout)
        {
            auto l = this->pNext;
            do {
                l->Print(cout);
                l = l->pNext;
            } while(l != this);
            return cout;
        }
};

class Node : public Link<Node>
{
    public:
        Node(float data) : data(data) {}
        bool Match(float rhs) { return data == rhs; }
        float data;
};
