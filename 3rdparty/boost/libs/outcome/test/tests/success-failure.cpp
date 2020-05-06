/* Unit testing for outcomes
(C) 2017-2019 Niall Douglas <http://www.nedproductions.biz/> (10 commits)


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#include <boost/outcome/result.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

#include <iostream>

BOOST_OUTCOME_AUTO_TEST_CASE(works_success_failure, "Tests that the success and failure type sugars work as intended")
{
  using namespace BOOST_OUTCOME_V2_NAMESPACE;
#ifdef __cpp_deduction_guides
  std::cout << "__cpp_deduction_guides = 1" << std::endl;
#endif
  {
    auto a = success(5);
    auto b = success();
    auto c = success("hello");
    static_assert(std::is_same<decltype(a), success_type<int>>::value, "");
    static_assert(std::is_same<decltype(b), success_type<void>>::value, "");
    static_assert(std::is_same<decltype(c), success_type<const char *>>::value, "");
    static_assert(std::is_same<decltype(a)::value_type, int>::value, "");
    // static_assert(std::is_same<decltype(b.value), int>::value, "");
    static_assert(std::is_same<decltype(c)::value_type, const char *>::value, "");
  }
#if !defined(__APPLE__) || defined(__cpp_exceptions)
  {
    auto e = boost::copy_exception(std::exception());
    auto a = failure(5);
    auto b = failure(5, e);
    auto c = failure(5, 5);
    static_assert(std::is_same<decltype(a), failure_type<int, void>>::value, "");
    static_assert(std::is_same<decltype(b), failure_type<int, boost::exception_ptr>>::value, "");
    static_assert(std::is_same<decltype(c), failure_type<int, int>>::value, "");
    static_assert(std::is_same<decltype(a)::error_type, int>::value, "");
    static_assert(std::is_same<decltype(b)::error_type, int>::value, "");
    static_assert(std::is_same<decltype(b)::exception_type, boost::exception_ptr>::value, "");
    static_assert(std::is_same<decltype(c)::error_type, int>::value, "");
    static_assert(std::is_same<decltype(c)::exception_type, int>::value, "");
  }
#endif
}