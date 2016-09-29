#include "cpp_exp_base.h"
#include <vector>

typedef std::vector<int> myvec_int;                                     // C++03 alias syntax
using myvec_double = std::vector<double>;                       // C++11 syntax
template<typename T> using myvec = std::vector<T>;      // C++11 syntax

//  is_same_v<T1,T2>    ====>   std::is_same<T1,T2>::value

void test_template_alias()
{
    static_assert(std::is_same<myvec_int, std::vector<int>>::value, "sample msg");
    static_assert(std::is_same<myvec_double, std::vector<double>>::value, "sample msg");
    static_assert(std::is_same<myvec<float>, std::vector<float>>::value, "sample msg");
}

