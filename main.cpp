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

    cout << "LEGAL PASSWORD TESTS \n";
    for (int idx : indices) {
        if (idx >= static_cast<int>(rawEntries.size())) continue;

        const string& u = rawEntries[idx].first;
        const string& p = rawEntries[idx].second;

        Node* node = hashtable.search(u);
        if (!node) {
            cout << "User " << u << " not found in hash table.\n";
            continue;
        }

        string encryptedAttempt = vigenereEncrypt(p);
        bool match = (encryptedAttempt == node->encryptedPassword);

        cout << "User: " << u
             << " legal password -> "
             << (match ? "MATCH" : "NO MATCH") << "\n";
    }

    cout << "\n ILLEGAL PASSWORD TESTS \n";
    for (int idx : indices) {
        if (idx >= static_cast<int>(rawEntries.size())) continue;

        const string& u = rawEntries[idx].first;
        string illegalPass = rawEntries[idx].second;

        Node* node = hashtable.search(u);
        if (!node) {
            cout << "User " << u << " not found in hash table.\n";
            continue;
        }

        // Changes first letter to test illegal password
        if (!illegalPass.empty()) {
            illegalPass[0] = (illegalPass[0] == 'a') ? 'b' : 'a';
        }

        string encryptedAttempt = vigenereEncrypt(illegalPass);
        bool match = (encryptedAttempt == node->encryptedPassword);

        cout << "User: " << u
             << " illegal password -> "
             << (match ? "MATCH (ERROR)" : "NO MATCH (CORRECT)") << "\n";
    }

    return 0;
}
