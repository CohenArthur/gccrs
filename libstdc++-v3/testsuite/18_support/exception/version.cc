// { dg-do preprocess { target c++26 } }
// { dg-add-options no_pch }

#include <exception>

#ifndef __cpp_lib_constexpr_exceptions
# error "Feature test macro for constexpr_exceptions is missing in <exception>"
#elif __cpp_lib_constexpr_exceptions < 202411L
# error "Feature test macro for constexpr_exceptions has wrong value in <exception>"
#endif
