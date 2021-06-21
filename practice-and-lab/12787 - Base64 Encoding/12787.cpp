// Author: justin0u0<dancinglinkxalgorithm@gmail.com>

#include <iostream>
#include "function.h"
using namespace std;

/* ====== Begin implementation of Base64Codec member function ====== */

/**
 * Given a 6 bit binary number in 10 decimal,
 * return the corresponding character to Base64 encoding.
 * Example:
 *  binaryNumber = 010011(binary) = 19(decimal)
 *  encodeCharacter(binaryNumber) return character 'T'
 */
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
