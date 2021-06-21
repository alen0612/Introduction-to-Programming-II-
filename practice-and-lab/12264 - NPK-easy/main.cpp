#include <iostream>
#include <string>

#define america 0
#define africa 1
#define japan 2

using namespace std;

class List;

class Node{
public:
    int data;
	int country;
	Node* next;
	Node* prev;

	Node();
	Node(int data, int country);

	friend class List;
};

class List{
public:
    Node* head;
    Node* tail;
    Node* am;
    Node* af;
    Node* jp;

	List();
	void enqueue(int x);
	void dequeue();
	void printList();
};

Node::Node(){
}

Node::Node(int d, int c){
    data = d;
    country = c;

    next = NULL;
    prev = NULL;
}

List::List(){
    head = new Node(-1, -1);
    tail = new Node(-1, -1);

    head->next = tail;
    tail->prev = head;

    am = af = jp = head;
}

void List::enqueue(int x){
	Node* newNode = new Node(x, x % 3);

    if(head->next == tail){ // empty list
    	//cout << "empty list" << endl;
        head->next = newNode;
        tail->prev = newNode;

        newNode->next = tail;
        newNode->prev = head;

        if(newNode->country == america)
        	am = newNode;
        else if (newNode->country == africa)
        	af = newNode;
        else
        	jp = newNode;

        return;
    }

	if(newNode->country == america){
		if(am == head){
			newNode->next = tail;
			newNode->prev = tail->prev;
			tail->prev->next = newNode;
			tail->prev = newNode;
		}
		else{
			newNode->next = am->next;
			newNode->prev = am;
			am->next->prev = newNode;
			am->next = newNode;
		}

		am = newNode;
	}
	else if (newNode->country == africa){
		if(af == head){
			newNode->next = tail;
			newNode->prev = tail->prev;
			tail->prev->next = newNode;
			tail->prev = newNode;
		}
		else{
			newNode->next = af->next;
			newNode->prev = af;
			af->next->prev = newNode;
			af->next = newNode;
		}

		af = newNode;
	}
	else{
		if(jp == head){
			newNode->next = tail;
			newNode->prev = tail->prev;
			tail->prev->next = newNode;
			tail->prev = newNode;
		}
		else{
			newNode->next = jp->next;
			newNode->prev = jp;
			jp->next->prev = newNode;
			jp->next = newNode;
		}

		jp = newNode;
	}
}


void List::dequeue(){
	if(head->next == tail){
		cout << endl;
		return;
	}

	Node* tmp = head->next;
	cout << tmp->data << endl;

	if(tmp->country == america){
		if(am == tmp)
			am = head;

		head->next = tmp->next;
		tmp->next->prev = head;		
	}
	else if (tmp->country == africa){
		if(af == tmp)
			af = head;

		head->next = tmp->next;
		tmp->next->prev = head;
	}
	else{
		if(jp == tmp)
			jp = head;

		head->next = tmp->next;
		tmp->next->prev = head;
	}

	delete tmp;
}

void List::printList(){
	if(head->next == tail){
		cout << endl;
		return;
	}

	Node* tmp = head->next;
	while(tmp != tail){
		cout << tmp->data << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

int main(){
	int n = 0;
	int x = 0;
	cin >> n;

    List* Listhead = new List();
    string cmd;

	while(n-- > 0){
		cin >> cmd;
		if(cmd[0] == 'E'){
			cin >> x;
			Listhead->enqueue(x);
			//Listhead->printList();
		}
		else
			Listhead->dequeue();
	}

	return 0;
}
