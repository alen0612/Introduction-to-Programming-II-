#include <iostream>
#include <string.h>
#include <iomanip>
//#include "function.h"

using namespace std;

class BigInt
{
private:
    constexpr static int N = 150;
    constexpr static int WIDTH = 8, BASE = 100000000;
    bool sign;
    int bigInt[N];
public:
    // constructor
    BigInt();
    BigInt(char*);
    BigInt(const BigInt&);
    // copy assignment operator
    BigInt &operator = (const BigInt&);
    // comparison operator
    bool operator < (BigInt);
    bool operator > (BigInt);
    bool operator == (BigInt);
    bool operator >= (BigInt);
    bool operator <= (BigInt);
    // arithmetic operator
    BigInt operator + (BigInt);
    BigInt operator - (BigInt);
    // insertion & extraction operator
    friend istream& operator >> (istream&, BigInt&);
    friend ostream& operator << (ostream&, BigInt&);
};

BigInt::BigInt() :sign(true){
    for(int i = 0; i < N; i++)
        bigInt[i] = 0;
}

BigInt::BigInt(char *input) :sign(true){
    for(int i = 0; i < N; i++)
        this->bigInt[i] = 0;

    long long len = strlen(input);
    int cursor = 0;
    int i;

    for(i = len - 1; i > 7; i -= 8){
        int tmp = 0;
        for(int j = i - 7; j <= i; j++){
            tmp *= 10;
            tmp += input[j] - '0';
        }
        this->bigInt[cursor++] = tmp;
    }

    int tmp = 0;
    for(int j = 0; j <= i; j++){
        tmp *= 10;
        tmp += input[j] - '0';
    }
    this->bigInt[cursor] = tmp;
}

BigInt::BigInt(const BigInt &copied){
    *this = copied;
}

BigInt& BigInt::operator = (const BigInt &copied){
    if(this == &copied)  return *this;
    this->sign = copied.sign;

    for(int i = 0; i < N; i++)
        this->bigInt[i] = copied.bigInt[i];
    return *this;
}

bool BigInt::operator < (BigInt right){
    if(sign == true && right.sign == false) return false;
    else if(sign == false && right.sign == true)    return true;
    else if(sign == true && right.sign == true){
        for(int i = N - 1; i >= 0; i--){
            if(bigInt[i] > right.bigInt[i])
                return false;
            else if(bigInt[i] < right.bigInt[i])
                return true;
        }
    }
    else{ // both false
        for(int i = N - 1; i >= 0; i--){
            if(bigInt[i] > right.bigInt[i])
                return true;
            else if(bigInt[i] < right.bigInt[i])
                return false;
        }
    }

    return false;
}

bool BigInt::operator > (BigInt right){
    if(this->sign == true && right.sign == false) return true;
    else if(sign == false && right.sign == true)    return false;
    else if(sign == true && right.sign == true){
        for(int i = N - 1; i >= 0; i--){
            if(bigInt[i] > right.bigInt[i])
                return true;
            else if(bigInt[i] < right.bigInt[i])
                return false;
        }
    }
    else{ // both false
        for(int i = N - 1; i >= 0; i--){
            if(bigInt[i] > right.bigInt[i])
                return false;
            else if(bigInt[i] < right.bigInt[i])
                return true;
        }
    }

    return true;
}

bool BigInt::operator == (BigInt right){
    if(sign != right.sign)  return false;
    for(int i = N - 1; i >= 0; i--)
        if(bigInt[i] != right.bigInt[i])
            return false;

    return true;
}

bool BigInt::operator >= (BigInt right){
	if (this->sign == true && right.sign == false)
		return true;
	else if (this->sign == false && right.sign == true)
		return false;
	else if (this->sign == true && right.sign == true) {
		for (int i = N - 1; i >= 0; i--) {
			if (this->bigInt[i] > right.bigInt[i])
				return true;
			else if (this->bigInt[i] < right.bigInt[i])
				return false;
		}
	}
	else if (this->sign == false && right.sign == false) {
		for (int i = N - 1; i >= 0; i--) {
			if (this->bigInt[i] > right.bigInt[i])
				return false;
			else if (this->bigInt[i] < right.bigInt[i])
				return true;
		}
	}
    return true;
}

