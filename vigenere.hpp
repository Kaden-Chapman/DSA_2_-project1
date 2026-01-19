#ifndef VIGENERE_HPP
#define VIGENERE_HPP
#include <string>
using namespace std;

class VigenereCipher {
    private:
        string key;
        char shiftChar(char plaintextChar, char keyChar, bool encrypt);

    public:
        VigenereCipher(const string& key);
        string encrypt(const string& plaintext);
        string decrypt(const string& ciphertext);
};
#endif