#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
//#include "function.h"

using namespace std;

class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }


    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};

std::ostream& operator<<(std::ostream& os, Codec& data){
    data.show(os);
    return os;
}

void encode_decode(Codec & data){
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}

void RleCodec::encode(){
	stringstream ss;
	int flag = 0;
	int count = 0;
	int idx = 0;
	int len = code_str.length();
	char start = ' ';

    for(int i = 0; i < len; i++){
        if(flag == 0){
            start = code_str[i];
            count++;
            flag = 1;
        }
        if(code_str[++idx] == start){
            count++;
            continue;
        }
        else{
            ss << "Q";
            char tmp = 'A';
            while(count > 26) {
                count -= 26;
                ss << "Z";
                ss << start;
                ss << "Q";
            }
            for(int j = 0; j < count - 1; j++)
                tmp++;
            ss << tmp;
            ss << start;
            start = ' ';
            flag = 0;
            count = 0;
        }
    }

    code_str = ss.str();
	encoded = true;
}

void RleCodec::decode(){
	stringstream os;
	string int_str;
	char q = 'A';
	char number = ' ';
	int cnt = 0;
	for (auto c : code_str) {
        if (q=='A') {
            q = c;
		}else if(number == ' '){
            number = c;
		}
        else {
            int_str.push_back(c);
			int cnt = 0;
            cnt = number - 'A' +1;
            for (int i=0; i<cnt; ++i)
				os << c;
			int_str.clear();
			number = ' ';
			q = 'A';
		}
	}

	code_str = os.str();
	encoded = false;
}


int main(){
    std::string input_string;
    std::cin >> input_string;

    DummyCodec dummy{input_string};
    encode_decode(dummy);
    std::cout << "Dummy encoding: ";
    std::cout << dummy << std::endl;
    encode_decode(dummy);
    std::cout << "Dummy decoding: ";
    std::cout << dummy << std::endl;

    RleCodec rle{input_string};
    encode_decode(rle);
    std::cout << "RLE encoding: ";
    std::cout << rle << std::endl;
    encode_decode(rle);
    std::cout << "RLE decoding: ";
    std::cout << rle << std::endl;
}
