#pragma once

#include <iostream>

template<typename T>
class List;

template<typename T>
class Link 
{

    public:
        Link();
        virtual ~Link() = default;
        T* next()
        {
            T* ret = this->pNext; 
            return ret;
        }

        T* prev()
        {
            T* ret = this->pPrev;
            return ret;
        }

        const T* insertAfter(T* toInsert)
        {
            T* temp = this->pNext;
            this->pNext = toInsert;
            toInsert->pPrev = this;
            toInsert->pNext = temp;
            temp->pPrev = toInsert;
            return toInsert;
        }

        T* insertBefore(T* toInsert)
        {
            T* temp = this->pPrev;
            this->pPrev = toInsert;
            toInsert->pNext = this;
            toInsert->pPrev = temp;
            temp->pNext = toInsert;
            return toInsert;
        }

        T* deleteAfter()
        {
            T* temp = this->pNext; 
            T* newNext = temp->pNext;
            this->pNext = temp->pNext;
            newNext->pPrev = this;
            temp->pNext = nullptr;
            temp->pPrev = nullptr;
            return temp;
        }

        template<typename Arg>
            T* findNext(const Arg* searchFor)
            {
                 
            }

        virtual std::ostream& print(std::ostream& out) const { return out; }

    private:
        Link* pNext;
        Link* pPrev;
        friend class List<T>;
};
