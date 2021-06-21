#include<iostream>
#include<string.h>
#include<stdlib.h>
//#include "function.h"
using namespace std;

class ListNode
{
    friend class List_stack; //make List_stack a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL ){} //end ListNode constructor

    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

List_stack::List_stack(){
    this->head = (ListNode*)malloc(sizeof(ListNode));
    this->head->data = 0;
    this->tail = (ListNode*)malloc(sizeof(ListNode));
    this->tail->data = 0;

    this->head->nextPtr = this->tail;
    this->head->prevPtr = NULL;
    this->tail->nextPtr = NULL;
    this->tail->prevPtr = this->head;
}

List_stack::~List_stack(){}

void List_stack::push(const int &a){
    ListNode* tmp = (ListNode*)malloc(sizeof(ListNode));

    tmp->data = a;
    tmp->nextPtr = tail;
    tmp->prevPtr = tail->prevPtr;

    tmp->prevPtr->nextPtr = tmp;
    tmp->nextPtr->prevPtr = tmp;
}

void List_stack::pop(){
    if(head->nextPtr == tail)   return;
    else{
        ListNode* tmp = tail->prevPtr;
        tmp->prevPtr->nextPtr = tmp->nextPtr;
        tmp->nextPtr->prevPtr = tmp->prevPtr;
        free(tmp);
    }
}

void List_stack::print(){
    if(head->nextPtr == tail)    return;
    else{
        ListNode* tmp = tail->prevPtr;
        while(tmp != head->nextPtr){
            cout << tmp->data << " ";
            tmp = tmp->prevPtr;
        }
        cout << head->nextPtr->data;
    }
}

int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}

