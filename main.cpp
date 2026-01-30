
#include "cipher.hpp"
#include "Hashtable.hpp"
#include "vigenere.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

string toUpper(const string& s) {
    string out = s;
    for (char& c : out) c = toupper(c);
    return out;
}

int main() {
    Cipher cipher;
    Hashtable hashtable;

    cipher.generateData("names.txt", "rawdata.txt");
    cipher.encryptData("rawdata.txt", "encrypteddata.txt");

    ifstream encFile("encrypteddata.txt");
    string userid, encryptedPassword;

    while (encFile >> userid >> encryptedPassword) {
        hashtable.insert(userid, encryptedPassword);
    }
    encFile.close();

    ifstream rawFile("rawdata.txt");
    vector<pair<string, string>> rawEntries;
    string rawUser, rawPass;

    while (rawFile >> rawUser >> rawPass) {
        rawEntries.emplace_back(rawUser, rawPass);
    }
    rawFile.close();


    int indices[] = {0, 2, 4, 6, 8};

  cout << "Legal:\n";
cout << left
     << setw(12) << "Userid"
     << setw(18) << "Password(file)"
     << setw(22) << "Password(table/un)"
     << setw(10) << "Result"
     << "\n";

for (int idx : indices) {
    if (idx >= static_cast<int>(rawEntries.size())) continue;

    const string& userid = rawEntries[idx].first;
    const string& plaintext = rawEntries[idx].second;

    string useridUpper = toUpper(userid);
    Node* node = hashtable.search(useridUpper);
    if (!node) continue;

    string encryptedAttempt = vigenereEncrypt(plaintext);
    bool match = (encryptedAttempt == node->encryptedPassword);

    cout << left
         << setw(12) << useridUpper
         << setw(18) << plaintext
         << setw(22) << node->encryptedPassword
         << setw(10) << (match ? "match" : "no match")
         << "\n";
}


  cout << "\nIllegal:\n";
cout << left
     << setw(12) << "Userid"
     << setw(18) << "Password(mod)"
     << setw(22) << "Password(table/un)"
     << setw(10) << "Result"
     << "\n";

for (int idx : indices) {
    if (idx >= static_cast<int>(rawEntries.size())) continue;

    const string& userid = rawEntries[idx].first;
    string illegalPass = rawEntries[idx].second;

    string useridUpper = toUpper(userid);
    Node* node = hashtable.search(useridUpper);
    if (!node) continue;

    if (!illegalPass.empty()) {
        illegalPass[0] = (illegalPass[0] == 'a') ? 'b' : 'a';
    }

    string encryptedAttempt = vigenereEncrypt(illegalPass);
    bool match = (encryptedAttempt == node->encryptedPassword);

    cout << left
         << setw(12) << useridUpper
         << setw(18) << illegalPass
         << setw(22) << node->encryptedPassword
         << setw(10) << (match ? "match (ERROR)" : "no match")
         << "\n";
}
 

    return 0;
}
