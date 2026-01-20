#ifndef VIGENERE_HPP
#define VIGENERE_HPP
#include <string>
using namespace std;

char shiftChar(char plaintextChar, char keyChar, bool encrypt);
string vigenereEncrypt(const std::string& text);
string randomPassword();

#endif