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

## Output:

```
+---------------+
| FINAL REPORT: |
+---------------+

Total number of allocations: 6
Total number of deallocations: 6
Total number of allocations in bytes: 132
Total number of deallocations in bytes: 132
Maximum memory occupation during runtime in bytes: 132
Memory occupation upon completion: 0


GREAT JOB! YOU DO NOT HAVE MEMORY LEAKAGE
```

