#include <iostream>
#include <vector>

using std::cout;
using std::endl;

int fib(int n){
    if(n==0||n==1){
        return n;
    }
    return fib(n-1)+fib(n-2);
}

class FibIterator{
    int prev;
    int current;
public:
    FibIterator(int n):current(fib(n)){
        if (n>0)
            prev=fib(n-1);
        else
            prev=0;
    }
    int operator*() const{
        return current;
    }
    bool operator!=(const FibIterator& it){
        return it.prev!=prev||it.current!=current;
    }
    FibIterator& operator++() {
        if (!prev && !current) {
            current = 1;
        } else {
            int temp = current;
            current += prev;
            prev = temp;
            return *this;
        }
    }
    FibIterator operator++(int i){
        FibIterator temp=*this;
        ++(*this);
        return temp;
    }
};

using std::ostream;
using std::string;

class debugStream{
private:
    ostream& out;
public:
    debugStream(ostream & channel):out(channel){}

    template <class T>
    debugStream& operator<<(const T& print_me){
        out << print_me << ", ";
        return *this;
    }
    ~debugStream(){
        out<<"\b\b "<<std::endl;
    }
};


#define cdbg debugStream(cout)
template <class T, class DATA>
class Stack{
    DATA stack;
public:
    void push(const T& ele){
        stack.push_back(ele);
    }

};



int main() {/*
// Get an iterator to the 1st Fibonacci number
    FibIterator i(0);
// Print all Fibonacci numbers starting from the first Fibonacci number and
// until the first number which is greater than 200 (Including that number)
    while (*i++ < 200) {
        cout << *i << endl;
    }
// Print the even numbers from the first 10 Fibonacci numbers
    for (FibIterator i(0); i != FibIterator(10); ++i) {
        if (*i % 2 == 0) {
            cout << *i << endl;
        }
    }*/
Stack<int,std::vector<int>>my;
    std::string str=

    return 0;
}