#include "cpp_exp_base.h"
#include <iostream>
#include <array>
#include <stdlib.h>

namespace { //anonymous namespace.

    template<typename T>
    T abs(T x)
    {
        return (x >= 0) ? x : -x;
    }

    void simple_template_func()
    {
        double(*foo)(double) = abs<double>;
        std::cout << "abs<int>(-42) = " << abs<int>(-42) << "\n";
        std::cout << "foo(-3.5) = " << foo(-3.5) << "\n";
    }

    template<typename T, typename U>
    void foo(std::array<T, sizeof(U)> x,
        std::array<U, sizeof(T)> y,
        int z)
    {
        std::cout << " foo." << "\n";
    }

    void template_func_deduction()
    {
        // warning C4244: 'argument': conversion from 'double' to 'int', possible loss of data
        foo(std::array<int, 8>{}, std::array<double, 4>{}, 1);

        //
        // below line trigger a build error:
        // error C2664: 'void foo<int,double>(std::array<int,8>,std::array<double,4>,int)': cannot convert argument 1 from 'std::array<int,9>' to 'std::array<int,8>'
        //
        //foo(std::array<int, 9>{}, std::array<double, 4>{}, 0.0);
    }

    template<typename R, typename A>
    void foo_lambda(R(*fptr)(A))
    {
        puts(__PRETTY_FUNCTION__);
    }

    void lambda_template_func()
    {
        /*
        Captureless lambda types are always implicitly convertible to function pointer type. 
        But being implicitly convertible to a thing doesn¡¯t mean actually being that thing!
        Protip: If you absolutely need the function-pointer conversion to happen, add a unary +.
        */
        //foo_lambda([](double x) { return int(x); }); // error
        //foo_lambda(+[](double x) { return int(x); }); // compiles
    }

    template<typename T>
    class is_pointer_impl 
    {
    public: 
        static bool _() { return false; } 
    };

    template<typename Tp>
    class is_pointer_impl<Tp*> 
    { 
    public: 
        static bool _() { return true; } 
    };

    template<typename T>
    bool pointer_guess(T x)
    {
        return is_pointer_impl<T>::_();
    }

    void test_pointer_guess()
    {
        int i = 0;
        int* p = &i;
        std::cout << " i is pointer? " << pointer_guess(i) << "\n";
        std::cout << " &i is pointer? " << pointer_guess(&i) << "\n";
        std::cout << " p is pointer? " << pointer_guess(p) << "\n";
        std::cout << " *p is pointer? " << pointer_guess(*p) << "\n";
    }
} //end of anonymous namespace.

void template_func()
{
    simple_template_func();
    template_func_deduction();
    lambda_template_func();
    test_pointer_guess();
}