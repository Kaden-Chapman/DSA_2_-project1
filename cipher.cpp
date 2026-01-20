#include "cipher.hpp"
#include "vigenere.hpp"
#include <fstream>
#include <string>
using namespace std;

void Cipher::generateData(const string& namesFile,
                          const string& rawFile)
{
    ifstream infile(namesFile);
    ofstream outfile(rawFile);

    string userid;

    while (infile >> userid) {
        string password = randomPassword();
        outfile << userid << " " << password << "\n";
    }
}

void Cipher::encryptData(const string& rawFile,
                         const string& encryptedFile)
{
    ifstream infile(rawFile);
    ofstream outfile(encryptedFile);

    string userid;
    string rawPassword;

    while (infile >> userid >> rawPassword) {
        string encrypted = vigenereEncrypt(rawPassword);  // key = "jones"
        outfile << userid << " " << encrypted << "\n";
    }
}
