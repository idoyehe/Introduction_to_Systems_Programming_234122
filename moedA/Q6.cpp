#include <iostream>
using namespace std;
class XX {
protected:
    double data;
public:
    XX():data(0) {cout<<"XX::XX()"<<endl;}
    XX(double d):data(d) {cout<<"XX::XX(double d)"<<endl;}
    XX(const XX& a):data(a.data) {cout<<"XX::XX(const XX& a)"<<endl;}
    virtual operator double() {cout <<"XX::double()"<<endl; return data;}
    void operator()() {cout <<"XX::operator()"<<endl;}
    operator int() {cout <<"XX::int()"<<endl; return static_cast<int>(data);}
};
class YYY : public XX {
public:
    YYY(){cout<<"YYY::YYY()"<<endl;}
    YYY(double d):XX(d){cout<<"YYY::YYY(double d)"<<endl;}
    operator double() {cout <<"YYY::double()"<<endl; return data;}
    operator int() {cout <<"YYY::int()"<<endl; return static_cast<int>(data);}
    void operator[](double d) {cout <<"YYY::operator[]()"<<endl; throw YYY(d);}
    YYY operator+(double d) {cout <<"YYY::operator+()"<<endl; YYY temp(*this);
        temp.data+= d; return temp;}
    void operator()() {cout <<"YYY::operator()"<<endl;}
};

int main() {
    YYY b;
    cout << "a:" << endl;
    double d = b + 3.0;
    try {
        cout << "b:" << endl;
        XX *a = &b;
        cout << "c:" << endl;
        (*a)();
        cout << "d:" << endl;
        b[d];
        cout << "e:" << endl;
    } catch (int e) {
        cout << "caught int" << endl;
    } catch (double e) {
        cout << "caught double" << endl;
    } catch (const XX &e) {
        cout << "caught XX" << endl;
    } catch (const YYY &e) {
        cout << "caught YYY" << endl;
    }
    try {
        cout << "f:" << endl;
        b[d];
        cout << "g:" << endl;
    } catch (int e) {
        cout << "caught int" << endl;
    } catch (double e) {
        cout << "caught double" << endl;
    } catch (const YYY e) {
        cout << "caught YYY" << endl;
    } catch (const XX e) {
        cout << "caught XX" << endl;
    }
    return 0;
}