//===----------------------------------------------------------------------===//
//
// ��������������������The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <forward_list>

// void push_front(value_type&& v);

#include <forward_list>
#include <cassert>

#include "../../../MoveOnly.h"

int main()
{
#ifdef _LIBCPP_MOVE
    {
        typedef MoveOnly T;
        typedef std::forward_list<T> C;
        C c;
        c.push_front(1);
        assert(c.front() == 1);
        assert(distance(c.begin(), c.end()) == 1);
        c.push_front(3);
        assert(c.front() == 3);
        assert(*next(c.begin()) == 1);
        assert(distance(c.begin(), c.end()) == 2);
    }
#endif
}