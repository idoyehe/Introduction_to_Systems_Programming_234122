#include <iostream>
#include <list>
#include <vector>
#include <assert.h>
using std::list;
using std::vector;
using std::cout;
using std::endl;

template <class T, typename IT1, typename IT2, typename Compare>
list<T> mergeData(IT1 data_struct1,const IT1& data_struct1_end,
                  IT2 data_struct2,const IT2& data_struct2_end,
                  const Compare& compare){
    list<T> merged_list;
    while(data_struct1!=data_struct1_end&&data_struct2!=data_struct2_end){
        if(compare(*data_struct1,*data_struct2)){
            merged_list.push_back(*data_struct2);//insert element from data_struct 2
            data_struct2++;//increase ONLY iterator of data_struct 2
            continue;
        }
        merged_list.push_back(*data_struct1);//insert element from data_struct 1
        data_struct1++;//increase ONLY iterator of data_struct 1
    }
    while (data_struct1!=data_struct1_end){
        merged_list.push_back(*data_struct1);
        data_struct1++;
    }
    assert(data_struct1==data_struct1_end);
    while (data_struct2!=data_struct2_end){
        merged_list.push_back(*data_struct2);
        data_struct2++;
    }
    assert(data_struct2==data_struct2_end);
    return merged_list;
}

bool compare(int n1,int n2){
    return n2<n1;
}

int main() {
    list<int> l1;
    vector<int> v2;
    cout << "Numbers in list:";
    for (int i = 0; i < 20; i += 2) {
        cout << i << ' ';
        l1.push_back(i);
    }
    cout << endl;
    cout << "Numbers in vector:";
    for (int i = 1; i < 30; i += 2) {
        cout << i << ' ';
        v2.push_back(i);
    }
    cout << endl;
    list<int> merged = mergeData<int,list<int>::iterator,vector<int>::iterator>
            (l1.begin(),l1.end(),v2.begin(),v2.end(),compare);
    cout << "Merged list numbers:";
    for (list<int>::iterator it = merged.begin(); it != merged.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}