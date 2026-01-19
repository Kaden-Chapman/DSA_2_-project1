#ifndef CIPHER_HPP  
#define CIPHER_HPP
#include <string>
using namespace std;

class Cipher{
    public:
        void generateData(const string& namesFile, const string& rawFile);
        void encryptData(const string& rawFile, const string& encryptedFile);
};
#endif