#include <iostream>
#include <string.h>
//#include "function.h"

using namespace std;

class ListNode {
    friend class List_queue; //make List_queue a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
        {
        } //end ListNode constructor
    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_queue {
    public:
        List_queue();
        ~List_queue();
        void enqueue(const int &);
        void dequeue();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};

List_queue::List_queue(){
    head = new ListNode(-1);
    tail = head;
}

List_queue::~List_queue(){
    delete head;
}

void List_queue::enqueue(const int &n){
    ListNode* node = new ListNode(n);
    if(head->nextPtr == NULL){
        head->nextPtr = node;
        node->prevPtr = head;
        tail = node;
    }
    else{
        tail->nextPtr = node;
        node->prevPtr = tail;
        tail = node;
    }
}

void List_queue::dequeue(){
    if(head->nextPtr == NULL)  return;
    if(head->nextPtr == tail){
        head->nextPtr = NULL;
        delete tail;
        tail = head;
    }
    else{
        ListNode* tmp = head->nextPtr;
        head->nextPtr = tmp->nextPtr;
        tmp->nextPtr->prevPtr = head;
        delete tmp;
    }
}

void List_queue::print(){
    if(head->nextPtr == NULL)   return;

    ListNode* tmp = head->nextPtr;
    while(tmp != tail){
        cout << tmp->data << " ";
        tmp = tmp->nextPtr;
    }
    cout << tail->data;
}


using namespace std;

int main() {
    List_queue L_queue;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"dequeue")==0){
            L_queue.dequeue();
        }else if(strcmp(command,"enqueue")==0){
            cin >> n;
            L_queue.enqueue(n);
        }else if(strcmp(command, "print") == 0){
            L_queue.print();
            cout << endl;
        }
    }
    return 0;
}
