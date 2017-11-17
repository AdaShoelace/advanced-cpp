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
        T* Next()
        {
            T* ret = this->pNext;
            return ret;
        }

        T* Prev()
        {
            T* ret = this->pPrev;
            return ret;
        }

        const T* InsertAfter(T* toInsert)
        {
            T* temp = this->pNext;
            this->pNext = toInsert;
            toInsert->pPrev = this;
            toInsert->pNext = temp;
            temp->pPrev = toInsert;
            return toInsert;
        }

        T* InsertBefore(T* toInsert)
        {
            T* temp = this->pPrev;
            this->pPrev = toInsert;
            toInsert->pNext = this;
            toInsert->pPrev = temp;
            temp->pNext = toInsert;
            return toInsert;
        }

        T* DeleteAfter()
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
            T* FindNext(const Arg* searchFor)
            {
                T* ret = nullptr;
                for(Link* n = this->pNext; n != this; n = n->pNext)
                {
                    if(static_cast<T*>(this)->Match(searchFor))
                    {
                        ret = static_cast<T*>(this);
                    }
                }
                return ret;
            }

        virtual std::ostream& Print(std::ostream& out) const
        {
            Link* l = this;
            do {
                out << static_cast<T*>(this)->val << " ";
                l = l->pNext;
            } while(l != this);
            return out;
        }

    private:
        Link* pNext;
        Link* pPrev;
        friend class List<T>;
};
