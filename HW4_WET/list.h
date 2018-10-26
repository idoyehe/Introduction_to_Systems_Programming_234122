#ifndef HW4_WET_LIST_H
#define HW4_WET_LIST_H

#include "Exceptions.h"
#include <assert.h>
#define START_SIZE 0
using namespace mtm::ListExceptions;

template <class T>
class List {
private:
/************************* begin of Node implementation************************/
    class Node {
    private:
        T data;
        Node*prev;
        Node*next;
        friend class List<T>;
        friend class Iterator;

    public:
        /*
        * constructor copy data to the node and set next and prev to NULL
        */
        Node(const T &data):data(data), prev(NULL), next(NULL) {};

        /*
         * assignment operator set to be default
         */
        Node &operator=(const Node &node) = default;

        /*
         * copy constructor  set to be default
         */
        Node(const Node &node) = default;

        /*
        * destructor set to be default
        */
        ~Node() = default;
/*********************** end of Node implementation****************************/
    };
    Node*first;
    Node*last;
    int size;
    /*
     * clear all the nodes from the list and set size to 0
     */
    void listClear() {
        while(first) {
            Node *to_delete=first;
            first=first->next;
            delete(to_delete);
        }
        size=START_SIZE;
        last=NULL;
    }
public:
    class Iterator;
    /*
    * constructor initializing the fist and last to NULL and size is 0
    */
    explicit List();

    /*
     * destructor for the list
     */
    ~List();
    /*
     * copy constructor
     */
    List(const List<T>& list);
    /*
     * assignment operator
     */
    List<T>& operator=(const List<T>& list);

    /*
     * operator Equal return true if the list holds the same elements in the
     * same order
     */
    bool operator==(const List<T>& list) const;

    /*
    * operator  NOT Equal return true if the list does not holds the same
    * elements in the  same order
    */
    bool operator!=(const List<T>& list) const;

    /*
     * return the number of elements in the list
     */
    int getSize() const;

    /*
     * return Iterator to the head of the list
     */
    Iterator begin() const;
    /*
    * return Iterator to the tail of the list means NULL
    */
    Iterator end() const;

    /*
     * insert new element to the list
     */

    /*
     * adding new element to the list with value data before the current
     * location of the iterator
     * throw ElementNotFound if the iterarot is of other list
     */
    void insert(const T& data,Iterator iterator);
    /*
    * adding new element to the list with value to the end of the list
    */
    void insert(const T& data);

    /*
    * removing an element that iterator holds from the list with value to the
    * end of the list
    */
    void remove(Iterator iterator);
    /*
     * return an iterator to the element in the list that predicate return
     * true for it if finds nothing return iterator to the end
     */
    template <class Perdicate>
    Iterator find(const Perdicate& perdicate) const;
    /*
     * sorting the list using compare function
    */
    template <class Compare>
    void sort(const Compare& compare);
};

/********************begin list implementation*********************************/
template <class T>
List<T>::List():first(NULL),last(NULL),size(START_SIZE){}

template <class T>
List<T>::~List() {
    listClear();
}

template <class T>
int List<T>::getSize() const {
    return size;
}

template <class T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(this,first);
}

template <class T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(this,NULL);
}

template <class T>
bool List<T>::operator==(const List<T> &list) const{
    if(getSize()!=list.getSize()){
        return false;
    }
    Iterator it1=begin();
    for (Iterator it2=list.begin();it2!=list.end();++it2){
        if(*(it1)!=*(it2)){
            return false;
        }
        ++it1;
    }
    return true;
}

template <class T>
bool List<T>::operator!=(const List<T> &list) const{
    return !(*this==list);
}

template <class T>
void List<T>::insert(const T& data,Iterator iterator) {
    if (iterator.list != this) {
        throw ElementNotFound();
    }
    Node*to_add = new Node(data);
    if (!(iterator.ptr)) {//case need to be added last
        to_add->prev = last;
        assert(to_add->next == NULL);
        if(last){//case list is not empty
            last->next=to_add;
        }
        last=to_add;
    } else {
        to_add->prev = iterator.ptr->prev;
        to_add->next=iterator.ptr;
        iterator.ptr->prev=to_add;
        if(to_add->prev){
            to_add->prev->next=to_add;
        }
    }
    if(!(to_add->prev)){
        first=to_add;
    }
    size++;
    iterator.ptr = NULL;
}

template <class T>
void List<T>::insert(const T &data) {
    insert(data,end());
}

