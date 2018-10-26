#include <functional>
#include "../list.h"
#include "../mtmtest.h"

/**
 * Function object for finding a target integer
 */
using namespace mtm::ListExceptions;

class EqualTo {
private:
  int target;
public:
  EqualTo(int i) : target(i) {}
  bool operator()(const int& i) const {
    return i == target;
  }
};

static bool compare (int e1,int e2){
    return e1<e2;
}

static void testConstructor() {
    List<int> list;
    List<char> list2;
    List<double> list3;
}

static void testListBegin(){
    List<int> list;
    ASSERT_THROWS(ElementNotFound,*(list.begin()));
    list.insert(1);
    ASSERT_EQUALS(*(list.begin()),1);
    *(list.begin())=7;
    ASSERT_THROWS(ElementNotFound,*(--list.begin()));
}

static void testListEnd(){
    List<int> list;
    ASSERT_THROWS(ElementNotFound,*(list.end()));
    list.insert(1);
    ASSERT_THROWS(ElementNotFound,*(list.end()));
}

static void testIntInsert(){
    List<int> list;
    for(int i=1;i<10;++i) {
        list.insert(i);
    }
    ASSERT_EQUALS(list.getSize(),9);
    int i=1;
    for(List<int>::Iterator it= list.begin();it!=list.end();++it){
        ASSERT_EQUALS(*(it),i++);
    }
}

static void testIteratorOperatorValue(){
    List<int> list;
    ASSERT_THROWS(ElementNotFound,*(list.begin()));
    list.insert(1);
    ASSERT_EQUALS(1,*(list.begin()));
}

static void testIteratorOperatorsEqual(){
    List<int> list;
    List<int>::Iterator it1=list.begin();
    List<int>::Iterator it2=list.begin();
    ASSERT_EQUALS(it1,it2);
    ASSERT_TRUE(it1==it2);
    ASSERT_TRUE(it2==it1);
    list.insert(1);
    it1=list.begin();
    ASSERT_FALSE(it1==it2);
}

static void testIteratorOperatorsNOTEqual() {
    List<int> list1;
    List<int> list2;
    List<int>::Iterator it1 = list1.begin();
    List<int>::Iterator it2 = list2.begin();
    ASSERT_NOT_EQUAL(it1, it2);
    ASSERT_TRUE(it1 != it2);
    ASSERT_TRUE(it2 != it1);
    list1.insert(1);
    list2.insert(1);
    it1 = list1.begin();
    List<int>::Iterator it3 = list1.begin();
    ASSERT_FALSE(it1 != it3);
    it3 = list2.begin();
    ASSERT_FALSE(it1 == it3);
    ASSERT_NOT_EQUAL(it1, it3);
    ASSERT_TRUE(it1 != it3);
    ASSERT_TRUE(it3 != it1);

}

static void testIteratorOperatorsAdvance(){
    List<int> list;
    List<int>::Iterator it=list.begin();
    ASSERT_EQUALS(it,list.end());
    list.insert(1);
    it=list.begin();
    ASSERT_EQUALS(*(it++),1);
    ASSERT_EQUALS(it,list.end());
    it=list.begin();
    ASSERT_EQUALS(++it,list.end());
}

static void testIteratorOperatorsDecrease(){
    List<int> list;
    List<int>::Iterator it=list.begin();
    ASSERT_EQUALS(it,list.end());
    list.insert(1);
    it=list.begin();
    ASSERT_EQUALS(--it,list.end());
    it=list.begin();
    ASSERT_EQUALS(*(it),1);
    ASSERT_EQUALS(*(it--),1);
    ASSERT_EQUALS(it,list.end());


}

static void testIntInsert2(){
    List<int> list;
    List<int> temp;
    List<int>::Iterator it=list.end();
    ASSERT_THROWS(ElementNotFound,temp.insert(1,it));
    list.insert(2,list.begin());
    list.insert(1,list.begin());
    list.insert(3,list.end());
    int i=1;
    for(it=list.begin();it!=list.end();it++){
        ASSERT_EQUALS(*(it),i++);
    }
    it=list.begin();
    it++;
    ASSERT_EQUALS(*(it),2);
    list.insert(5,it);
    it=list.begin();
    it++;
    ASSERT_EQUALS(*(it),5);
}

static void testGetSize(){
    List<int> list;
    ASSERT_EQUALS(list.getSize(),0);
    for(int i=0;i<100;i++){
        list.insert(i);
        ASSERT_EQUALS(list.getSize(),i+1);
    }
}

static void testListRemove() {
    List<int> list;
    List<int> temp;
    temp.insert(1);
    ASSERT_THROWS(ElementNotFound, list.remove(list.begin()));
    list.insert(1);
    ASSERT_THROWS(ElementNotFound, list.remove(temp.begin()));
    list.remove(list.begin());
    ASSERT_THROWS(ElementNotFound, list.remove(list.begin()));
    ASSERT_EQUALS(list.getSize(), 0);
    for (int i = 1; i < 3; i++) {
        list.insert(i);
    }
    list.remove(++list.begin());
    ASSERT_EQUALS(list.getSize(), 1);
    list.remove(list.begin());
    ASSERT_EQUALS(list.getSize(), 0);
    for (int i = 1; i < 4; i++) {
        list.insert(i);
    }
    list.remove(++list.begin());
    ASSERT_EQUALS(*(list.begin()++), 1);
    ASSERT_EQUALS(list.getSize(), 2);
    list.remove(list.begin());
    list.remove(list.begin());
    ASSERT_EQUALS(list.getSize(), 0);
    ASSERT_THROWS(ElementNotFound, list.remove(list.begin()));
    for (int i = 0; i < 100; i++) {
        list.insert(i);
    }
    for (int i = 0; i < 100; i++) {
        list.remove(list.begin());
    }
    ASSERT_EQUALS(list.getSize(), 0);
    for (int i = 0; i < 100; i++) {
        list.insert(i);
    }
    for (int i = 0; i < 100; i++) {
        list.remove(list.begin());
    }
    ASSERT_EQUALS(list.getSize(), 0);
}

