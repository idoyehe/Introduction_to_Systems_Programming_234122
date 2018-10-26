#include <ostream>
#include <iostream>

using std::cout;
using std::endl;

template <class Iterator>
int find2ndMalla(Iterator begin,Iterator end) {
    int i = 1;
    while (++begin != end) {
        Iterator it = --begin;
        if (*(++begin) < *it) break;
        i++;
    }
    return i;
}

template <class Iterator>
int numofMalla(Iterator begin,Iterator end) {
    int count=0;
    while (begin!=end){
        int i=find2ndMalla(begin,end);
        while(begin!=end&&i>0){
            begin++;
            i--;
        }
        count++;
    }
    return count;
}



int main(){
int arr[5]={0};
    int x=5;
    void v =(void)x;


    return 0;
}