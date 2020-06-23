#pragma once
// Exception thrown when an attempt is made to
// use an Iter that exceeds the range of the
// underlying object.
//
class OutOfRangeExc
{
    // Add functionality if needed by your application.
};


// An iterator-like class for cycling through arrays
// that are pointed to by GCPtrs. Iter pointers
// ** do not ** participate in or affect garbage
// collection. Thus, an Iter pointing to
// some object does not prevent that object
// from being recycled.
//
template <class T>
class Iter
{
    T *ptr;
    // current pointer value
    T *end;
    // points to element one past end

    T *begin;        // points to start of allocated array
    unsigned length; // length of sequence
  public:
    // ctor
    Iter();
    Iter(T *p, T *first, T *last);

    // Return length of sequence to which this
    // Iter points.
    unsigned size();

    // Return value pointed to by ptr.
    // Do not allow out-of-bounds access.
    T &operator*();

    // Return address contained in ptr.
    // Do not allow out-of-bounds access.
    T *operator->();

    // Prefix ++.
    Iter operator++();

    // Prefix --.
    Iter operator--();

    // Postfix ++.
    Iter operator++(int notused);

    // Postfix --.
    Iter operator--(int notused);

    // Return a reference to the object at the
    // specified index. Do not allow out-of-bounds
    // access.
    T &operator[](int i);

    // Define the relational operators.
    bool operator==(Iter op2);
    bool operator!=(Iter op2);
    bool operator<(Iter op2);
    bool operator<=(Iter op2);
    bool operator>(Iter op2);
    bool operator>=(Iter op2);

    // Subtract an integer from an Iter.
    Iter operator-(int n);

    // Add an integer to an Iter.
    Iter operator+(int n);

    // Return number of elements between two Iters.
    int operator-(Iter<T> &itr2);
};

#include "gc_iterator.hpp"
