#pragma once

#include <utility>

template<typename T>
class SharedPtr;

class RefCounter;

template<typename T>
class WeakPtr {

    private:
        friend SharedPtr<T>;
        T* ptr;
        RefCounter* refs;

        void weakRefDec()
        {
            if(this->refs)
                this->refs->decrement_weak_users();
        }

        void weakRefInc()
        {
            if(this->refs)
                this->refs->increment_weak_users();
        }

    public:
        WeakPtr() : ptr(nullptr), refs(nullptr) {}
        WeakPtr(SharedPtr<T>& obj) : ptr(obj.ptr), refs(obj.refs)
        {

            if(obj.ptr)
                weakRefInc();
        }

        WeakPtr(WeakPtr<T>& obj) : ptr(obj.ptr), refs(obj.refs)
        {

            if(obj.ptr)
                weakRefInc();
        }

        ~WeakPtr()
        {
            if(this->refs) 
            {
                if(this->refs->getWeakUsers() <= 1 && this->refs->getUsers() == 0) 
                {
                    delete refs; 
                }
                else 
                {
                    weakRefDec(); 
                }
            }
        }

        SharedPtr<T> lock()
        {
            return expired() ? SharedPtr<T>() : SharedPtr<T>(*this); 
        }

        bool expired()
        {
            return this->refs ? this->refs->getUsers() == 0 : true;
        }

        WeakPtr& operator=(SharedPtr<T>& obj)
        {
            this->ptr = obj.ptr;
            this->refs = obj.refs;
            weakRefInc();
            return *this;
        }

        WeakPtr& operator=(WeakPtr& obj)
        {
            if(obj.ptr != this->ptr)
            {
                weakRefDec();        
                ptr = obj.ptr;
                refs = obj.refs;
                weakRefInc();
            }
            return *this;
        }


};
