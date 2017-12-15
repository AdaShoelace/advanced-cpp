#include <iostream>
#include "GCD.h"
#include "mytrait.h"

template<typename T>
class Rational {
    public:
        Rational(): p(0), q(1) {};
        Rational(T p): p(p), q(1) {}
        Rational(T p, T q): p(p), q(q) { Reduce(p, q); }
        Rational(Rational<T>& rtal)
        {
            p = rtal.p;
            q = rtal.q;
        }

        T p, q;

        friend std::ostream& operator<< (std::ostream& cout, Rational<T> R)
        {
            cout << R.nom << '/' << R.denom;
            return cout;
        }
        
        void operator+=(const Rational& rhs)
        {
            long long temp = q;
            p = (p * rhs.q) + (rhs.p * temp);
            q = (q * rhs.q);
            Reduce(p, q);
        }

        //Operators
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


    private:
};

template<typename L, typename R>
Rational<typename RationalTrait<L,R>::fallback_type> operator+(const Rational<L> lhs, const Rational<R> rhs)
{
    Rational<typename RationalTrait<L,R>::fallback_type> temp(lhs.p, lhs.q);
}
