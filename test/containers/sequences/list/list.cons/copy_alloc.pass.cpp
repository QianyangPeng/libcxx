//===----------------------------------------------------------------------===//
//
// ��������������������The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <list>

// list(const list& c, const allocator_type& a);

#include <list>
#include <cassert>
#include "../../../DefaultOnly.h"
#include "../../../test_allocator.h"

int main()
{
    {
        std::list<int, test_allocator<int> > l(3, 2, test_allocator<int>(5));
        std::list<int, test_allocator<int> > l2(l, test_allocator<int>(3));
        assert(l2 == l);
        assert(l2.get_allocator() == test_allocator<int>(3));
    }
    {
        std::list<int, other_allocator<int> > l(3, 2, other_allocator<int>(5));
        std::list<int, other_allocator<int> > l2(l, other_allocator<int>(3));
        assert(l2 == l);
        assert(l2.get_allocator() == other_allocator<int>(3));
    }
}