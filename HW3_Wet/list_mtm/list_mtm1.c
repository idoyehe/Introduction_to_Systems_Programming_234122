#include <stdlib.h>
#include <assert.h>
#include "list_mtm1.h"

#define EMPTY -1

/* Generic Node Container
* contains two arguments on is pointer to ListElement and one is pointer to the
* next Node in the List*/
typedef struct node* Node;

struct node{
    ListElement element;
    Node next;
};

struct list_t {
    Node first;
    CopyListElement copyFunc;
    FreeListElement freeFunc;
    Node current_element;
};

List listCreate(CopyListElement copyElement, FreeListElement freeElement){
    if(!copyElement||!freeElement){
        return NULL;
    }
    List new_list=(List)malloc(sizeof(*new_list));
    if(!new_list){
        return NULL;
    }
    new_list->first=NULL;// default empty list
    new_list->copyFunc=copyElement;
    new_list->freeFunc=freeElement;
    new_list->current_element=NULL;
    return new_list;
}

int listGetSize(List list){
    if(!list){
        return EMPTY;
    }
    int node_counter=0;
    Node node_ptr=list->first;
    while(node_ptr){
        node_counter++;
        node_ptr=node_ptr->next;
    }
    return node_counter;
}

ListElement listGetFirst(List list) {
    if(!list||!(list->first)){
        return NULL;
    }
    list->current_element = list->first;
    return list->first->element;
}

ListElement listGetCurrent(List list){
    if (!list || !(list->current_element)) {
        return NULL;
    }
    return list->current_element->element;
}

ListElement listGetNext(List list) {
    if (!list || !(list->current_element)) {
        return NULL;
    }
    list->current_element = list->current_element->next;
    if (!(list->current_element)) {//when reaches the end of the list
        return NULL;
    }
    return list->current_element->element;
}

/**
* Find and return the Node before the iterator
*
* @param list The list that has valid iterator and it hasn't point the first
*        Node
* @return
* The Node before current element in the list
*/
static Node beforeCurrent(List list){
    assert(list!=NULL);
    assert(list->current_element!=NULL);
    assert(list->current_element!=list->first);
    Node node_ptr=list->first;
    while(node_ptr->next!=list->current_element)
        node_ptr=node_ptr->next;
    return node_ptr;
}

/*
* create new Node with given ListElement and set it's next to be NULL
*
* @params:
* element to insert. A copy of the element will be inserted using by supplied
*                   copying function which is stored in the list
* @param:
*           copyFunc the function to copy given element
* @return
* NULL if an allocation failed (Meaning the allocation new Node failed or
*                                   function for copying an element failed)
* pointer to new Node if the Node created successfully
*/
static Node createNode(ListElement element,CopyListElement copyFunc){
    assert(copyFunc!=NULL);
    Node new_Node = (Node) malloc(sizeof(*new_Node));
    if (!new_Node) {
        return NULL;
    }
    new_Node->element = copyFunc(element);
    if (!(new_Node->element)) {
        free(new_Node);
        return NULL;
    }
    new_Node->next=NULL;
    return new_Node;
}

ListResult listInsertFirst(List list, ListElement element){
    if (!list||!element) {
        return LIST_NULL_ARGUMENT;
    }
    Node new_Node = createNode(element,list->copyFunc);
    if (!new_Node) {
        return LIST_OUT_OF_MEMORY;
    }
    new_Node->next=list->first;
    list->first=new_Node;
    return LIST_SUCCESS;
}

/**
* Find and return the last Node in the list
*
* @param
* list The list which is NOT empty
* @return
* The last Node in the list
*/
static Node getLastNode(List list){
    assert(list!=NULL);
    assert(list->first!=NULL);
    Node node_ptr=list->first;
    while(node_ptr->next){
        node_ptr=node_ptr->next;
    }
    return node_ptr;
}

ListResult listInsertLast(List list, ListElement element){
    if (!list||!element) {
        return LIST_NULL_ARGUMENT;
    }
    if(!(list->first)){//case empty list
        return listInsertFirst(list,element);
    }
    Node new_Node = createNode(element,list->copyFunc);
    if (!new_Node) {
        return LIST_OUT_OF_MEMORY;
    }
    Node last_Node=getLastNode(list);
    last_Node->next=new_Node;
    new_Node->next=NULL;
    return LIST_SUCCESS;
}

ListResult listInsertBeforeCurrent(List list, ListElement element) {
    if (!list||!element) {
        return LIST_NULL_ARGUMENT;
    }
    if (!(list->current_element)) {
        return LIST_INVALID_CURRENT;
    }
    Node new_Node = createNode(element,list->copyFunc);
    if (!new_Node) {
        return LIST_OUT_OF_MEMORY;
    }
    if (list->current_element == list->first) {
        new_Node->next = list->first;
        list->first = new_Node;
        return LIST_SUCCESS;
    }
    Node node_ptr=beforeCurrent(list);
    new_Node->next=list->current_element;
    node_ptr->next=new_Node;
    return LIST_SUCCESS;
}

