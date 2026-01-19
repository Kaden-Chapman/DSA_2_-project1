#ifndef NODE_HPP
#define NODE_HPP
#include <string>
using namespace std;

class Node {
    public:
    string userid;
    string encryptedPassword;
    Node* next;

    Node(const string& user, const string& encrypted) : userid(user), encryptedPassword(encrypted), next(nullptr) {}

};
#endif

