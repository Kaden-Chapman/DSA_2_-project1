#include "vigenere.hpp"

char VigenereCipher::shiftChar(char plaintextChar, char keyChar, bool encrypt){
int base = plaintextChar - 'a';
int shift = keyChar - 'a';
if(!encrypt) shift = -shift;
return 'a' + (base + shift + 26) % 26;
}
