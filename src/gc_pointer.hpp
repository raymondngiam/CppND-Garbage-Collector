// STATIC INITIALIZATION
// Creates storage for the static variables
template <class T, int size>
std::list<PtrDetails<T> > Pointer<T, size>::refContainer;
template <class T, int size>
bool Pointer<T, size>::first = true;

// Constructor for both initialized and uninitialized objects. -> see class interface
template<class T,int size>
Pointer<T,size>::Pointer(T* t){
    // Register shutdown() as an exit function.
    if (first)
        atexit(shutdown);
    first = false;

    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab
    PtrDetails<T> new_item(t, size);
    refContainer.push_back(new_item);
    addr = t;
    if (size > 0)
        isArray = true;
    arraySize = size;
}
// Copy constructor.
template< class T, int size>
Pointer<T,size>::Pointer(const Pointer& ob){

    // TODO: Implement Pointer constructor
    // Lab: Smart Pointer Project Lab
    typename std::list<PtrDetails<T> >::iterator p;
    p = findPtrInfo(ob.addr);
    p->refcount++; // increment ref count
    addr = ob.addr;
    arraySize = ob.arraySize;
    if (arraySize > 0)
        isArray = true;
    else
        isArray = false;
}

// Destructor for Pointer.
template <class T, int size>
Pointer<T, size>::~Pointer(){
    
    // TODO: Implement Pointer destructor
    // Lab: New and Delete Project Lab
    typename std::list<PtrDetails<T>>::iterator p;
    p = findPtrInfo(addr);
    if (p->refcount)
        p->refcount--; 
    // decrement ref count
    // Collect garbage when a pointer goes out of scope.
    collect();
    // For real use, you might want to collect unused memory less frequently,
    // such as after refContainer has reached a certain size, after a certain number of Pointers have gone out of scope,
    // or when memory is low.
}

// Collect garbage. Returns true if at least
// one object was freed.
template <class T, int size>
bool Pointer<T, size>::collect(){

    // TODO: Implement collect function
    // LAB: New and Delete Project Lab
    // Note: collect() will be called in the destructor
    bool memfreed = false;
    typename std::list<PtrDetails<T> >::iterator p;
    do{
        // Scan refContainer looking for unreferenced pointers.
        for (p = refContainer.begin(); p != refContainer.end(); p++){
            // If in-use, skip.
            if (p->refcount> 0)
                continue;
            memfreed = true;
            // Remove unused entry from refContainer.
            refContainer.remove(*p);

            // Free memory unless the Pointer is null.
            if (p->memPtr){
                if (p->isArray){
                    delete[] p->memPtr; // delete array
                }
                else{
                    delete p->memPtr; // delete single element
                }
            }
            // Restart the search.
            break;
        }
    } while (p != refContainer.end());
    return memfreed;
}

// Overload assignment of pointer to Pointer.
template <class T, int size>
T* Pointer<T, size>::operator=(T* t){

    // TODO: Implement operator==
    // LAB: Smart Pointer Project Lab
    auto p = findPtrInfo(this->addr);
    --p->refcount;

    p =findPtrInfo(t);
    if ( p != refContainer.end()) {
        ++p->refcount;
    } else {
        PtrDetails<T> new_item(t, size);
        refContainer.push_back(new_item); 
    }
        
    //std::cout << "#debug the refcount of current: " << p->refcount << std::endl;
    //std::cout << "#debug refContainer size is: " << refContainerSize() << std::endl;
    this->addr = t;
    return addr;
}
// Overload assignment of Pointer to Pointer.
template <class T, int size>
Pointer<T, size>& Pointer<T, size>::operator=(Pointer& rv){

    // TODO: Implement operator==
    // LAB: Smart Pointer Project Lab
    typename std::list<PtrDetails<T> >::iterator p;
    // First, decrement the reference count
    // for the memory currently being pointed to.
    p = findPtrInfo(addr);
    p->refcount--;
    // Next, increment the reference count of
    // the new address.
    p = findPtrInfo(rv.addr);
    p->refcount++;  // increment ref count
    addr = rv.addr; // store the address.
    return rv;
}

// A utility function that displays refContainer.
template <class T, int size>
void Pointer<T, size>::showlist(){
    typename std::list<PtrDetails<T> >::iterator p;
    std::cout << "refContainer<" << typeid(T).name() << ", " << size << ">:\n";
    std::cout << "memPtr refcount value\n ";
    if (refContainer.begin() == refContainer.end())
    {
        std::cout << " Container is empty!\n\n ";
    }
    for (p = refContainer.begin(); p != refContainer.end(); p++)
    {
        std::cout << "[" << (void *)p->memPtr << "]"
             << " " << p->refcount << " ";
        if (p->memPtr)
            std::cout << " " << *p->memPtr;
        else
            std::cout << "---";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
// Find a pointer in refContainer.
template <class T, int size>
typename std::list<PtrDetails<T> >::iterator
Pointer<T, size>::findPtrInfo(T *ptr){
    typename std::list<PtrDetails<T> >::iterator p;
    // Find ptr in refContainer.
    for (p = refContainer.begin(); p != refContainer.end(); p++)
        if (p->memPtr == ptr)
            return p;
    return p;
}
// Clear refContainer when program exits.
template <class T, int size>
void Pointer<T, size>::shutdown(){
    if (refContainerSize() == 0)
        return; // list is empty
    typename std::list<PtrDetails<T> >::iterator p;
    for (p = refContainer.begin(); p != refContainer.end(); p++)
    {
        // Set all reference counts to zero
        p->refcount = 0;
    }
    collect();
}
