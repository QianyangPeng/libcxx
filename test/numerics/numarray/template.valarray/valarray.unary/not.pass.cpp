//===----------------------------------------------------------------------===//
//
// ��������������������The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <valarray>

// template<class T> class valarray;

// valarray<bool> operator!() const;

#include <valarray>
#include <cassert>

int main()
{
    {
        typedef int T;
        T a[] = {1, 2, 3, 4, 5};
        const unsigned N = sizeof(a)/sizeof(a[0]);
        std::valarray<T> v(a, N);
        std::valarray<bool> v2 = !v;
        assert(v2.size() == v.size());
        for (int i = 0; i < v2.size(); ++i)
            assert(v2[i] == !v[i]);
    }
    {
        typedef double T;
        T a[] = {1, 2.5, 3, 4.25, 5};
        const unsigned N = sizeof(a)/sizeof(a[0]);
        std::valarray<T> v(a, N);
        std::valarray<bool> v2 = !(v + v);
        assert(v2.size() == v.size());
        for (int i = 0; i < v2.size(); ++i)
            assert(v2[i] == !2*v[i]);
    }
}