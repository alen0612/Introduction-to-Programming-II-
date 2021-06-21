#include <iostream>
#include <string>
#include <stdexcept>
//#include "function.h"

using namespace std;

class ListNode {
private:
    int data;
    ListNode *next;
    ListNode *prev;
public:
    ListNode():data(0),next(nullptr), prev(nullptr) {};
    ListNode(int a):data(a),next(nullptr), prev(nullptr) {};

    friend class List;
};

class List {
private:
    ListNode* head;  // head of the doubly linked list
    ListNode* tail;  // tail of the doubly linked list
    ListNode* middle; // middle of the list
    int       cnt;   // total count of the elements in the list
    int       pos;   // the position of middle

    void reset() {
        head = nullptr;
        tail = nullptr;
        middle = nullptr;
        cnt = 0;
        pos = 0;
    }

    void clean() {
        ListNode* temp;
        while(head!=nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    // constructor and destructor
    List() {
        reset();
    }

    ~List() {
        clean();
    }

    void InsertHead(int data);
    int  RemoveHead();
    void InsertTail(int data);
    int  RemoveTail();
    void Swap();
    int  getSize();
    int  getMiddle();

};

void List::InsertHead(int data) {
    ListNode *newHead = new ListNode;
    newHead->data = data;
    newHead->next = head;
    newHead->prev = nullptr;

    if(head != nullptr)
        head->prev = newHead;

    if(cnt == 0) {
        middle = newHead;
        tail = newHead;
        head = newHead;
        cnt++;
        pos++;
        return;
    }
    head = newHead;
    cnt++;
    pos++;

    if(cnt/2 + 1 < pos) {
        pos--;
        middle = middle->prev;
    }
}

int List::RemoveHead() {
    if(head == nullptr)
        throw out_of_range("\n");
    cnt--;
    pos--;

    if(cnt/2 + 1 < pos) {
        pos--;
        middle = middle->prev;
    }

    ListNode *oldHead = head;
    int oldData = oldHead->data;
    head = head->next;

    if(head != nullptr)
        head->prev = nullptr;
    delete oldHead;
    if(cnt == 0)
        reset();

    return oldData;
}

void List::InsertTail(int data) {
    ListNode *newTail = new ListNode;
    newTail->data = data;
    newTail->next = nullptr;
    newTail->prev = tail;
    if(tail != nullptr)
        tail->next = newTail;
    if(cnt == 0) {
        head = newTail;
        middle = newTail;
        tail = newTail;
        cnt++;
        pos++;
        return;
    }
    tail = newTail;

    cnt++;
    if(cnt/2 + 1 > pos) {
        pos++;
        middle = middle->next;
    }
}

int  List::RemoveTail() {
    if(tail == nullptr)
        throw out_of_range("\n");

    cnt--;
    if(cnt/2 + 1 < pos) {
        pos--;
        middle = middle->prev;
    }

    ListNode *oldTail = tail;
    int oldData = oldTail->data;
    tail = tail->prev;
    if(tail != nullptr)
        tail->next = nullptr;
    delete oldTail;
    if(cnt == 0)
        reset();

    return oldData;
}

void List::Swap() {
    if(cnt ==0 || cnt == 1)
        return;
    ListNode* oldHead = head;
    ListNode* oldTail = tail;
    ListNode* oldMiddle = middle;
    head = oldMiddle;
    tail = oldMiddle->prev;

    oldTail->next = oldHead;
    oldHead->prev = oldTail;
    head->prev = nullptr;
    tail->next = nullptr;

    if(cnt%2 == 0)
        pos--;
    middle = oldTail;
    if(cnt/2 + 1 > pos) {
        pos++;
        middle = middle->next;
    }
}

int main() {
    List L;
    string cmd;
    int data, cnt=0, pos = 0;

    while(cin >> cmd) {
        if(cmd=="IH") { // insert an integer to the head
            cin >> data;
            L.InsertHead(data);
        } else if (cmd=="IT") { // insert an integer to the end
            cin >> data;
            L.InsertTail( data);
        } else if (cmd=="RH") {  // print and remove a node from head
            try {
                cout<< L.RemoveHead() <<endl;
            } catch (const out_of_range &e) {
                cout << endl;
            }
        } else if (cmd=="RT") { // print and remove a node from tail
            try {
                cout << L.RemoveTail()<<endl;
            } catch (const out_of_range &e) {
                cout << endl;
            }
        } else if (cmd=="S") {
            L.Swap();
        }
    }
}
