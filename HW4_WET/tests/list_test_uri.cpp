#include <functional>
#include "../list.h"
#include "../mtmtest.h"
#include "../Exceptions.h"
#include <cstdio>
#include <cstring>

using std::string;
using namespace mtm::ListExceptions;

/**
 * Function object for finding a target integer
 */
class EqualTo {
private:
  int target;
public:
  EqualTo(int i) : target(i) {}
  bool operator()(const int& i) const {
    return i == target;
  }
};

static void constructorTest(){
	List<int> int_list_1;
	List<int> int_list_2();
	List<string> string_list;
	List<float> float_list;
	List<char> char_list;
}

static void getSizeTest(){
	List<string> list;
	ASSERT_EQUALS(list.getSize(), 0);

	//check that size increases
	list.insert("A");
	ASSERT_EQUALS(list.getSize(), 1);
	list.insert("B");
	ASSERT_EQUALS(list.getSize(), 2);
	list.insert("C");
	ASSERT_EQUALS(list.getSize(), 3);

	//check that size decreases
	List<string>::Iterator iterator = list.begin();
	list.remove(iterator);
	ASSERT_EQUALS(list.getSize(), 2);
}

static void insertLastTest(){
	List<string> list;
	list.insert("A");
	ASSERT_EQUALS(list.getSize(), 1);
	list.insert("B");
	ASSERT_EQUALS(list.getSize(), 2);
	list.insert("C");
	ASSERT_EQUALS(list.getSize(), 3);

	//weird insert values
	list.insert("");
	list.insert("!@#$%");
	ASSERT_EQUALS(list.getSize(), 5);

	//Now we check that all vlues were inserted in a correct order
	List<string>::Iterator iterator = list.begin();
	ASSERT_EQUALS(*iterator, "A");
	iterator++;
	ASSERT_EQUALS(*iterator, "B");
	iterator++;
	ASSERT_EQUALS(*iterator, "C");
	iterator++;
	ASSERT_EQUALS(*iterator, "");
	iterator++;
	ASSERT_EQUALS(*iterator, "!@#$%");
}

static void insertBeforeTest(){
	List<string> list;
	List<string>::Iterator iterator = list.begin();
	list.insert("C", iterator);
	ASSERT_EQUALS(list.getSize(), 1);
	iterator = list.begin();
	ASSERT_EQUALS(*iterator,"C");

	//Now we insert A before C
	list.insert("A", iterator);
	ASSERT_EQUALS(list.getSize(), 2);
	iterator = list.begin();
	ASSERT_EQUALS(*iterator,"A");
	iterator++;
	ASSERT_EQUALS(*iterator,"C");

	list.insert("B", iterator);
	ASSERT_EQUALS(list.getSize(), 3);
	iterator = list.begin();
	ASSERT_EQUALS(*iterator,"A");
	iterator++;
	ASSERT_EQUALS(*iterator,"B");
	iterator++;
	ASSERT_EQUALS(*iterator,"C");

	iterator = list.end();
	list.insert("D", iterator);
	ASSERT_EQUALS(list.getSize(), 4);
	iterator = list.begin();
	ASSERT_EQUALS(*iterator,"A");
	iterator++;
	ASSERT_EQUALS(*iterator,"B");
	iterator++;
	ASSERT_EQUALS(*iterator,"C");
	iterator++;
	ASSERT_EQUALS(*iterator,"D");
}

static void constructorCopyTest(){
	//copying empty lists
	List<string> original_list;
	List<string> copy_list(original_list);
	ASSERT_EQUALS(copy_list, original_list);

	//Copy meaningful list
	original_list.insert("A");
	original_list.insert("B");
	original_list.insert("C");
	List<string> second_copy_list(original_list);

	ASSERT_EQUALS(second_copy_list.getSize(), 3);
	List<string>::Iterator iterator = second_copy_list.begin();
	ASSERT_EQUALS(*iterator, "A");
	iterator++;
	ASSERT_EQUALS(*iterator, "B");
	iterator++;
	ASSERT_EQUALS(*iterator, "C");
}

