#include "test.h"

/// Class C with only protected members
class C {    
    protected:
    C(int a1);
    int var1;
    void func1(int a1);
}

/// Class B with private and public members
/// Private members coming from parent class C
class B : private C {    
    private:
    B(int a1); // this is a C++ single line comment
    public:
    B(int a1, int a2);
    int var2;
    void func2();    
}

/// Class A with only public members
class A : public B {        
    public:
    A(int a1, int a2);
    int var3;
    void func3();
}