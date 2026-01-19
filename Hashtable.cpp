#include "Hashtable.hpp"
using namespace std;
Hashtable::Hashtable() {
    for (int i = 0; i < tableSize; ++i) {
        table[i] = nullptr;
    }
}

Hashtable::~Hashtable() {
    for (int i = 0; i < tableSize; ++i) {
        Node* current = table[i];
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
}

int Hashtable::hashFunction(const string& userid) {
    unsigned int hash = 0;
    for (char c : userid) {
        hash = ((hash << 5) + hash) + c; 
    }
    return hash % tableSize;
}

void Hashtable::insert(const string& userid, const string& encryptedPassword) {
    int index = hashFunction(userid);
    Node* newNode = new Node(userid, encryptedPassword);
    newNode->next = table[index];
    table[index] = newNode;
}

Node* Hashtable::search(const string& userid) {
    int index = hashFunction(userid);
    Node* current = table[index];
    while (current != nullptr) {
        if (current->userid == userid) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void Hashtable::remove(const string& userid) {
    int index = hashFunction(userid);
    Node* current = table[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->userid == userid) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}