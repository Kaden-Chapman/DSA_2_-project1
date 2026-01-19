#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP
#include <string>
#include "Node.hpp"
using string;
class Hashtable {
    private:
        static const int tableSize = 101; // A prime number for better distribution
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