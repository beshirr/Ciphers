#ifndef ENCRYPTION_DECRYPTION_DECRYPTION_H
#define ENCRYPTION_DECRYPTION_DECRYPTION_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <limits>
#include <bitset>
#include <algorithm>
#include <cmath>

using namespace std;

class Decryption {
public:
    static void baconian_decryption(string textToEncrypt);
    static void xor_decryption(string message);
    static void vignere_decryption(string message);
    static void decryptAffineCipher(const string& text);
    static void polybius_square_decryption(string& encrypted);
    static void route_cipher_decryption(const string& encrypted_sentence);
    static void morse_code_decipher(const string& text);
    static void rail_Fence_Decrypt(const string& message);
    static void simple_sub_decryption(const string& textToDecrypt);
    static void atbash_decryption(string textToDecrypt);
};
#endif
