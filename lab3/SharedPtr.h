#include "WeakPtr.h"
#include <utility>

#include <iostream>

template<typename T>
class SharedPtr {
    public:
        SharedPtr() : ptr(nullptr), users(new unsigned int{1}){}

        SharedPtr(std::nullptr_t nptr) : ptr(nptr), users(new unsigned int{1}){}

        SharedPtr(T* obj) : ptr(obj), users(new unsigned int{1}){}

        SharedPtr(const SharedPtr& obj)
        {
            users = obj.users;
            ptr = obj.ptr;
            (*users)++;
        }

        SharedPtr(SharedPtr&& obj)
        {
            ptr = obj.get();
            users = obj.users;
            obj = nullptr;
        }

        //SharedPtr(WeakPtr<T> obj);

        ~SharedPtr()
        {
            if(users == nullptr || *users == 1)
            {
                reset();
            }
            else
            {
                (*users)--;
            }
        }

        SharedPtr& operator=(SharedPtr& obj)
        {
            ptr = obj.get();
            users = obj.users;
            return *this;
        }

        SharedPtr& operator=(SharedPtr&& obj)
        {
            ptr = obj.get();
            users = obj.users;
            obj.reset();
            return *this;
        }

        bool operator==(std::nullptr_t nptr) const
        {
            return ptr == nptr;
        }

        bool operator==(const SharedPtr& compare_to) const
        {
            return ptr == compare_to.ptr;
        }

        operator bool() { return ptr != nullptr; }

        bool operator<(const SharedPtr& compare_to)
        {
            return ptr < compare_to.ptr;
        }

        bool operator<(std::nullptr_t nptr){ return this < nptr; }

        T& operator*() { return *ptr; }

        T* operator->() { return ptr; }

        T* get() { return ptr; }

        bool unique(){ return *users == 1; }

        void reset()
        {
            ptr = nullptr;
            users = nullptr;
        }

    private:
        T* ptr;
        unsigned int* users;
};
