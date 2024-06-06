#ifndef ENCRYPTION_DECRYPTION_ENCRYPTION_H
#define ENCRYPTION_DECRYPTION_ENCRYPTION_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <bitset>
#include <algorithm>
#include <cmath>

using namespace std;

class Encryption {
public:
    static void baconian_encryption(string textToEncrypt);
    static void xor_encryption(const string& message);
    static void vignere_encryption(string message);
    static void encryptAffineCipher(const string& text);
    static void polybius_square_encryption(const string& message);
    static void route_cipher_encryption(const string& sentence_to_encrypt);
    static void morse_code_cipher(const string& text);
    static void rail_Fence_Encrypt(const string& message);
    static void simple_sub_encryption(const string& textToEncrypt);
    static void atbash_encryption(string textToEncrypt);
};


#endif //ENCRYPTION_DECRYPTION_ENCRYPTION_H
