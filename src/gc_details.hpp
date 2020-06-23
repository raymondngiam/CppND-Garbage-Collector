// Overloading operator== allows two class objects to be compared.
// This is needed when we are iterating through STL list to look 
// for a specific ptr in the `Pointer<T, size>::findPtrInfo(T *ptr)`
// function.
template <class T>
bool operator==(const PtrDetails<T> &ob1,
                const PtrDetails<T> &ob2)
{
    // TODO: Implement operator==
    return (ob1.memPtr == ob2.memPtr);
}
