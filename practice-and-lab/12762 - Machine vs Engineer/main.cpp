#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <climits>
#include <ctime>
#include <iostream>
#include <cassert>
//#include "function.h"
using namespace std;

class Machine{
public:
    Machine(int L = 1, int R = 10);
    ~Machine();
    void init(int L, int R);
    bool MakeAnswer(char query_str[]) const;
    int TheNumber() const;
private:
    int Password;
};


class Engineer{
public:
    Engineer();
    ~Engineer();
    void init(); // Initialize the history, count
    void MakeQuery(char* query_str); // Make a Query depends on the history
    void GetAnswer(bool ans); // Get the answer From Machine, Update
private:
    int count;
    int value_history[201];
    int action_history[201];
    bool answer_history[201];
};


const int MAX_GUESS = 200;
int L, R;
int LB[4] = {0, 0, 0, (int)-1e8};
int RB[4] = {10, 1000, 10000, (int)1e8};

void init(int T){
    if( T <= 10 )
        L = LB[0], R = RB[0];
    else if( T <= 100 )
        L = LB[1], R = RB[1];
    else if( T <= 1000 )
        L = LB[2], R = RB[2];
    else
        L = LB[3], R = RB[3];
}

Engineer::Engineer() {}
Engineer::~Engineer() {}
void Engineer::init(){
    count = 0;
}
void Engineer::MakeQuery(char* query_str){
    static long long l = INT_MIN, r = INT_MAX;
    if(count == 0){
        l = INT_MIN;
        r = INT_MAX;
    } else {
        if(answer_history[0]) l = ((l+r) >> 1) + 1;
        else r = (l+r) >> 1;
    }
    count++;
    std::string s;
    if(l != r) s = "greater " + std::to_string((l+r) >> 1);
    else s = "guess " + std::to_string(l);
    strcpy(query_str, s.c_str());
}
void Engineer::GetAnswer(bool ans){
    answer_history[0] = ans;
}

int main(){
    srand(time(NULL));
    int T;
    scanf("%d", &T);
    init(T);

    Machine Mac(L, R);
    Engineer Eng;
    for(int t=1; t<=T; t++){
        printf("Round: %d\n", t);
        char query_str[100];
        bool success = false;
        Mac.init(L, R);
        Eng.init();

        for(int i=0; i<MAX_GUESS; i++){
            memset(query_str, 0, sizeof(query_str));
            Eng.MakeQuery( query_str );
            bool answer = Mac.MakeAnswer( query_str );
            Eng.GetAnswer(answer);

            if( strncmp(query_str, "guess", 5) == 0 && answer == true ){
                success = true;
                break;
            }
            fprintf(stderr, "%s\n", ( answer ? "YES" : "NO") );
        }
        if( success == true ){
            printf("Success!!\n");
        }
        else{
            printf("Freeze!! The Number is %d\n", Mac.TheNumber() );
            break;
        }
        printf("-----------------------\n");
    }
    return 0;
}
/* Class Machine */
Machine::Machine(int L, int R){
    this->init(L, R);
}
Machine::~Machine(){}
void Machine::init(int L, int R){
    static int shift = 0;
    shift += ( Password + rand() | 0xFFCCFF + 02473 ) * rand();
    shift = (shift << 16 ) | rand() & 0x0000FFFF + time(NULL);
    shift = abs(shift);
    Password = abs( rand() + shift ) % (R - L + 1) + L;
    
    assert( L <= Password && Password <= R );
}
bool Machine::MakeAnswer(char query_str[]) const{
    char op[100];
    int x;
    sscanf(query_str, "%s %d", op, &x);

    if (strcmp(op, "guess") == 0)
    {
        fprintf(stderr, "Guess %d is equal to P.\n", x);
        return this->Password == x;
    }
    else if (strcmp(op, "greater") == 0)
    {
        fprintf(stderr, "Query: P is %s than %d?\n", op, x);
        return this->Password > x;
    }
    else if (strcmp(op, "less") == 0)
    {
        fprintf(stderr, "Query: P is %s than %d?\n", op, x);
        return this->Password < x;
    }
    else
    {
        fprintf(stderr, "Unknown Action: %s\n", query_str);
        return false;
    }
}
int Machine::TheNumber() const{
    return Password;
}