static void testListfind(){
    List<int> list;
    List<int>::Iterator it=list.find(EqualTo(3));
    ASSERT_EQUALS(list.end(),it);
    for (int i = 0; i < 100; i++) {
        list.insert(i);
    }
    it=list.find(EqualTo(100));
    ASSERT_EQUALS(list.end(),it);
    it=list.find(EqualTo(-1));
    ASSERT_EQUALS(list.end(),it);
    it=list.find(EqualTo(1));
    ASSERT_EQUALS(++list.begin(),it);
    list.insert(99);
    list.insert(0,list.begin());
    it=list.find(EqualTo(0));
    ASSERT_EQUALS(list.begin(),it);
    ASSERT_NOT_EQUAL(++list.begin(),it);
    it=list.find(EqualTo(99));
    List<int>::Iterator it2=list.begin();
    for (int i = 0; i < 101; i++) {
        it2++;
    }
    ASSERT_NOT_EQUAL(it2,it);
    ASSERT_EQUALS(--it2,it);
}

static void testListSort() {
    List<int> list;
    for (int i = 99; i >=0; i--) {
        list.insert(i);
    }
    list.sort(compare);
    int i=0;
    for(List<int>::Iterator it=list.begin();it!=list.end();it++){
        ASSERT_EQUALS(*(it),i++);
    }

}

static void testListCopyConstructor(){
    List<int> list1;
    List<int> list2(list1);
    ASSERT_NOT_EQUAL(list1.begin(),list2.begin());
    ASSERT_NOT_EQUAL(list1.end(),list2.end());
    ASSERT_EQUALS(list2.getSize(),0);
    for (int i = 0; i < 100; i++) {
        list1.insert(i);
    }
    List<int> list3(list1);
    ASSERT_EQUALS(list3.getSize(),100);
    ASSERT_EQUALS(list1.getSize(),list3.getSize());
    List<int>::Iterator it1=list1.begin();
    for (List<int>::Iterator it3=list3.begin(); it3!=list3.end(); it3++) {
        ASSERT_EQUALS(*it1,*it3);
        ASSERT_NOT_EQUAL(it1,it3);
        it1++;
    }
}

static void testListAssignment(){
    List<int> list1;
    for (int i = 0; i < 100; i++) {
        list1.insert(i);
    }
    List<int> list2;
    for (int i = 99; i >=0; i--) {
        list2.insert(i);
    }
    ASSERT_EQUALS(list2.getSize(),100);
    ASSERT_EQUALS(list1.getSize(),list2.getSize());
    list1=list1;
    list2=list1;
    List<int>::Iterator it1=list1.begin();
    for (List<int>::Iterator it2=list2.begin(); it2!=list2.end(); it2++) {
        ASSERT_EQUALS(*it1,*it2);
        ASSERT_NOT_EQUAL(it1,it2);
        it1++;
    }
}

static void testListOperatorEqual(){
    List<int> list1;
    for (int i = 0; i < 5; i++) {
        list1.insert(i);
    }
    List<int> list2;
    for (int i = 5; i >0; i--) {
        list2.insert(i);
    }
    ASSERT_EQUALS(list1.getSize(),list2.getSize());
    ASSERT_FALSE(list1==list2);
    list2=list1;
    ASSERT_EQUALS(list1,list2);
    ASSERT_EQUALS(list2,list1);
    ASSERT_TRUE(list1==list2);
    ASSERT_TRUE(list2==list1);
}

static void testListOperatorNOTEqual(){
    List<int> list1;
    for (int i = 0; i < 5; i++) {
        list1.insert(i);
    }
    List<int> list2;
    for (int i = 5; i >0; i--) {
        list2.insert(i);
    }
    ASSERT_EQUALS(list1.getSize(),list2.getSize());
    ASSERT_NOT_EQUAL(list1,list2);
    ASSERT_NOT_EQUAL(list2,list1);
    ASSERT_TRUE(list1!=list2);
    ASSERT_TRUE(list2!=list1);
    list2=list1;
    ASSERT_FALSE(list1!=list2);
}



int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testListBegin);
    RUN_TEST(testListEnd);
    RUN_TEST(testIntInsert);
    RUN_TEST(testIteratorOperatorValue);
    RUN_TEST(testIteratorOperatorsEqual);
    RUN_TEST(testIteratorOperatorsNOTEqual);
    RUN_TEST(testIteratorOperatorsAdvance);
    RUN_TEST(testIteratorOperatorsDecrease);
    RUN_TEST(testIntInsert2);
    RUN_TEST(testGetSize);
    RUN_TEST(testListRemove);
    RUN_TEST(testListfind);
    RUN_TEST(testListSort);
    RUN_TEST(testListCopyConstructor);
    RUN_TEST(testListAssignment);
    RUN_TEST(testListOperatorEqual);
    RUN_TEST(testListOperatorNOTEqual);
    return 0;
}
