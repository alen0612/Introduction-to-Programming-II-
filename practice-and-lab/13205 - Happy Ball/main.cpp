#include <iostream>
//#include "function.h"

using namespace std;

class ContainerBase {
	public:
		/* for the first-type operation */
		virtual int print() = 0;
		/* for the second-type operation */
		virtual void move(int) = 0;
		/* for the third-type operation */
		virtual void remove() = 0;
		int getSize() { return size; }

		virtual ~ContainerBase() {}
	protected:
		int size;	// the number of elements(people) in the container
};

/* array class deriving from ContainerBase */
class Array final : public ContainerBase {
	public:
		Array() {}
		Array(int n, int *arr) {
			size = n;

			mem = new int[size + 1];
			for(int i=1;i<=size;i++)	mem[i] = arr[i];
			cur = 1;
		}

		virtual int print() override { return mem[cur]; }
		/* TODO */
		virtual void move(int) override;
		/* TODO */
		virtual void remove() override;

		~Array() { delete[] mem; }
	private:
		int *mem;	// array for maintaining all the elements(the happy value of all the people)
		int cur;	// record who is carrying the ball
};

/* doubly linked list class deriving from ContainerBase */
class List final : public ContainerBase {
	public:
		List() {}
		List(int n, int *arr) {
			size = n;

			cur = new Node(arr[1]);
			Node *back = cur;
			for(int i=2;i<=n;i++) {
				Node *newNode = new Node(arr[i]);
				back->insertBack(newNode);
				back = newNode;
			}
		}

		virtual int print() override { return cur->getVal(); }
		/* TODO */
		virtual void move(int) override;
		/* TODO */
		virtual void remove() override;

		~List() { for(int i=1;i<=size;i++)	cur = cur->remove(); }
	private:
		/* nested class for the node in linked list */
		class Node {
			public:
				Node() {}
				Node(int newVal) : pre(nullptr), nxt(nullptr), val(newVal) {}
				/* insert a new node after the current node */
				void insertBack(Node *newNode) {
					nxt = newNode;
					newNode->pre = this;
				}
				/* remove the current node and return the next node(or the previous node if the next node doesn't exist) */
				Node* remove() {
					Node *ret = (nxt == nullptr ? pre : nxt);
					if(pre != nullptr)	pre->nxt = nxt;
					if(nxt != nullptr)	nxt->pre = pre;
					delete this;
					return ret;
				}
				Node* getPre() { return pre; }
				Node* getNxt() { return nxt; }
				int getVal() { return val; }
			private:
				Node *pre, *nxt;
				int val;
		} *cur;	// record who is carrying the ball
};

/* a class for operation */
class Operation {
	public:
		int type,d;
};

void Array::move(int n){
	// move
	if(size <= 1)   return;

	cur += n;
	if (cur < 1) cur = 1;
	if (cur > size) cur = size;
}

void Array::remove(){
    if(size == 0)   return;
    else{
        if(cur == size){ // pass to left
            cur--;
            size--;
        }
        else{
            for(int i = cur; i < size; i++)
                mem[i] = mem[i + 1];
            size--;
        }
    }
}

void List::move(int n){
    if(n >= 0)
        while(n-- > 0){
            Node* tmp = cur->getNxt();
            if(tmp != NULL)
                cur = tmp;
            else
                break;
        }
    else
        while(n++ < 0){
            Node* tmp = cur->getPre();
            if(tmp != NULL)
                cur = tmp;
            else
                break;
        }
}

void List::remove(){
    cur = cur->remove();
    size--;
}

/* TODO: create array/linked list based on operations and return it */
ContainerBase* create(int n, int* arr, int q, Operation* op){
	// n : number of total people
	// q : number of operation

	int cnt2 = 0;
	int cnt3 = 0;

	for(int i = 1; i <= q; i++){
		if(op[i].type == 2)
			cnt2++;
		if(op[i].type == 3)
			cnt3++;
	}
	if(cnt2 >= cnt3){
		Array* tmp = new Array(n, arr);
		return tmp;
	}
	else{
		List* tmp = new List(n, arr);
		return tmp;
	}
}

int main() {
	/* I/O optimization */
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;
	while(t--) {
		int n;
		cin >> n;
		int *arr = new int[n + 1];
		for(int i=1;i<=n;i++)	cin >> arr[i];

		int q;
		cin >> q;
		Operation *ops = new Operation[q + 1];
		for(int i=1;i<=q;i++) {
			cin >> ops[i].type;
			if(ops[i].type == 2)	cin >> ops[i].d;
		}

		ContainerBase *solver = create(n, arr, q, ops);
		//cout << "solver create success" << endl;
		for(int i=1;i<=q;i++) {
			if(ops[i].type == 1)
				cout << solver->print() << '\n';
			else if(ops[i].type == 2)
				solver->move(ops[i].d);
			else
				solver->remove();
		}

		delete[] arr;
		delete[] ops;
		delete solver;
	}
	return 0;
}
