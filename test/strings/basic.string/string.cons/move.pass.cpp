//===----------------------------------------------------------------------===//
//
// ��������������������The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <string>

// basic_string(basic_string<charT,traits,Allocator>&& str);

#include <string>
#include <cassert>

#ifdef _LIBCPP_MOVE

#include "../test_allocator.h"

template <class S>
void
test(S s0)
{
    S s1 = s0;
    S s2 = std::move(s0);
    assert(s2.__invariants());
    assert(s0.__invariants());
    assert(s2 == s1);
    assert(s2.capacity() >= s2.size());
    assert(s2.get_allocator() == s1.get_allocator());
}

#endif

int main()
{
#ifdef _LIBCPP_MOVE
    typedef test_allocator<char> A;
    typedef std::basic_string<char, std::char_traits<char>, A> S;
    test(S(A(3)));
    test(S("1", A(5)));
    test(S("1234567890123456789012345678901234567890123456789012345678901234567890", A(7)));
#endif
}