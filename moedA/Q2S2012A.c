#include <stdlib.h>
#include <stdbool.h>

typedef struct node* Node;
struct node{
    int n;
    Node next;
};

typedef struct dlnode* DLNode;
struct dlnode{
    int n;
    DLNode next;
    DLNode previous;
};

typedef bool(*Condition)(int,int);

DLNode filterToDL(Node first, Condition condition,int num){
    Node current=first;
    DLNode export=NULL;
    DLNode ptr=NULL;
    while(current){
        if(condition(current->n,num)){
            DLNode temp=(DLNode)malloc(sizeof(*temp));
            if(temp==NULL){
                //destoryList (temp)
                return NULL;
            }
            if(ptr!=NULL)ptr->next=temp;
            temp->n=current->n;
            temp->previous=ptr;
            temp->next=NULL;
            ptr=temp;
            if(export==NULL) export=ptr;
        }
        current=current->next;
    }
    return export;
}
bool condition(int x,int y){
    return x%y==0;
}

int main(){
    Node n1=(Node)malloc(sizeof(*n1));
    Node n2=(Node)malloc(sizeof(*n2));
    Node n3=(Node)malloc(sizeof(*n3));
    n1->n=2;n1->next=n2;
    n2->n=5;n2->next=n3;
    n3->n=4;n3->next=NULL;
    DLNode first=filterToDL(n1,condition,2);
    DLNode check=first;


}