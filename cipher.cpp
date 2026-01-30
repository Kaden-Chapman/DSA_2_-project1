#include "cipher.hpp"
#include "vigenere.hpp"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void Cipher::generateData(const string& namesFile, const string& rawFile)
{
    cout << "Generating raw data file from names file: " << namesFile << endl;
    ifstream infile(namesFile);
    ofstream outfile(rawFile);


    if (!infile.is_open()) {
        cerr << "Error opening names file: " << namesFile << endl;
        return;
    }

    string userid;

    string line;

while (getline(infile, line)) {
    if (line.empty()) continue;

    string userid = line.substr(0, line.find(' '));

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
