#include <ostream>
#include <iostream>


using std::ostream;

class precision{
    int point;
public:
    precision(int n):point(n){}
    int getPoint()const { return point;}

};

ostream& operator<<(ostream & out, const precision &p){
    out.precision(p.getPoint());
    return out;
}

int main(){
    double a=1.23456789,b=2.123456;
    std::cout << precision(5) << a << " " << precision(2) << b << std::endl;
    return 0;
}