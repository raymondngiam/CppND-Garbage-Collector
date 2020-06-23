#pragma once
// This class defines an element that is stored
// in the garbage collection information list.
//
template <class T>
class PtrDetails
{
  public:
    unsigned refcount; // current reference count
    T *memPtr;         // pointer to allocated memory
    /* isArray is true if memPtr points
to an allocated array. It is false
otherwise. */
    bool isArray; // true if pointing to array
    /* If memPtr is pointing to an allocated
array, then arraySize contains its size */
    unsigned arraySize; // size of array
    // Here, mPtr points to the allocated memory.
    // If this is an array, then size specifies
    // the size of the array.

    // ctor
    // implementation is declared in .h instead of .hpp, due to
    // redeclaration of class funtion may not have default arguments
    PtrDetails(T *m_ptr, unsigned size = 0)
    {
        // TODO: Implement PtrDetails ctor
        refcount = 1;
        memPtr = m_ptr;
        if (size != 0) isArray = true;
        else isArray = false;

        arraySize = size;
    }
};

#include "gc_details.hpp"
