#include <iostream>
#include <string.h>
#include <math.h>
//#include "function.h"
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST(); // TODO
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    // TODO
    virtual bool search(const int &) const override;
    // TODO
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};

Array_BST::Array_BST() : BST(){ // constructor
    for(int i = 0; i < 1025; i++)
        array[i] = 0;
}

void Array_BST::insert(const int& data){
    // keep array[0] empty

    int count = 1, index = 1;
    while(array[index] != 0){
        if(data < array[index])
            index *= 2;
        else if(data > array[index])
            index = index*2 + 1;
        else if(data == array[index])
            return;
        count++;
    }
    array[index] = data;
    if(count > Height)
        Height = count;
}

bool Array_BST::search(const int& data) const{
    int index = 1;
    while(index < 1025){
        if(data == array[index])
            return true;
        else if(data < array[index])
            index *= 2;
        else if(data > array[index])
            index = index*2 + 1;
    }
    return false;
}

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    // TODO
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    // TODO
    virtual bool search(const int &) const override;
    // TODO
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    // TODO
    void deleteTree(ListNode *root);
    // TODO
    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};

List_BST::List_BST() : BST(), root(NULL){ 
    // constructor
}

void List_BST::insert(const int& data){
    int count = 1;
    ListNode *new_node = createLeaf(data);
    if(Height == 0) root = new_node;
    else{
        ListNode *tmp = root;
        while(tmp != NULL){
            if(data < tmp->key){
                if(tmp->left == NULL){
                    tmp->left = new_node;
                    count++;
                    break;
                }
                tmp = tmp->left;
            }
            else if(data > tmp->key){
                if(tmp->right == NULL){
                    tmp->right = new_node;
                    count++;
                    break;
                }
                tmp = tmp->right; 
            }
            else if(data == tmp->key)
                return;
            count++;
        }
    }
    if(count > Height)
        Height = count;
}

bool List_BST::search(const int& data) const{
    ListNode *tmp = root;
    while(tmp != NULL){
        if(data == tmp->key)
            return true;
        else if(data < tmp->key)
            tmp = tmp->left;
        else if(data > tmp->key){
            tmp = tmp->right;
        }
    }
    return false;
}

ListNode* List_BST::createLeaf(int key) const{
    ListNode *new_node = new ListNode(key);
    return new_node;
}

void List_BST::deleteTree(ListNode *root){
    if(root == NULL)    return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}
int main(){
    Array_BST A_bst;
    List_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
