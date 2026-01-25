#include "cipher.hpp"
#include "Hashtable.hpp"
#include "vigenere.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    Cipher cipher;
    Hashtable hashtable;

    // Generates and encrypts data files
    cipher.generateData("names.txt", "rawdata.txt");
    cipher.encryptData("rawdata.txt", "encrypteddata.txt");

    // Loads encrypteddata.txt into hash table
    ifstream encFile("encrypteddata.txt");
    string userid, encryptedPassword;

    while (encFile >> userid >> encryptedPassword) {
        hashtable.insert(userid, encryptedPassword);
    }
    encFile.close();

    // Loads rawdata.txt into memory
    ifstream rawFile("rawdata.txt");
    vector<pair<string, string>> rawEntries;
    string rawUser, rawPass;

    while (rawFile >> rawUser >> rawPass) {
        rawEntries.emplace_back(rawUser, rawPass);
    }
    rawFile.close();

    // test
int indices[] = {0, 2, 4, 6, 8};

cout << "Legal:\n";
cout << "Userid\tPassword(file)\tPassword(table/un)\tResult\n";

for (int idx : indices) {
    if (idx >= static_cast<int>(rawEntries.size())) continue;

    const string& userid = rawEntries[idx].first;
    const string& plaintext = rawEntries[idx].second;

    Node* node = hashtable.search(userid);
    if (!node) continue;

    string encryptedAttempt = vigenereEncrypt(plaintext);
    bool match = (encryptedAttempt == node->encryptedPassword);

    cout << userid << "\t"
         << plaintext << "\t"
         << node->encryptedPassword << "\t"
         << (match ? "match" : "no match")
         << "\n";
}

cout << "\nIllegal:\n";
cout << "Userid\tPassword(mod)\tPassword(table/un)\tResult\n";

for (int idx : indices) {
    if (idx >= static_cast<int>(rawEntries.size())) continue;

    const string& userid = rawEntries[idx].first;
    string illegalPass = rawEntries[idx].second;

    Node* node = hashtable.search(userid);
    if (!node) continue;

    // modify first letter
    if (!illegalPass.empty()) {
        illegalPass[0] = (illegalPass[0] == 'a') ? 'b' : 'a';
    }

    string encryptedAttempt = vigenereEncrypt(illegalPass);
    bool match = (encryptedAttempt == node->encryptedPassword);

    cout << userid << "\t"
         << illegalPass << "\t"
         << node->encryptedPassword << "\t"
         << (match ? "match (ERROR)" : "no match")
         << "\n";
}
    return 0;
}
