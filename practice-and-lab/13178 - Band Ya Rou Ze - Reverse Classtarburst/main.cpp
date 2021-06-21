#include <iostream>
#include <string>
//#include "function.h"
using namespace std;

class Node {
	private:
		char instrm;
		Node *neighbors[2];
		/* disconnect the link with a specific node */
		void unLink(Node *delNeighbor) {
			/* you could consider "nullptr" as "NULL" */
			if(neighbors[0] == delNeighbor) neighbors[0] = nullptr;
			if(neighbors[1] == delNeighbor) neighbors[1] = nullptr;
		}
	public:
		Node() {}
		Node(char instrument) : instrm(instrument), neighbors{nullptr, nullptr} {}
		/* connect this node with another node */
		void link(Node *newNeighbor) {
			neighbors[(neighbors[0] == nullptr ? 0 : 1)] = newNeighbor;
			// 0->right
			// 1->left
		}
		void output(Node *prevNode) {
			std::cout << instrm;
			for(int i=0;i<2;i++)
				if(neighbors[i] != nullptr && neighbors[i] != prevNode)
					neighbors[i]->output(this);
		}
		/* TODO: destructor for this class */
		~Node();
};

class List {
	private:
		Node *head, *tail;	// point to the first and the last node of this linked list
	public:
		List() : head(nullptr), tail(nullptr) {}
		/* TODO: using a string to initialize this linked list */
		void init(std::string s);
		/* TODO: make this linked list be a new linked list which is merged from two linked list */
		void merge(List &front, List &back);
		void clear() { head = tail = nullptr; }
		/* TODO: exchange this linked list with another linked list; try to use std::swap! */
		void swap(List &swapList);
		/* TODO: reverse the order of this linked list */
		void reverse();
		void output() {
			if(head != nullptr) head->output(nullptr);
			std::cout << '\n';
		}
		/* TODO: destructor for this class */
		~List();
};

void List::init(string s){
    // 0->right
    // 1-left
    if(s[0] == '\0')    return;
    Node* node = new Node(s[0]);
    head = tail = node;
    Node* array[s.length()];
    array[0] = node;

    if(s.length() == 1) return;
    else{
        for(int i = 1; i < s.length(); i++){
            tail = new Node(s[i]);
            array[i] = tail;
        }
        for(int i = 0; i < s.length(); i++){
            if(array[i] == head)  array[i]->link(array[i+1]);
            else if(array[i] == tail)   array[i]->link(array[i-1]);
            else{
                array[i]->link(array[i+1]);
                array[i]->link(array[i-1]);
            }
        }
    }
}

void List::merge(List &front, List &back){
    if(front.head == nullptr && back.tail == nullptr)   return;

    if(front.head == nullptr){
        if(head != nullptr) return;
        head = back.head;
        tail = back.tail;
    }
    else if(back.tail == nullptr){
        if(tail != nullptr) return;
        head = front.head;
        tail = front.tail;
    }
    else{
        front.tail->link(back.head);
        back.head->link(front.tail);
        head = front.head;
        tail = back.tail;

    }
}

void List::swap(List &swapList){
    std::swap(head, swapList.head);
    std::swap(tail, swapList.tail);
}

void List::reverse(){
    std::swap(head, tail);
}

Node::~Node(){
    //cout << "~NODE" << endl;
    //if(this == nullptr) return;
    if(this->neighbors[0] != nullptr){
        neighbors[0]->unLink(this);
        //this->unLink(neighbors[0]);
        delete neighbors[0];
    }

    if(this->neighbors[1] != nullptr){
        neighbors[1]->unLink(this);
        //this->unLink(neighbors[1]);
        delete neighbors[1];
    }
}

List::~List(){
    //cout << "~list" << endl;
    if(head == nullptr) delete head;
}

int main() {
	/* I/O optimization */
	ios::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		List *row = new List[n + 1];
		for(int i=1;i<=n;i++) {
			int sz;
			cin >> sz;
			if(sz > 0) {
				string s;
				cin >> s;
				row[i].init(s);
			}
		}

		int q;
		cin >> q;
		while(q--) {
			int type, a, b;
			cin >> type >> a;
			if(type != 4)   cin >> b;

			if(type == 1) {
				row[b].merge(row[a], row[b]);
				row[a].clear();

			}
			else if(type == 2) {
				row[b].merge(row[b], row[a]);
				row[a].clear();
			}
			else if(type == 3) {
				row[a].swap(row[b]);
			}
			else {
				row[a].reverse();
			}
		}
		for(int i=1;i<=n;i++)
			row[i].output();

		delete[] row;
	}
	return 0;
}

