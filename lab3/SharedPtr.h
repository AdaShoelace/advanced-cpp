#pragma once

#include "WeakPtr.h"
#include <utility>
#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>

class RefCounter{
    public:
        RefCounter(unsigned int users = 0,
                unsigned int weak_users = 0) :
            users(users),
            weak_users(weak_users) {
                std::cout << "Users" << users << " Weak-users" << weak_users << "\n";
            }

        ~RefCounter()
        {
        }

        unsigned int getUsers() {return users;}
        void setUsers(unsigned int value) {users = value;}

        unsigned int getWeakUsers() {return weak_users;}
        void setWeakUsers(unsigned int value) {weak_users = value;}

        void increment_users() {users++;}
        void decrement_users() {if (users > 0) users--;}

        void increment_weak_users() {weak_users++;}
        void decrement_weak_users() {if (weak_users > 0) weak_users--;}
    private:
        unsigned int users;
        unsigned int weak_users;
};

template<typename T>
class SharedPtr {
    public:

        /*
         * Constructors
         */
        SharedPtr() : ptr(nullptr), refs(nullptr){}
        SharedPtr(std::nullptr_t nptr) : ptr(nptr), refs(nullptr){}
        SharedPtr(T* obj) : ptr(obj), refs(new RefCounter(1)){}
        SharedPtr(WeakPtr<T> obj) : ptr(obj.ptr), refs(obj.refs)
        {
            if(obj.refs->getWeakUsers() != 0)
                refInc();
            else
                throw "std::bad_weak_ptr";
        } 
        SharedPtr(SharedPtr& obj) : ptr(obj.ptr), refs(obj.refs) {refInc();}
        SharedPtr(SharedPtr&& obj) : ptr(nullptr), refs(new RefCounter()) { this->swap(obj); }

        ~SharedPtr()
        {
            if(refs != nullptr)
            {
                if(refs->getUsers() <= 1)
                {
                    if(ptr != nullptr) delete ptr;
                    delete refs;
                }
                else
                {
                    refDec();
                    ptr = nullptr;
                    refs = nullptr;
                }
            }
        }

        /*
         * Operators
         */
        SharedPtr& operator=(SharedPtr& obj)
        {
            if(obj != *this)
            {
                ptr = obj.get();
                refDec();
                refs = obj.refs;
                refInc();
            }
            return *this;
        }

        SharedPtr& operator=(SharedPtr&& obj)
        {
            if(obj != *this)
            {
                swap(obj);
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

        bool operator<(const SharedPtr& compare_to)
        {
            return ptr < compare_to.ptr;
        }

        operator bool() { return ptr != nullptr; }
        bool operator<(std::nullptr_t nptr){ return this < nptr; }
        T& operator*() { return *ptr; }
        T* operator->() { return ptr; }

        T* get() { return ptr; }

        bool unique(){ return refs ? refs->getUsers() == 1 : true; }

        void reset()
        {
            if(!ptr)
                return;

            if(refs)
            {
                if(refs->getUsers() <= 1)
                {
                    delete ptr;
                    ptr = nullptr;
                    refs->setUsers(0);
                }
                else
                {
                    refDec();
                    ptr = nullptr;
                    refs = new RefCounter();
                }

            }
        }


    private:
        friend WeakPtr<T>;
        T* ptr;
        RefCounter* refs;

        void swap(SharedPtr& obj)
        {
            std::swap(ptr, obj.ptr);
            std::swap(refs, obj.refs);
        }

        void refDec()
        {
            if(refs) refs->decrement_users();
        }

        void refInc()
        {
            if(refs) refs->increment_users();
        }
};
