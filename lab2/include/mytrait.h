
template<typename L, typename R>
struct RationalTrait
{
    typedef long long fallback_type;
};

//same, same
template<>
struct RationalTrait<int, int>
{
    typedef int fallback_type;
};

template<>
struct RationalTrait<short, short>
{
    typedef short fallback_type;
};

template<>
struct RationalTrait<long long, long long>
{
    typedef long long fallback_type;
};

//int, short
template<>
struct RationalTrait<int, short>
{
    typedef int fallback_type;
};

template<>
struct RationalTrait<short, int>
{
    typedef int fallback_type;
};

//int, long long
template<>
struct RationalTrait<int, long long>
{
    typedef long long fallback_type;
};

template<>
struct RationalTrait<long long, int>
{
    typedef long long fallback_type;
};

//long,short
template<>
struct RationalTrait<long long, short>
{
    typedef long long fallback_type;
};

template<>
struct RationalTrait<short, long long>
{
    typedef long long fallback_type;
};

