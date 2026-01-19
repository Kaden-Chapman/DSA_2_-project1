#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <string>
#include "Node.hpp"
class Hashtable {
    private:
        static const int tableSize = 101;
        Node* table[tableSize];

        int hashFunction(const string& userid);

    public:
        Hashtable();
        ~Hashtable();

        void insert(const string& userid, const string& encryptedPassword);
        Node* search(const string& userid);
        void remove(const string& userid);
};
#endif