template <class T>
void List<T>::remove(Iterator iterator) {
    if(!first||iterator.list!=this){
        throw ElementNotFound();
    }
    Node *to_delete=iterator.ptr;
    if(!to_delete){
        return;
    }
    if(to_delete!=first&&to_delete!=last){//case removing node from middle
        to_delete->next->prev = to_delete->prev;
        to_delete->prev->next = to_delete->next;
    }else {
        if (to_delete == last) {//case removing last node
            last = to_delete->prev;
            if (last) {
                last->next = NULL;
            }
        }
        if (to_delete == first) {//case removing first node
            first = first->next;
            if (first) {
                first->prev = NULL;
            }
        }
    }
    size--;
    assert(size>=START_SIZE);
    delete(to_delete);
    iterator.ptr=NULL;
    return;
}

template <class T>
List<T>::List(const List<T> &list) {
    first = NULL;
    last = NULL;
    size = START_SIZE;
    for (Iterator it = list.begin(); it != list.end(); ++it) {
        insert(*(it));
    }
}

template <class T>
List<T> & List<T>::operator=(const List<T> &list) {
    if(this==&list){
       return *this;
    }
    listClear();
    first = NULL;
    last = NULL;
    size = START_SIZE;
    for (Iterator it = list.begin(); it != list.end(); ++it) {
        insert(*(it));
    }
    return *this;
}

template <class T>
template <class Perdicate>
typename List<T>::Iterator List<T>::find(const Perdicate& perdicate) const {
    for(Iterator it=begin();it!=end();++it){
        if(perdicate(*(it))) {
            return it;
        }
    }
    return end();
}

template <class T>
template <class Compare>
void List<T>::sort(const Compare& compare) {
    if (!(first)) {
        return;
    }
    bool swapped = true;
    while (swapped) {
        Node*ptr = first;
        swapped = false;
        while ((ptr->next)) {
            if (!(ptr->data==ptr->next->data)&&
                    !(compare(ptr->data, ptr->next->data))) {
                T temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = true;
            }
            ptr = ptr->next;
        }
    }
    return;
}

/**********************end list implementation*********************************/



/********************* begin of iterator implementation************************/
template <class T>
class List<T>::Iterator {
private:
    const List<T> *list;
    List<T>::Node *ptr;
    /*
    * constructor for iterator set the node pointer to given and set the
    * pointer to list the given list pointer
    */
Iterator(const List<T> *list, Node *ptr):list(list),ptr(ptr){};
    friend class List<T>;

public:
    /*
    * returning const reference to the data in the node the iterator point on
    */
    const T& operator*() const {
        if (!ptr) {
            throw ElementNotFound();
        }
        return ptr->data;
    }

    /*
    * returning reference to the data in the node the iterator point on
    */
    T& operator*() {
        if (!ptr) {
            throw ElementNotFound();
        }
        return ptr->data;
    }

    /*
    * preforming ++iterator advance the iterator to the next node and return
    */
    Iterator& operator++(){ // prefix ++i
        assert(ptr!=NULL);
        ptr=ptr->next;
        return *this;
    }
    /*
    * return the current iterator then preforming iterator++ advance the
    * iterator to the next node
    */
    Iterator operator++(int) { // postfix i++
        assert(ptr!=NULL);
        Iterator result = *this;
        ++*this;
        return result;
    }

    /*
    * preforming --iterator decrease the iterator to the previous node and
    * return
    */
    Iterator& operator--() {// prefix --i
        assert(ptr!=NULL);
        ptr = ptr->prev;
        return *this;
    }

    /*
    * return the current iterator and then preforming iterator-- decrease the
    * iterator to the previous node
    */
    Iterator operator--(int) { // postfix i--
        assert(ptr!=NULL);
        Iterator result = *this;
        --*this;
        return result;
    }

    /*
    * return true if the iterators are point the same node in the same list
    */
    bool operator==(const Iterator &iterator) const{
        return (list==iterator.list)&&(ptr==iterator.ptr);
    }

    /*
    * return true if the iterators are NOT point the same node in the same list
    */
    bool operator!=(const Iterator &iterator) const {
        return !(*this == iterator);
    }

    /*
    * assignment operator set to be default
    */
    Iterator &operator=(const Iterator &iterator) = default;

    /*
    * destructor set to be default
    */
    ~Iterator() = default;
};
/************************end of iterator implementation************************/
#endif //HW4_WET_LIST_H