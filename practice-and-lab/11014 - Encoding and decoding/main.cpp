#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
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

class RleCodec: public Codec
{
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

void RleCodec::encode()
{
    /*stringstream ss;
    string s;
    char tmp = code_str.front();
    int count = 0;

    for(auto c : code_str){
        if(c == tmp)    count++;
        else{
            if(count == 1)  ss << tmp;
            else if(count == 2) ss << tmp << tmp;
            else    ss << count << tmp;

            tmp = c;
            count = 1;
        }
    }

    if(count == 1)  ss << tmp;
    else if(count == 2) ss << tmp << tmp;
    else    ss << count << tmp;

    code_str = ss.str();
    encoded = true;*/
}

void RleCodec::decode()
{
    /*stringstream ss;
    stringstream int_ss;
    for(auto c : code_str){
        if(isdigit(c))  int_ss << c;
        else if(isalpha(c)){
            int count = 0;
            int_ss >> count;
            if(count == 0)  ss << c;
            else
                while(count--)  ss << c;

            int_ss.str("");
            int_ss.clear();
        }
    }

    code_str = ss.str();
    encoded = false;*/
}

std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}

int main()
{
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
