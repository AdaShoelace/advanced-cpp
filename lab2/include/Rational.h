#include <iostream>
#include "GCD.h"
template<typename T>
class Rational {
    public:
        Rational(): nom(0), denom(1) {};
        Rational(T nom):nom(nom), denom(1) {}
        Rational(T nom, T denom): nom(nom), denom(denom) {
            Reduce(nom, denom);
        }

        T nom, denom;
        friend std::ostream& operator<< (std::ostream& cout, Rational<T> R)
        {
            cout << R.nom << '/' << R.denom;
            return cout;
        }

        Rational operator+(const Rational rhs) const
        {

        }

    private:
        template<typename Q>
            int val_type(Q val)
            {
                return val_type<Q>();
            }

        template<typename Q>
            int val_type()
            {
                return 0;
            }

        template<>
            int val_type<short>()
            {
                return 1;
            }

        template <>
            int val_type<int>()
            {
                return 2;
            }

        template <>
            int val_type<long long>()
            {
                return 3;
            }
};
