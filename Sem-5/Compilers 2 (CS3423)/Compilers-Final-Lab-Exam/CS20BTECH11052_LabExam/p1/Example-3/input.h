#include<iostream>

/// Class C with only protected members
class C {    
    protected:
    C();
    int var1;
    void func1();
}

/// Class B with only public members
class B : {    
    public:
    B(int a1);
    int var2;
    void func2(int a1);
}

/// Class A with private and protected members
class A : protected B, private C {        
    public:
    A()
    A(int a1);
}