//===----------------------------------------------------------------------===//
//
// ��������������������The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <memory>

// template <class OuterAlloc, class... InnerAllocs>
//   class scoped_allocator_adaptor

// pointer allocate(size_type n, const_void_pointer hint);

#include <memory>
#include <cassert>

#include "../allocators.h"

int main()
{
#ifdef _LIBCPP_MOVE

    {
        typedef std::scoped_allocator_adaptor<A1<int>> A;
        A a;
        A1<int>::allocate_called = false;
        assert(a.allocate(10, (const void*)0) == (int*)10);
        assert(A1<int>::allocate_called == true);
    }
    {
        typedef std::scoped_allocator_adaptor<A1<int>, A2<int>> A;
        A a;
        A1<int>::allocate_called = false;
        assert(a.allocate(10, (const void*)10) == (int*)10);
        assert(A1<int>::allocate_called == true);
    }
    {
        typedef std::scoped_allocator_adaptor<A1<int>, A2<int>, A3<int>> A;
        A a;
        A1<int>::allocate_called = false;
        assert(a.allocate(10, (const void*)20) == (int*)10);
        assert(A1<int>::allocate_called == true);
    }

    {
        typedef std::scoped_allocator_adaptor<A2<int>> A;
        A a;
        A2<int>::allocate_called = false;
        assert(a.allocate(10, (const void*)0) == (int*)0);
        assert(A2<int>::allocate_called == true);
    }
    {
        typedef std::scoped_allocator_adaptor<A2<int>, A2<int>> A;
        A a;
        A2<int>::allocate_called = false;
        assert(a.allocate(10, (const void*)10) == (int*)10);
        assert(A2<int>::allocate_called == true);
    }
    {
        typedef std::scoped_allocator_adaptor<A2<int>, A2<int>, A3<int>> A;
        A a;
        A2<int>::allocate_called = false;
        assert(a.allocate(10, (const void*)20) == (int*)20);
        assert(A2<int>::allocate_called == true);
    }
#endif
}