#include "WeakPtr.h"
#include <utility>
#include <algorithm>
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



        SharedPtr(SharedPtr&& obj) : ptr(nullptr), users(new unsigned int{1})
        {
            this->swap(obj);
        }

        void swap(SharedPtr& obj)
        {
            std::swap(ptr, obj.ptr);
            std::swap(users, obj.users);
        }

        //SharedPtr(WeakPtr<T> obj);

        ~SharedPtr()
        {
            if(*users == 1)
            {
                if(ptr) delete ptr;
                delete users;
            }
            else
            {
                (*users)--;
                ptr = nullptr;
            }
        }

        SharedPtr& operator=(SharedPtr& obj)
        {
            if(&obj != this)
            {
                ptr = obj.get();
                users = obj.users;
            }
            return *this;
        }

        SharedPtr& operator=(SharedPtr&& obj)
        {
            if(obj != this)
            {
                ptr = obj.get();
                users = obj.users;
                obj.reset();
            }
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
            if(!ptr)
                return;

            if(*users == 1)
            {
                delete ptr;
                ptr = nullptr;
            }
        }

    private:
        T* ptr;
        unsigned int* users;
};
