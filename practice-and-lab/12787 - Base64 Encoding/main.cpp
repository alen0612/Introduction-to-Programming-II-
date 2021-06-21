// Author: justin0u0<dancinglinkxalgorithm@gmail.com>

#include <iostream>
#include <sstream>
//#include "function.h"
using namespace std;

/* ====== Begin implementation of Base64Codec member function ====== */

/**
 * Given a 6 bit binary number in 10 decimal,
 * return the corresponding character to Base64 encoding.
 * Example:
 *  binaryNumber = 010011(binary) = 19(decimal)
 *  encodeCharacter(binaryNumber) return character 'T'
 */

class Codec {
protected:
  bool encoded;
  string code_str;
public:
  Codec(string& code_str): code_str(code_str), encoded(false) {}
  virtual void encode() = 0;
  virtual void decode() = 0;
  virtual void print(ostream& os) const = 0;
  virtual bool is_encoded() const = 0;
};

class Base64Codec: public Codec {
private:
  // Given 6-bits binary number, return with the Base64 encode character
  char encodeCharacter(int binaryNumber) const;
public:
  // Inherit from base class
  Base64Codec(string& code_str): Codec(code_str) {}
  // TODO: Encode the code_str
  void encode() override;
  // Decode the code_str
  void decode() override;
  // Print the code_str
  void print(ostream& os) const override;
  // Get code_str status
  bool is_encoded() const override;
};

char Base64Codec::encodeCharacter(int binaryNumber) const {
  if (binaryNumber >= 0 && binaryNumber < 26)
    return binaryNumber + 'A';
  else if (binaryNumber < 52)
    return binaryNumber - 26 + 'a';
  else if (binaryNumber < 62)
    return binaryNumber - 52 + '0';
  else if (binaryNumber == 62)
    return '+';
  else if (binaryNumber == 63)
    return '-';
  return ' ';
}

void Base64Codec::decode() {
}

void Base64Codec::print(ostream& os) const {
  os << code_str;
}

bool Base64Codec::is_encoded() const {
  return encoded;
}

ostream& operator<<(ostream& os, const Base64Codec& codec) {
  codec.print(os);
  return os;
}

void Base64Codec::encode(){
    cout << "Encode!" << endl;
    cout << code_str << endl;
    string ascii;

    for(auto c:code_str){
        int tmp = (int)c;
        cout << "tmp : " << tmp << endl;
        if(tmp == 32)   ascii += "00100000";
        else if(tmp == 33) ascii += "00100001";
        else if(tmp == 44) ascii += "00101100";
        else if(tmp == 46) ascii += "00101110";
        else if(tmp == 65) ascii += "01000001"; // A
        else if(tmp == 66) ascii += "01000010";
        else if(tmp == 67) ascii += "01000011";
        else if(tmp == 68) ascii += "01000100";
        else if(tmp == 69) ascii += "01000101";
        else if(tmp == 70) ascii += "01000110";
        else if(tmp == 71) ascii += "01000111";
        else if(tmp == 72) ascii += "01001000";
        else if(tmp == 73) ascii += "01001001";
        else if(tmp == 74) ascii += "01001010";
        else if(tmp == 75) ascii += "01001011";
        else if(tmp == 76) ascii += "01001100";
        else if(tmp == 77) ascii += "01001101";
        else if(tmp == 78) ascii += "01001110";
        else if(tmp == 79) ascii += "01001111";
        else if(tmp == 80) ascii += "01010000";
        else if(tmp == 81) ascii += "01010001";
        else if(tmp == 82) ascii += "01010010";
        else if(tmp == 83) ascii += "01010011";
        else if(tmp == 84) ascii += "01010100";
        else if(tmp == 85) ascii += "01010101";
        else if(tmp == 86) ascii += "01010110";
        else if(tmp == 87) ascii += "01010111";
        else if(tmp == 88) ascii += "01011000";
        else if(tmp == 89) ascii += "01011001";
        else if(tmp == 90) ascii += "01011010";
        else if(tmp == 97) ascii += "01100001";
        else if(tmp == 98) ascii += "01100010";
        else if(tmp == 99) ascii += "01100011";
        else if(tmp == 100) ascii += "01100100";
        else if(tmp == 101) ascii += "01100101";
        else if(tmp == 102) ascii += "01100110";
        else if(tmp == 103) ascii += "01100111";
        else if(tmp == 104) ascii += "01101000";
        else if(tmp == 105) ascii += "01101001";
        else if(tmp == 106) ascii += "01101010";
        else if(tmp == 107) ascii += "01101011";
        else if(tmp == 108) ascii += "01101100";
        else if(tmp == 109) ascii += "01101101";
        else if(tmp == 110) ascii += "01101110";
        else if(tmp == 111) ascii += "01101111";
        else if(tmp == 112) ascii += "01110000";
        else if(tmp == 113) ascii += "01110001";
        else if(tmp == 114) ascii += "01110010";
        else if(tmp == 115) ascii += "01110011";
        else if(tmp == 116) ascii += "01110100";
        else if(tmp == 117) ascii += "01110101";
        else if(tmp == 118) ascii += "01110110";
        else if(tmp == 119) ascii += "01110111";
        else if(tmp == 120) ascii += "01111000";
        else if(tmp == 121) ascii += "01111001";
        else if(tmp == 122) ascii += "01111010";
    }
    int count = 0;
    for(auto check:ascii){
        count++;
    }
    if(count%6 == 0){ // no need to add '='
        while(count > 0){

        }
    }
    else{

    }
}

/* ===================== End Implementation ===================== */

int main() {
  string s;
  getline(cin, s);

  Base64Codec str(s);

  if (!str.is_encoded()) {
    str.encode();
    cout << str << endl;
  }
  return 0;
}
