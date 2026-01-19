#include "cipher.hpp"
#include "vigenere.hpp" 
#include <fstream>
#include <string>
using namespace std;

string randomPassword() {
    string password;
    password.reserve(9);
    for (int i = 0; i < 9; ++i) {
        char c = 'a' + rand() % 26;
        password.push_back(c);
    }
    return password;
}


