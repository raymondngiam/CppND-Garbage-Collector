# CppND-Garbage-Collector

The final project for this Memory Management course is to implement your own
version of a smart pointer. You can think of this as implementing your own
garbage collector, to use a concept from other programming languages. Building
this project will help you understand both how to work with pointers and
references, and also why smart pointers are so important to modern C++
programming. Complete the implementations and verify that your implementation
does not have any memory leaks!

# Dependencies

- cmake >= 3.18
- make >= 4.1
- g++ >= 7.5


# Building

The main program can be built and run by doing the following from the project top directory.

``` shell
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j2 
$ ../bin/main
```

# Example usage 1 - Non array

```
#include "gc_pointer.h"
#include "LeakTester.h"

int main() {
    auto ptr1 = new int(19);
    auto ptr2 = new int(21);
    auto ptr3 = new int(28);
    
    // scope 1
    if (true) {
        //ctor
        Pointer<int> p(ptr1);
        std::cout<<"ctor"<<std::endl;
        Pointer<int>::showlist();

        // scope 2
        if (true){
            //copy constructor
            Pointer<int> p2(p);
            std::cout<<"copy constructor"<<std::endl;
            Pointer<int>::showlist();
            std::cout<<"p: "<<p<<std::endl;
            std::cout<<"p2: "<<p2<<std::endl<<std::endl;

            //assignment of pointer to Pointer
            p2 = ptr2;
            p2 = ptr3;
            std::cout<<"assignment of pointer to Pointer"<<std::endl;
            Pointer<int>::showlist();
            std::cout<<"p: "<<p<<std::endl;
            std::cout<<"p2: "<<p2<<std::endl<<std::endl;
        }
        // end of scope 2: Pointer p2 should be disposed
        std::cout<<"end of scope 2"<<std::endl;
        Pointer<int>::showlist();
    }
    // end of scope 1: Pointer p1 should be disposed
    std::cout<<"end of scope 1"<<std::endl;
    Pointer<int>::showlist();

    return 0;
}
```

### Output

```
ctor
refContainer<i, 0>:
memPtr refcount value
[0x55c2de4a7280] 1  19

copy constructor
refContainer<i, 0>:
memPtr refcount value
[0x55c2de4a7280] 2  19

p: 0x55c2de4a7280
p2: 0x55c2de4a7280

assignment of pointer to Pointer
refContainer<i, 0>:
memPtr refcount value
[0x55c2de4a7280] 1  19
[0x55c2de4a72d0] 0  21
[0x55c2de4a7320] 1  28

p: 0x55c2de4a7280
p2: 0x55c2de4a7320

end of scope 2
refContainer<i, 0>:
memPtr refcount value
[0x55c2de4a7280] 1  19

end of scope 1
refContainer<i, 0>:
memPtr refcount value
  Container is empty!

```

### Brief walkthrough

- Here a `Pointer<int>` object, `p` is instantiated via constructor by inputting address of a heap `int` variable. We observed that a memory address is added to the `refContainer` list of the `Pointer<int>` class, with `refcount` = `1`, and `value` = `19`.

- When object `p2` is instantiated by a copy of `p`, the existing item in `Pointer<int>` class's `refContainer` list with `value` = `19`, has its `refcount` incremented by 1. This means that there are two `Pointer<int>` objects (`p` and `p2`) are referencing to this `int` variable address.

- Object `p2` is then assigned to two different heap `int` variables, `21` and `28`, sequentially. We observed that 2 memory addresses were appended to the `refContainer` list. The `refcount` for the items `19`, `21`, and `28` are now `1`, `0`, and `1`, respectively. Item `19` is now referenced by `Pointer<int>` object `p`, and item `28` is now referenced by `p2`.

- Next, when program exit the scope for object `p2`, we observed that items `21`, and `28` were removed from the `refContainer` list. This is due to the destructor for the `Pointer<int>` object was executed thus the heap memory was released for any references that has `refcount` = `0`.

- Finally, when program exit the scope for object `p1`, we observed that item `19` was also removed from the `refContainer` list.

# Example usage 2 - Array

```
#include "gc_pointer.h"
#include "LeakTester.h"

int main()
{
    const int size = 3;
    auto ptr4 = new std::string[size]{"abc","def","ghi"};

    // scope 1
    if (true){
        //ctor
        Pointer<std::string,size> p3(ptr4);
        std::cout<<"ctor"<<std::endl;
        Pointer<std::string,size>::showlist();
        std::cout<<"Array content:"<<std::endl;
        for (auto it = p3.begin(); it != p3.end(); it++)
        {
            std::cout<<*it<<std::endl;
        }
        std::cout<<"Array content (alternative):"<<std::endl;
        for (const auto& item : p3)
        {
            std::cout<<item<<std::endl;
        }
    }
    // end of scope 1: Pointer p3 should be disposed
    std::cout<<"end of scope 1"<<std::endl;
    Pointer<std::string,size>::showlist();

    return 0;
}
```

### Output:

```
ctor
refContainer<NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, 3>:
memPtr refcount value
 [0x55f2fbe4d498] 1  abc

Array content:
abc
def
ghi
Array content (alternative):
abc
def
ghi
end of scope 1
refContainer<NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, 3>:
memPtr refcount value
  Container is empty!
```

### Brief walkthrough

- Here, a string array is instantiated from heap using the `new` keyword, and is used to instantiate a `Pointer<std::string,size>` object, `p3`.

- The `refContainer` list of the `Pointer<std::string,size>` class was registered with an entry of memory address.

- The content of the array can be accessed via `for loop` with `iterator` from the `Pointer<std::string,size>` class.

- Finally, when program exit the scope for object `p3`, we observed that item registered was removed from the `refContainer` list.


