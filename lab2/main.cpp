#include <limits>
#include <iostream>
#include <cassert>
#include "include/Rational.h"
#include "include/VG.h"

bool TestAccuracy() {
    Rational<int> left(std::numeric_limits<int>::max(), 2), right(left), result;
    result = left + right;
    assert(result == Rational<int>(std::numeric_limits<int>::max(), 1));
    return true;
}
template<class Result, class L, class R>
bool CheckPlus(Result, L l, R r) {
    auto res = l + r; //Varför används inte variablen!?
    assert((std::is_same<Result, decltype(l + r)>::value));
    return std::is_same<Result, decltype(l + r)>::value;
};
bool TestCompatibility() {
    bool res = true;
    res &= CheckPlus(Rational<short>(), Rational<short>(), Rational<short>());
    res &= CheckPlus(Rational<int>(), Rational<short>(), Rational<int>());
    res &= CheckPlus(Rational<long long>(), Rational<long long>(), Rational<short>());
    res &= CheckPlus(Rational<long long>(), Rational<short>(), Rational<long long>());
    // res &= CheckPlus(Rational<short>(), Rational<short>(), Rational<long>());  //Rational<long> is more correct (Varför ska det bli en short!? Varför används long!?)
    return res;
}
void TestForValGodkant() {
    assert(TestAccuracy());
    assert(TestCompatibility());

    Rshort rs(3,2); Rint ri(2,1); RLL rl;
    assert(!(1 == rs));
    assert(2 == ri);
}
void TestForGodkant() {
    Rational<short> rs0, rs1(1), rs2(2, 1), rs3(3);
    Rational<int> ri0;
    Rational<long long> rll0, rll1(1), rll2(2, 1), rll3(3);
    RLL   rllx(1);
    RLL   rlly(rs0);

    assert(rs1 == rs1);
    assert(rs2 == 2);
    assert(rs1 == rll1);
    assert(rs1 == Rational<short>(rs1.p, rs1.q));
    assert(rs1 == Rational<short>(-rs1.p, -rs1.q));

    rs3 = Rint(13, 3);
    assert(rs3 == Rshort(13, 3));
    rs3 = rll3 = -17;
    assert(rs3 == Rshort(-17));

    assert((rs3 += 4) == Rshort(-13));

    rs3 = Rshort(13, 3);
    assert(rs3 + rll2 == Rshort(19, 3));
    assert(rs3 + 2 == Rshort(19, 3));

    assert((rs0 = -rs1) == Rshort(-1));

    rll3 = RLL(1, 6);
    assert(++rll3 == RLL(7, 6));
    assert(rll3++ == RLL(7, 6));
    assert(rll3 == RLL(13, 6));

    // explicit konvertering till Tal. (Kr�ver VS2012 och kompilator CTnom november 12.
    // int i = static_cast<int>(rll3);
    // assert(i == 2);

    // Overloading av << och >> (ut och in matning)
    std::cout << "Utmatning>" << rs3 << "< skriv in texten mellan > och < + retur\n";
    std::cin >> rs2;
    assert(rs3 == rs2);
}

int main()
{
  TestForGodkant();
  TestForValGodkant();
  return 0;
}
