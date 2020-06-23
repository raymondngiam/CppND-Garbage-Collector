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

# Example usage

```
#include "gc_pointer.h"
#include "LeakTester.h"

int main()
{
    std::cout<<"Non array example:"<<std::endl;
    std::cout<<"=================="<<std::endl;
    auto ptr1 = new int(19);
    auto ptr2 = new int(21);
    auto ptr3 = new int(28);
    
    // scope 1
    if (true){
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

            //assignment of pointer to Pointer
            p = ptr2;
            p = ptr3;
            std::cout<<"assignment of pointer to Pointer"<<std::endl;
            Pointer<int>::showlist();
        }
        // end of scope 2: Pointer p2 should be disposed
        std::cout<<"end of scope 2"<<std::endl;
        Pointer<int>::showlist();
    }
    // end of scope 1: Pointer p1 should be disposed
    std::cout<<"end of scope 1"<<std::endl;
    Pointer<int>::showlist();

    std::cout<<"Array example:"<<std::endl;
    std::cout<<"=============="<<std::endl;
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

# Output:

```
Non array example:
==================
ctor
refContainer<i, 0>:
memPtr refcount value
 [0x55f2fbe4d280] 1  19

copy constructor
refContainer<i, 0>:
memPtr refcount value
 [0x55f2fbe4d280] 2  19

assignment of pointer to Pointer
refContainer<i, 0>:
memPtr refcount value
 [0x55f2fbe4d280] 1  19
[0x55f2fbe4d2d0] 0  21
[0x55f2fbe4d320] 1  28

end of scope 2
refContainer<i, 0>:
memPtr refcount value
 [0x55f2fbe4d320] 1  28

end of scope 1
refContainer<i, 0>:
memPtr refcount value
  Container is empty!

 
Array example:
==============
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

 


+---------------+
| FINAL REPORT: |
+---------------+

Total number of allocations: 8
Total number of deallocations: 8
Total number of allocations in bytes: 276
Total number of deallocations in bytes: 276
Maximum memory occupation during runtime in bytes: 144
Memory occupation upon completion: 0


GREAT JOB! YOU DO NOT HAVE MEMORY LEAKAGE

```

