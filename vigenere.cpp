#include "vigenere.hpp"
#include <string>
#include <random>
using namespace std;

char shiftChar(char plaintextChar, char keyChar, bool encrypt) {
    int base = plaintextChar - 'a';
    int shift = keyChar - 'a';
    if (!encrypt) shift = -shift;
    return 'a' + (base + shift + 26) % 26;
}

string vigenereEncrypt(const string& text) {
    string key = "jones";
    string result;

    for (size_t i = 0; i < text.size(); ++i) {
        result += shiftChar(text[i], key[i % key.size()], true);
    }

    return result;
}

string randomPassword() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 25);

    string password;
    password.reserve(9);

    for (int i = 0; i < 9; ++i) {
        password += char('a' + dist(gen));
    }

    return password;
}
