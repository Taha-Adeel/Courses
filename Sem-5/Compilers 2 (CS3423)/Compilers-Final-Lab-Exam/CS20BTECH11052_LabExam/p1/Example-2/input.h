#include<iostream>
#include "test.h"

/// Class C doxygen comment
class C {    
    public:
    C();
    int var1;
    void func1();
}

/// Class B doxygen comment
class B : {    
    private:
    B(int a1);
    int var1;
    void func1();

    protected:
    int var2;
    void func2(int a1); // this is a C++ single line comment, ignore it
}

/// Class A doxygen comment
class A : public B {    

    private:
    A()
    int var1;
    void func1();
        
    public:
    A(int a1, int a2);
    int var3;
    void func3(int a1, int a2);
    void func4(int a1, int a2, int a3);
}