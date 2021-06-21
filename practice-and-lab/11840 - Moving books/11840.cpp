#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int data;
    struct _node* next;
} Node;

int n;
Node* table[25];
int position[25];

Node* makeNode(int a){
    //printf("make node : %d\n", a);
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = a;
    head->next = NULL;

    return head;
}

void initialize(){
    //printf("initialize\n");
    for(int i = 0; i < n; i++){
        table[i] = makeNode(100 + i);
        table[i]->next = makeNode(i);
        position[i] = i;
    }
}

void returnBook(Node* book){
    //printf("return book : %d\n", book->data);
    Node* tmp = table[book->data];
    //printf("tmp->data : %d\n", tmp->data);
    if(tmp->next == NULL){
        //printf("there's no book on table %d\n", book->data);
        tmp->next = book;
        book->next = NULL;
    }
    else{
        Node* next = tmp->next;
        tmp->next = book;
        book->next = next;
    }

    position[book->data] = book->data;
}

void resetBook(int a){
    //printf("reset book : %d\n", a);

    //printf("find node %d that all books on it should be returned\n", a);
    Node* tmp = table[position[a]]->next;
    //printf("2\n");
    while(tmp->data != a)   tmp = tmp->next;
    //printf("3\n");


    if(tmp->next == NULL){
        //printf("no books are on book %d so do nothing\n", a);
        return;
    }

    //printf("while loop\n");
    while(tmp->next != NULL){
        Node* next = tmp->next;
        tmp->next = next->next;
        returnBook(next);
    }
}

void updatePos_move(Node* book, int target){
    position[book->data] = target;
}

void updatePos_pile(Node* book, int target){
    Node* tmp = book;

    while(tmp != NULL){
        position[tmp->data] = target;
        tmp = tmp->next;
    }
}

void moveOnto(int a, int b){
    //printf("move onto\n");

    Node* theA = table[position[a]]->next;
    while(theA->data != a)  theA = theA->next;
    Node* theB = table[position[b]]->next;
    while(theB->data != b)  theB = theB->next;

    Node* Aprev = table[position[a]];
    while(Aprev->next != theA)  Aprev = Aprev->next;

    Aprev->next = NULL;
    theB->next = theA;

    //updatePos_move(theA, b);
    Node* updatePos = theA;
    while(updatePos != NULL){
        position[updatePos->data] = position[theB->data];
        updatePos = updatePos->next;
    }
}

void moveOver(int a, int b){
    //printf("move %d over %d\n", a, b);

    Node* theA = table[position[a]]->next;
    while(theA->data != a)  theA = theA->next;
    Node* theB = table[position[b]]->next;
    while(theB->data != b)  theB = theB->next;

    Node* Aprev = table[position[a]];
    while(Aprev->next != theA)  Aprev = Aprev->next;

    Aprev->next = NULL;

    if(theB->next == NULL){
        theB->next = theA;
        position[a] = position[b];
    }
    else{
        Node* Blast = theB;
        while(Blast->next != NULL)   Blast = Blast->next;
        Blast->next = theA;
    }

    //updatePos_move(theA, b);

    Node* updatePos = theA;
    while(updatePos != NULL){
        position[updatePos->data] = position[theB->data];
        updatePos = updatePos->next;
    }
}


void pileOnto(int a, int b){
    //printf("pile onto\n");

    //printf("find node %d and node %d\n", a, b);
    Node* theA = table[position[a]]->next;
    while(theA->data != a)    theA = theA->next;
    Node* theB = table[position[b]]->next;
    while(theB->data != b)    theB = theB->next;

    //printf("find the node before node %d\n", a);
    Node* Aprev = table[position[a]];
    //printf("1\n");
    while(Aprev->next != theA)   Aprev = Aprev->next;

    //printf("move %d and all books on book %d onto book %d\n", a, a, b);
    Aprev->next = NULL;
    theB->next = theA;

    //printf("update book %d and all books on %d's position to book %d\n", a, a, b);
    //updatePos_pile(theA, b);
    Node* tmp = theA;
    while(tmp != NULL){
        position[tmp->data] = position[theB->data];
        tmp = tmp->next;
    }
}

void pileOver(int a, int b){
    //printf("pile over\n");

    Node* theA = table[position[a]]->next;
    while(theA->data != a)  theA = theA->next;
    Node* theB = table[position[b]]->next;
    while(theB->data != b)  theB = theB->next;

    Node* Aprev = table[position[a]];
    while(Aprev->next != theA)  Aprev = Aprev->next;
    Aprev->next = NULL;

    if(theB->next == NULL){
        Aprev->next = NULL;
        theB->next = theA;
    }
    else{
        Node* Blast = theB;
        while(Blast->next != NULL)  Blast = Blast->next;
        Blast->next = theA;
    }

    //updatePos_pile(theA, b);
    Node* updatePos = theA;
    while(updatePos != NULL){
        position[updatePos->data] = position[theB->data];
        updatePos = updatePos->next;
    }

}

void printfPos(){
    for(int i = 0; i < n; i++){
        printf("%d ", position[i]);
    }

    printf("\n");
}

void printTable(){
    for(int i = 0; i < n; i++){
        printf("%d:", i);
        Node* tmp = table[i];
        while(tmp->next != NULL){
            printf(" %d", tmp->next->data);
            tmp = tmp->next;
        }
        printf("\n");
    }

    //printfPos();
}

int main(){
    scanf("%d", &n);

    initialize();

    int a, b = 0;
    char move1[4], move2[4];

    while(1){
        scanf("%s", move1);

        if(move1[0] == 'e')  break;

        scanf("%d", &a);
        scanf("%s", &move2);
        scanf("%d", &b);

        if(a == b)  continue;
        if(a > n || b > n)  continue;
        if(position[a] == position[b]) continue;

        if(move1[1] == 'o'){
            if(move2[1] == 'n'){ // move onto
                resetBook(a);
                resetBook(b);
                moveOnto(a, b);
                //printTable();
            }
            else{ // move over
                resetBook(a);
                //printTable();
                //printf("\n");
                moveOver(a, b);
                //printTable();
                //printf("move over finished\n");
            }
        }
        else{
            if(move2[1] == 'n'){ // pile onto
                resetBook(b);
                //printTable();
                //printf("\n");
                pileOnto(a, b);
                //printTable();
            }
            else{ // pile over
                pileOver(a, b);
                //printTable();
            }
        }
    }

    printTable();

    return 0;
}
