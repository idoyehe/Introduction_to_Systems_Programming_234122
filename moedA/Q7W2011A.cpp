#include <iostream>

class A{
public:
    virtual void printError() const {
        std::cout<<"UserFault"<<std::endl;
    }
};

class B : public A{
public:
    void printError() const override {
        std::cout<<"ProgrammerFault"<<std::endl;
    }
};

void f(){
    throw B();
}

int main() {
    try {
        f();
    } catch (A a) {
        a.printError();
    }
    return 0;
}