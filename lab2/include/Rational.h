#include <iostream>
#include "GCD.h"
#include <string>
#include "mytrait.h"
#include <utility>

template<typename T>
class Rational {
    public:
        Rational(): p(0), q(1) {};
        Rational(T p): p(p), q(1) {}
        Rational(T p, T q): p(p), q(q == 0 ? 1 : q) { Reduce(this->p, this->q); }

        template<typename R>
            Rational(const Rational<R>& rtal)
            {
                p = rtal.p;
                q = rtal.q;
                Reduce(p, q);
            }

        T p, q;

        //Operators
        friend std::ostream& operator<< (std::ostream& cout, Rational<T>& R)
        {
            cout << R.p << '/' << R.q;
            return cout;
        }

        friend std::istream& operator>>(std::istream& is, Rational<T>& R)
        {
            std::string res;
            std::getline(is, res);
            std::string first = res.substr(0, res.find_first_of('/'));
            std::string second = res.substr(res.find_first_of('/')+1);
            int pInt = std::stoi(first);
            int qInt = std::stoi(second);
            R.p = pInt;
            R.q = qInt;
            return is;
        }

        template<typename R>
        Rational& operator=(const Rational<R> rhs)
        {
            p = rhs.p;
            q = rhs.q;
            Reduce(p, q);
            return *this;
        }

        Rational& operator=(T rhs)
        {
            p = rhs;
            q = 1;
            return *this;
        }
        template<typename R>
            friend bool operator==(const Rational<R>& lhs, const Rational<T>& rhs)
            {
                return (lhs.p == rhs.p && lhs.q == rhs.q);
            }

        friend bool operator==(const Rational<T> lhs, const T& t)
        {
            return (lhs.p == t && lhs.q == 1);
        }

        friend bool operator==(const T& t, const Rational<T> rhs)
        {
            return (t == rhs.p && 1 == rhs.q);
        }

        Rational& operator+=(const Rational& rhs)
        {
            long long tempP = p;
            long long tempQ = q;
            if(q != rhs.q)
            {
                tempQ *= rhs.q;
                tempP *= rhs.q;
                tempP += (rhs.p * q);
            }
            else
            {
                tempP += rhs.p;
            }
            Reduce(p, q);
            p = tempP;
            q = tempQ;

            return *this;
        }

        Rational& operator++()
        {
            p += q;
            Reduce(p,q);
            return *this;
        }

        Rational operator++(int)
        {
            Rational temp(*this);
            operator++();
            return temp;
        }

        Rational operator-()
        {
            p = -p;
            return *this;
        }

        template<typename R>
            Rational operator-(Rational<R>& rhs)
            {
                Rational<T> temp(p - rhs.p, q - rhs.q);
                if(temp.q == 0)
                {
                    temp.q = 1;
                }
                Reduce(temp.p, temp.q);
                return temp;
            }

    private:
        void swap(Rational to_swap)
        {
            std::swap(q, to_swap.q);
            std::swap(p, to_swap.p);
        }
};

template<typename L, typename R> 
Rational<typename RationalTrait<L,R>::fallback_type> operator+(const Rational<L>& lhs, const Rational<R>& rhs)
{
    Rational<typename RationalTrait<L,R>::fallback_type> temp(lhs.p, lhs.q);
    temp += rhs;
    Reduce(temp.p, temp.q);
    return temp;
}

template<typename L, typename R> 
Rational<typename RationalTrait<L,R>::fallback_type> operator+(const Rational<L> lhs, R rhs)
{
    Rational<typename RationalTrait<L,R>::fallback_type> temp(rhs, 1);
    temp += lhs;
    Reduce(temp.p, temp.q);
    return temp;
}