static void assignmentOperatorTest(){
	List<string> original_list;
	original_list.insert("A");
	original_list.insert("B");
	original_list.insert("C");

	List<string> assign_here;
	assign_here.insert("trash");
	assign_here.insert("spam");
	assign_here.insert("garbage");
	assign_here.insert("none of this matters");

	assign_here = original_list;

	ASSERT_EQUALS(assign_here.getSize(),3);
	List<string>::Iterator iterator = assign_here.begin();
	ASSERT_EQUALS(*iterator, "A");
	iterator++;
	ASSERT_EQUALS(*iterator, "B");
	iterator++;
	ASSERT_EQUALS(*iterator, "C");
}

static void equalOperatorTest(){
	List<string> list_a;
	List<string> list_b;
	ASSERT_EQUALS(list_a, list_a);
	ASSERT_EQUALS(list_b, list_b);
	ASSERT_EQUALS(list_b, list_a);
	ASSERT_EQUALS(list_a, list_b);
	list_a.insert("A");
	ASSERT_NOT_EQUAL(list_a, list_b);
	ASSERT_NOT_EQUAL(list_b, list_a);
	list_b.insert("B");
	ASSERT_NOT_EQUAL(list_a, list_b);
	ASSERT_NOT_EQUAL(list_b, list_a);
	List<string>::Iterator removes_b = list_b.begin();
	list_b.remove(removes_b);
	list_b.insert("A");
	ASSERT_EQUALS(list_a, list_a);
	ASSERT_EQUALS(list_b, list_b);
	ASSERT_EQUALS(list_b, list_a);
	ASSERT_EQUALS(list_a, list_b);
}

static void removeTest(){
	List<string> first_list;
	List<string> second_list;
	List<string>::Iterator first_list_iterator = first_list.begin();
	ASSERT_THROWS(ElementNotFound,first_list.remove(first_list_iterator));
	first_list.insert("A");
	first_list.insert("B");
	first_list.insert("X");
	first_list.insert("C");
	//first list: ->A->B->X->D

	//Check if mixing iterator works
	second_list.insert("A");
	List<string>::Iterator second_list_iterator = second_list.begin();
	ASSERT_THROWS(ElementNotFound,first_list.remove(second_list_iterator));
	ASSERT_THROWS(ElementNotFound,second_list.remove(first_list_iterator));

	//Remove an element in the middle of the list:
	first_list_iterator = first_list.begin();
	first_list_iterator++;
	first_list_iterator++;//Now points at X
	ASSERT_NO_THROW(first_list.remove(first_list_iterator));
	ASSERT_EQUALS(first_list.getSize(),3);
	first_list_iterator = first_list.begin();
	ASSERT_EQUALS(*first_list_iterator,"A");
	first_list_iterator++;
	ASSERT_EQUALS(*first_list_iterator,"B");
	first_list_iterator++;
	ASSERT_EQUALS(*first_list_iterator,"C");

	//Remove an element at the end of the list:
	ASSERT_NO_THROW(first_list.remove(first_list_iterator));
	ASSERT_EQUALS(first_list.getSize(),2);
	first_list_iterator = first_list.begin();
	ASSERT_EQUALS(*first_list_iterator,"A");
	first_list_iterator++;
	ASSERT_EQUALS(*first_list_iterator,"B");

	//Remove an element from the beginning of the list
	first_list_iterator = first_list.begin();
	ASSERT_NO_THROW(first_list.remove(first_list_iterator));
	ASSERT_EQUALS(first_list.getSize(),1);
	first_list_iterator = first_list.begin();
	ASSERT_EQUALS(*first_list_iterator,"B");

	//Remove the only element in list (this element is both first and last)
	first_list_iterator = first_list.begin();
	ASSERT_NO_THROW(first_list.remove(first_list_iterator));
	ASSERT_EQUALS(first_list.getSize(),0);
}

static void findTest(){
	List<int> list;
	list.insert(1);
	list.insert(2);
	list.insert(3);
	list.insert(4);
	list.insert(5);

	//Should find all numbers below. Includes first element, last element and
	//an element in the middle
	List<int>::Iterator iterator = list.find(EqualTo(1));
	ASSERT_EQUALS(*iterator,1);
	iterator = list.find(EqualTo(2));
	ASSERT_EQUALS(*iterator,2);
	iterator = list.find(EqualTo(5));
	ASSERT_EQUALS(*iterator,5);

	//Now we try to remove a number not in the list
	iterator = list.find(EqualTo(0));
	ASSERT_THROWS(ElementNotFound,*iterator);
	iterator = list.find(EqualTo(6));
	ASSERT_THROWS(ElementNotFound,*iterator);

	//Now we will see it returns the first number in the list that it finds
	list.insert(2);
	iterator = list.find(EqualTo(2));
	iterator--;
	ASSERT_EQUALS(*iterator, 1);
}