ListResult listInsertAfterCurrent(List list, ListElement element){
    if (!list||!element) {
        return LIST_NULL_ARGUMENT;
    }
    if (!(list->current_element)) {
        return LIST_INVALID_CURRENT;
    }
    Node new_Node = createNode(element,list->copyFunc);
    if (!new_Node) {
        return LIST_OUT_OF_MEMORY;
    }
    new_Node->next=list->current_element->next;
    list->current_element->next=new_Node;
    return LIST_SUCCESS;
}

/**
* Free allocated memory of Node
*
* @param Node to destroyed
* @param freeElement function to free the allocated memory of ListElement
* @return
* void function
*/
static inline void nodeDestroy(Node node,FreeListElement freeElement){
    assert(node!=NULL);
    freeElement(node->element);
    free(node);
}

ListResult listRemoveCurrent(List list){
    if(!list){
        return LIST_NULL_ARGUMENT;
    }
    if(!(list->current_element)){
        return LIST_INVALID_CURRENT;
    }
    if(list->first==list->current_element){//case removing first element
        Node to_delete=list->first;
        list->first=list->first->next;
        nodeDestroy(to_delete,list->freeFunc);
        list->current_element=NULL;
        return LIST_SUCCESS;
    }
    //case removing middle element
    Node node_ptr=beforeCurrent(list);
    node_ptr->next=list->current_element->next;
    Node to_delete=list->current_element;
    list->current_element=NULL;
    nodeDestroy(to_delete,list->freeFunc);
    return LIST_SUCCESS;
}

ListResult listClear(List list) {
    if (!list) {
        return LIST_NULL_ARGUMENT;
    }
    list->current_element=list->first;
    while(listRemoveCurrent(list)!=LIST_INVALID_CURRENT){
        list->current_element=list->first;
    }
    assert(list->current_element==NULL);
    assert(list->first==NULL);
    return LIST_SUCCESS;
}

void listDestroy(List list){
    listClear(list);
    free(list);
}

List listCopy(List list){
    if(!list){
        return NULL;
    }
    List copy_List=listCreate(list->copyFunc,list->freeFunc);
    if(!copy_List) {
        return NULL;
    }
    Node node_ptr=list->first;
    while(node_ptr){
        if(listInsertLast(copy_List,node_ptr->element)==LIST_OUT_OF_MEMORY){
            listDestroy(copy_List);//case memory allocation fails
            return NULL;
        }
        assert(copy_List->first!=NULL);
        if(list->current_element==node_ptr){
            //transfer location of iterator to copy
            copy_List->current_element=getLastNode(copy_List);
        }
        node_ptr=node_ptr->next;
    }
    return copy_List;
}

List listFilter(List list, FilterListElement filterElement, ListFilterKey key){
    if(!list||!filterElement){
        return NULL;
    }
    assert(key!=NULL);
    List filtered_List=listCreate(list->copyFunc,list->freeFunc);
    if(!filtered_List) {
        return NULL;
    }
    Node node_ptr=list->first;
    while(node_ptr){
        if(filterElement(node_ptr->element,key)){
            if (listInsertLast(filtered_List, node_ptr->element) ==
                LIST_OUT_OF_MEMORY) {
                listDestroy(filtered_List);
                return NULL;
            }
        }
        node_ptr=node_ptr->next;
    }
    filtered_List->current_element=filtered_List->first;
    return filtered_List;
}
/**
* Swapping between two ListElements
*
* @param e1 pointer to first element to swap
* @param e2 pointer to second element to swap
* @return
* void function
*/
static inline void swapListElement(ListElement* e1,ListElement* e2){
    ListElement temp=*e1;
    *e1=*e2;
    *e2=temp;
}

/*sorting using bubble sort*/
ListResult listSort(List list, CompareListElements compareElement){
    if(!list||!compareElement){
        return LIST_NULL_ARGUMENT;
    }
    if(!(list->first)){
        return LIST_SUCCESS;
    }
    bool swapped = true;
    while (swapped){
        Node node_ptr = list->first;
        swapped = false;
        while ((node_ptr->next)) {
            if (compareElement(node_ptr->element, node_ptr->next->element)>0) {
                swapListElement(&(node_ptr->element),
                                &(node_ptr->next->element));
                swapped = true;
            }
            node_ptr = node_ptr->next;
        }
    }
    return LIST_SUCCESS;
}