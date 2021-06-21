#include <iostream>
#include <string>

using namespace std;

bool match(char l, char r){
	switch(l){
		case'(' : return r == ')';
		case'{' : return r == '}';
		case'[' : return r == ']';
		case'<' : return r == '>';
	}
	return false;
}

bool is_left(char x){
	switch(x){
		case'(' :
		case'{' :
		case'[' :
		case'<' :	return true;
	}
	return false;
}

int main(){
	int N = 0;
	cin >> N;

	bool error = false;
	char stack[1000];
	getchar();

	for(int testcase = 0; testcase < N; testcase++){
		// get input and initialize
		string input;
		getline(cin, input);
		error = false;
		int top = -1;

		if(!input.empty()){
			for(string::iterator i = input.begin(); i != input.end(); ++i){
				if(is_left(*i))
					stack[++top] = *i;
				else if(top < 0 || !match(stack[top--], *i)){
					error = true;
					break;
				}
			}
		}

		// top should be -1 if there's nothing left
		if(top >= 0)	error = true;
		cout << "Case " << testcase+1 << ": ";
		if(error) cout << "No" << endl;
		else cout << "Yes" << endl;
	}

	return 0;
}
