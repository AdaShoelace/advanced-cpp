#pragma once

#include <iostream>

template<typename T>
class List;

template<typename T>
class Link
{

    public:
        Link() = default;

        virtual ~Link() = default;
        const T* Next() const
        {
            return static_cast<T*>(this->pNext);
        }

        const T* Prev() const
        {
            return static_cast<T*>(this->pPrev);
        }
        T* Next()
        {
            return static_cast<T*>(this->pNext);
        }

        T* Prev()
        {
            return static_cast<T*>(this->pPrev);
        }

        T* InsertAfter(T* toInsert)
        {
            toInsert->pPrev = this;
            toInsert->pNext = this->pNext;
            this->pNext->pPrev = toInsert;
            this->pNext = toInsert;
            return toInsert;
        }

        T* InsertBefore(T* toInsert)
        {
            toInsert->pNext = this;
            this->pPrev->pNext = toInsert;
            toInsert->pPrev = this->pPrev;
            this->pPrev = toInsert;
            return toInsert;
        }

        T* DeleteAfter()
        {
            auto temp = static_cast<T*>(this->pNext);
            auto newNext = temp->pNext;
            this->pNext = temp->pNext;
            newNext->pPrev = this;
            temp->pNext = nullptr;
            temp->pPrev = nullptr;
            return temp;
        }

        template<typename Arg>
            T* FindNext(const Arg& searchFor)
            {
                T* ret = Next();
                while(ret != this)
                {
                    if(ret->Match(searchFor))
                    {
                        return ret;
                    }
                    ret = ret->Next();
                }
                return nullptr;
            }

        virtual std::ostream& Print(std::ostream& out) const
        {
            if(this->pNext != this)
                out << static_cast<const T*>(this)->data << " ";
            else
                out << "";
            return out;
        }

    private:
        Link* pNext;
        Link* pPrev;
        friend class List<T>;
};