bool BigInt::operator <= (BigInt right){
	if (this->sign == true && right.sign == false)
		return true;
	else if (this->sign == false && right.sign == true)
		return false;
	else if (this->sign == true && right.sign == true) {
		for (int i = N - 1; i >= 0; i--) {
			if (this->bigInt[i] > right.bigInt[i])
				return true;
			else if (this->bigInt[i] < right.bigInt[i])
				return false;
		}
	}
	else if (this->sign == false && right.sign == false) {
		for (int i = N - 1; i >= 0; i--) {
			if (this->bigInt[i] > right.bigInt[i])
				return false;
			else if (this->bigInt[i] < right.bigInt[i])
				return true;
		}
	}
    return true;
}

BigInt BigInt::operator + (BigInt right){
    return *this;
}

BigInt BigInt::operator - (BigInt right){
    BigInt ans;
	if (this->sign == true) {	//(*this) is positive case
		if (*this == right) {
			ans.sign = true;
			for (int i = 0; i < N; i++)
				ans.bigInt[i] = 0;
		}
		else if (*this > right) {
			ans.sign = true;
			for (int i = 0; i < N; i++) {
				if (this->bigInt[i] > right.bigInt[i])
					ans.bigInt[i] = this->bigInt[i] - right.bigInt[i];
				else if (this->bigInt[i] < right.bigInt[i]) {
					this->bigInt[i + 1] -= 1;
					ans.bigInt[i] = this->bigInt[i] + (BASE - right.bigInt[i]);
				}
				else
					ans.bigInt[i] = 0;
			}
		}
		else if (*this < right) {
			ans.sign = false;
			for (int i = 0; i < N; i++) {
				if (right.bigInt[i] > this->bigInt[i])
					ans.bigInt[i] = right.bigInt[i] - this->bigInt[i];
				else if (right.bigInt[i] < this->bigInt[i]) {
					right.bigInt[i + 1] -= 1;
					ans.bigInt[i] = right.bigInt[i] + (BASE - this->bigInt[i]);
				}
				else
					ans.bigInt[i] = 0;
			}
		}
	}
	else if (this->sign == false) {	//(*this) is negative case
		ans.sign = false;
                //這個迴圈可以寫成operator + 的function
                //變成ans = (*this) + right;
                //......吧? 因為我沒試過
                //我就懶(・∀・)
		for (int i = 0; i < N; i++) {
			ans.bigInt[i] = this->bigInt[i] + right.bigInt[i];
			if (ans.bigInt[i] >= BASE) {
				ans.bigInt[i] = ans.bigInt[i] - BASE;
				this->bigInt[i + 1] += 1;
			}
		}
	}
    return ans;
}

istream& operator >> (istream &in, BigInt &n){
	char str[1205];    //注意，只開100會REㄛ
	cin >> str;
	n = BigInt(str);
    return in;
}

ostream& operator << (ostream &out, BigInt &n){
    if (n.sign == false)
        cout << "-";
    bool start = false;
	bool first = true;
	for (int i = 149; i >= 0; i--) {
        if (n.bigInt[i] != 0)
            start = true;
        if (start) {
			if (first) {
				cout << n.bigInt[i];
				first = false;
			}
            else
                cout << setw(8) << setfill('0') << n.bigInt[i];
        }
    }
    //沒有下面兩行 第二筆會WA呦>.^
	if (!start)
		cout << "0";
    return out;
}

void solution(BigInt &tanjiro, BigInt &zenitsu, BigInt &inosuke, int n){
	for (int i = 0; i < n; i++) {
		BigInt mission;
		cin >> mission;
		if (inosuke >= tanjiro && inosuke >= zenitsu)
			inosuke = inosuke - mission;
		else if (tanjiro >= inosuke && tanjiro >= zenitsu)
			tanjiro = tanjiro - mission;
		else if (zenitsu >= inosuke && zenitsu >= tanjiro)
			zenitsu = zenitsu - mission;
	}
}

int main()
{
    int n;
    cin >> n;
    // initialize health condition
    BigInt hi, kaminari, kedamono;
    cin >> hi;
    kaminari = kedamono = hi;
    // go on mission
    solution(hi, kaminari, kedamono, n);
    // output result
    cout << hi << endl;
    cout << kaminari << endl;
    cout << kedamono << endl;
}

