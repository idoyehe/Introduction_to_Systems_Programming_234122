#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node_t *Node;
struct node_t {
    int n;
    Node next;
};
typedef void *Element;
typedef bool (*ConditionFunc)(Element);
/*Gets an element and return true if it is follow by the condition if not
 * return false*/

void destroyList(Node head) {
/* free all Nodes of the list*/
    while(head){
        Node to_delete=head;
        head=head->next;
        free(to_delete);
    }
    return;
}

Node createIntNode(Element n) {
/*create new Node with integer n and set next pointer to NULL,
 * return pointer to new node
 * Error results: if malloc fails return NULL */
    Node new=(Node) malloc(sizeof(*new));
    if(new == NULL){
        return NULL;
    }
    new->n=*(int *) n;
    new->next=NULL;
    return new;
}

Node getLast(Node head) {
/*Gets Head of a linked list and return pointer to the last node in the list,
 * Error results: if head is NULL return NULL */
    Node ptr=head;
    while(ptr != NULL && ptr->next != NULL)
        ptr=ptr->next;
    return ptr;//return Null if list is empty
}

Node addNode(Node *head, Element n) {
/*Gets pointer to head of a linked list and pointer to element n,
 * allocating new node for new element using create function and chain it as
 * last node in the list. return pointer to the new node.
 * Error results: if malloc fails return NULL */
    assert(head != NULL);
    assert(n != NULL);
    Node new=createIntNode(n);
    Node last_ptr=getLast(*head);
    if(last_ptr == NULL){//only when gets empty list
        *head=new;
        return new;
    }
    last_ptr->next=new;//if new is NULL make no change
    return new;
}

Node filteredList(Node head, ConditionFunc condition) {
/*Gets pointer to the head of list and condition function.
 * check each node in the list and create new list that each node on it
 * follow by the condition function
 * Error results: if malloc fails return NULL */
    assert(condition != NULL);
    Node new_list=NULL;
    Node iterator=head;
    while(iterator){
        if(condition(&(iterator->n))){
            if(addNode(&new_list, &(iterator->n)) == NULL){
                destroyList(new_list);
                //destroy all allocated nodes
                return NULL;
            }
        }
        iterator=iterator->next;
    }
    return new_list;
}

Node concatLists(Node head1, Node head2, ConditionFunc condition) {
/*Gets 2 head of linked list and build new list the all of it's nodes
* follow by input condition, the nodes from head1 will be before
* nodes from head2.
* Error results: if malloc fails return NULL */
    Node new_list1=filteredList(head1, condition);
    if(new_list1 == NULL){
        return NULL;
    }
    Node new_list2=filteredList(head2, condition);
    if(new_list2 == NULL){
        destroyList(new_list1);
        return NULL;
    }
    Node last1=getLast(new_list1);
    last1->next=new_list2;
    return new_list1;
}

void printIntList(Node head, char *title) {
/*Gets pointer to a list that contains integers and a title to print, first
 * print the title and then print all list values by their order
 * Error results: if head is NULL print nothing*/
    if(head != NULL){
        printf("%s", title);
        Node iterator=head;
        while(iterator){
            printf("%d ", iterator->n);
            iterator=iterator->next;
        }
        printf("\n");
    }
    return;
}

bool isOdd(Element e1) {
/*return true if e1 is odd integer*/
    assert (e1 != NULL);
    return (*(int *) e1) % 2 != 0;
}

bool isPrime(Element e1) {
/*return true if e1 is prime integer*/
    assert (e1 != NULL);
    int n=(*(int *) e1);
    if(n < 2){
        return false;
    }
    int i=2;
    while(i * i <= n){
        if(n % i == 0){
            return false;
        }
        i++;
    }
    return true;
}

int main() {
/*performing the requested example*/
    Node list1=NULL;
    // create first list
    for(int i=1; i <= 3; i++){
        if(addNode(&list1, &i) == NULL){
            destroyList(list1);
            list1=NULL;
            break;
        }
    }
    Node list2=NULL;
    //create second list
    for(int i=4; i <= 7; i++){
        if(addNode(&list2, &i) == NULL){
            destroyList(list2);
            list2=NULL;
            break;
        }
    }
    Node odd_list=concatLists(list1,list2,isOdd);//create odd numbers list
    Node prime_list=concatLists(list1,list2,isPrime);//create prime number list
    destroyList(list2);
    destroyList(list1);
    printIntList(odd_list, "Odd Numbers List: ");
    printIntList(prime_list, "Prime Numbers List: ");
    destroyList(odd_list);
    destroyList(prime_list);
    return 0;
}