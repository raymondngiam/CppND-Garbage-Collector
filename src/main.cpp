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