static void sortTest(){
	List<int> list;
	list.sort(std::less<int>());//does nothing
	list.insert(5);
	list.sort(std::less<int>());//does nothing
	list.insert(2);
	list.insert(1);
	list.insert(2);
	list.insert(4);
	list.insert(3);
	list.sort(std::less<int>());//We will check if it is sorted
/*
	List<int>::Iterator iterator = list.begin();
	ASSERT_EQUALS(*iterator, 1);
	iterator++;
	ASSERT_EQUALS(*iterator, 2);
	iterator++;
	ASSERT_EQUALS(*iterator, 2);
	iterator++;
	ASSERT_EQUALS(*iterator, 3);
	iterator++;
	ASSERT_EQUALS(*iterator, 4);
	iterator++;
	ASSERT_EQUALS(*iterator, 5);

	//one more sort
	list.insert(0);//inserts at the end
	list.sort(std::less<int>());
	iterator = list.begin();
	ASSERT_EQUALS(*iterator,0);*/
}

static void testIteratorDereferencing(){
	List<string> list;
	List<string>::Iterator iterator = list.begin();
	ASSERT_THROWS(ElementNotFound, *iterator);
	list.insert("A");
	list.insert("B");
	list.insert("C");
	iterator = list.begin();
	ASSERT_EQUALS(*iterator, "A");
	iterator++;
	ASSERT_EQUALS(*iterator, "B");
	iterator++;
	ASSERT_EQUALS(*iterator, "C");
	iterator++;
	ASSERT_THROWS(ElementNotFound, *iterator);

	iterator = list.end();
	ASSERT_THROWS(ElementNotFound, *iterator);
}

static void testIteratorIncreaseByOne(){
	List<string> list;
	list.insert("A");
	list.insert("B");
	list.insert("C");
	List<string>::Iterator iterator = list.begin();
	ASSERT_EQUALS(*(iterator++), "A");
	ASSERT_EQUALS(*iterator, "B");
	ASSERT_EQUALS(*(++iterator), "C");
	iterator++;
	ASSERT_THROWS(ElementNotFound, *iterator);

	iterator = list.begin();
	ASSERT_EQUALS(*(++(iterator++)), "B");
	ASSERT_EQUALS(*iterator, "B");

	iterator = list.begin();
	ASSERT_EQUALS(*((++iterator)++), "B");
	ASSERT_EQUALS(*iterator, "C");

	List<int> int_list;
	int_list.insert(1);
	int_list.insert(2);
	int_list.insert(3);
	int_list.insert(4);
	int_list.insert(5);
	List<int>::Iterator int_iterator = ++(int_list.find(EqualTo(4)));
	ASSERT_EQUALS(*int_iterator, 5);
	++int_iterator;
	ASSERT_THROWS(ElementNotFound,*int_iterator);
}

static void testIteratorDecreaseByOne(){
	List<string> list;
	list.insert("A");
	list.insert("B");
	list.insert("C");
	List<string>::Iterator iterator = list.begin();
	iterator++;
	iterator++;
	ASSERT_EQUALS(*(iterator--), "C");
	ASSERT_EQUALS(*(iterator), "B");
	ASSERT_EQUALS(*(--iterator), "A");
	iterator++;
	++iterator;
	ASSERT_EQUALS(*((--iterator)--), "B");


	List<int> int_list;
	int_list.insert(1);
	int_list.insert(2);
	int_list.insert(3);
	List<int>::Iterator int_iterator = --(int_list.find(EqualTo(3)));
	ASSERT_EQUALS(*int_iterator, 2);
}

