#ifndef ENCRYPTION_DECRYPTION_HELPERS_H
#define ENCRYPTION_DECRYPTION_HELPERS_H

#include <iostream>
#include <string>

using std::string, std::cout, std::cin, std::endl;

class Helpers {
public:
    static string strip(const string& sentence);
    // XOR Cipher
    static bool isHexa(string message);
    // Vignere Cipher
    static bool keyword_validity(const string& key);
    // Affine Cipher
    static int modulo(int a, int b);
    // Polybius square Cipher
    static bool poly_decrypted_validity(string & encrypted);
    static bool poly_key_validity (const string& key);
    // Route Cipher
    static int route_key_validity();
    // Simple substitution Cipher
    static string lower_case(string key);
    static string complete_simple_sub_Key(string key);
    static bool simpleSub_Key_Validity(const string& key);
    // Atbash Cipher
    static bool atbash_key_validity(const string& key);
};

#endif //ENCRYPTION_DECRYPTION_HELPERS_H
