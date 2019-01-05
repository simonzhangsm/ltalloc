// based on code by Jerry Coffin (most likely Public Domain)
// - rlyeh

#pragma once

#include <stdlib.h>
#include <new>
#include <limits>

#include "ltalloc.h"

namespace lt {
template <class T>
struct allocator {

    template <class U> struct rebind { typedef allocator<U> other; };
    allocator() throw() {}
    allocator(const allocator&) throw() {}

    template <class U> allocator(const allocator<U>&) throw(){}

    ~allocator() throw() {}

    T* address(T& x) const { return &x; }
    const T* address(const T& x) const { return &x; }

    T* allocate(size_t s, void const * = 0) {
        if (0 == s)
            return NULL;
        T* temp = (T*)ltmalloc(s * sizeof(T));
        if (temp == NULL)
            throw std::bad_alloc();
        return temp;
    }

    void deallocate(T* p, size_t) {
        ltfree(p);
    }

    size_t max_size() const throw() {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    void construct(T* p, const T& val) {
        new((void *)p) T(val);
    }

    void destroy(T* p) {
        p->~T();
    }
};
}
