// Author: justin0u0<dancinglinkxalgorithm@gmail.com>

#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
using namespace std;

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

#endif