static void testIteratorEquals(){
	List<string> list;
	list.insert("A");
	list.insert("B");
	list.insert("C");
	List<string>::Iterator iterator_1 = list.begin();
	List<string>::Iterator iterator_2 = list.begin();
	ASSERT_EQUALS(iterator_1, iterator_2);
	iterator_1++;
	ASSERT_NOT_EQUAL(iterator_1, iterator_2);
	ASSERT_NOT_EQUAL(iterator_2, iterator_1);
	iterator_2++;
	ASSERT_EQUALS(iterator_1, iterator_2);

	List<string> copy_list;
	copy_list.insert("A");
	copy_list.insert("B");
	copy_list.insert("C");
	List<string>::Iterator copy_iterator = copy_list.begin();
	copy_iterator++;
	//Now there two nodes to two identical lists, pointing to identical elements
	ASSERT_NOT_EQUAL(copy_iterator,iterator_1);
}

static void testIteratorCopy(){
	List<string> list;
	list.insert("A");
	list.insert("B");
	list.insert("C");
	List<string>::Iterator iterator_1 = list.begin();
	iterator_1++;
	List<string>::Iterator iterator_2(iterator_1);
	ASSERT_EQUALS(*iterator_2, "B");
	iterator_1++;
	iterator_1++;//points to nowhere
	List<string>::Iterator iterator_3(iterator_1);
	ASSERT_THROWS(ElementNotFound, *iterator_3);
}

static void testIteratorAssignment(){
	List<string> list;
	list.insert("A");
	list.insert("B");
	list.insert("C");
	List<string>::Iterator iterator_1 = list.begin();
	iterator_1++;
	List<string>::Iterator iterator_2 = list.begin();
	iterator_2 = iterator_1;
	ASSERT_EQUALS(*iterator_2, "B");
	iterator_1++;
	iterator_1++;//points to nowhere
	iterator_2 = iterator_1;
	ASSERT_THROWS(ElementNotFound, *iterator_2);
}

static void listExample(){
	List<int> list;
	list.insert(1, list.end());
	list.insert(2, list.end());
	list.insert(3, list.end());

	int counter = 1;
  for (List<int>::Iterator it = list.begin(); it != list.end(); ++it) {
    ASSERT_EQUALS(counter++, *it);
  }

	// C++11 syntactic sugar Range-based for-loop
	counter = 1;
  for (int& element : list) {
    ASSERT_EQUALS(counter++, element);
  }

	List<int>::Iterator it = list.begin();
	ASSERT_EQUALS(3, list.getSize());
	list.remove(++it);
	it = list.begin();
	ASSERT_EQUALS(*it, 1);
	list.insert(4, list.begin());
	list.insert(2, list.begin());


//	// std::less<int> is a function object defined in <functional>
//	// it simply calls operator< of the type compared
	list.sort(std::less<int>());
	it = list.begin();
	ASSERT_EQUALS(1, *it);
//
	it = list.find(EqualTo(3));
	ASSERT_EQUALS(3, *it);
//
//
//	// The following insert should add to end of list
	list.insert(5);
//
	const List<int> list2(list);
	ASSERT_TRUE(list == list2);
	ASSERT_FALSE(list != list2);

	//test directions
	it = list.begin();
	it++;
	ASSERT_EQUALS(2, *it);
	++it;
	ASSERT_EQUALS(3, *it);
	it--;
	ASSERT_EQUALS(2, *it);
	it++;
	it++;
	ASSERT_EQUALS(4, *it);
	--it;
	ASSERT_EQUALS(3, *it);


}


int main() {
  RUN_TEST(constructorTest);
  RUN_TEST(getSizeTest);
  RUN_TEST(insertLastTest);
  RUN_TEST(insertBeforeTest);
  RUN_TEST(constructorCopyTest);
  RUN_TEST(assignmentOperatorTest);
  RUN_TEST(equalOperatorTest);
  RUN_TEST(removeTest);
  RUN_TEST(findTest);
  RUN_TEST(sortTest);
  RUN_TEST(testIteratorDereferencing);
  RUN_TEST(testIteratorIncreaseByOne);
  RUN_TEST(testIteratorDecreaseByOne);
  RUN_TEST(testIteratorEquals);
  RUN_TEST(testIteratorCopy);
  RUN_TEST(testIteratorAssignment);

  RUN_TEST(listExample);
  return 0;
}
