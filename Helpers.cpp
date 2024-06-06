#include "helpers.h"

string Helpers::strip(const std::string &sentence) {
    // To remove spaces from text
    string strippedSentence;
    for(char i : sentence){
        if(i != ' '){
            strippedSentence += i;
        }
    }
    return strippedSentence;
}

bool Helpers::isHexa(std::string message) {
    message = strip(message);
    // Decrypted messages in hexa should only be length of even numbers
    if (message.length() % 2 != 0){
        cout << "Invalid message, try again" << endl;
        cout << "->";
        return false;
    }
    // Make sure that input is a valid hexadecimal number
    for(auto i: message){
        if((i < '0' || i > '9') && (i < 'A' || i > 'F')){
            cout << "Invalid Hexadecimal input, try again." << endl;
            cout << "->";
            return false;
        }
    }
    return true;
}

bool Helpers::keyword_validity(const std::string &key) {
    for(auto i : key){
        if(not isalpha(i)){
            cout << "Invalid key. Key should contain alphabetic letters only, try again" << endl;
            cout << "->";
            return false;
        }
    }

    if (key.length() > 8){
        cout << "Invalid key. Key cannot be more than 8 letters, try again" << endl;
        cout << "->";
        return false;
    }
    return true;
}

int Helpers::modulo(int a, int b) {
    return (a % b + b) % b;
}

bool Helpers::poly_decrypted_validity(std::string &encrypted) {
    // Checking the validity of the decrypted message.
    for (auto i : encrypted){
        if (isalpha(i)){
            cout << "Invalid message. Encrypted messages should be digits only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    string cleanEncrypted;
    for (auto i: encrypted) {
        if (!isdigit(i)) {
            continue;
        }
        else {
            cleanEncrypted += i;
        }
    }

    for (auto i : cleanEncrypted){
        string ch;
        ch = i;
        if (stoi (ch) > 5 || stoi(ch) == 0){
            cout << "Message should have numbers [1 -> 5] only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    if (cleanEncrypted.length() % 2 != 0){
        cout << "Invalid message. Try again." << endl;
        cout << "->";
        return false;
    }
    return true;
}

bool Helpers::poly_key_validity(const std::string &key) {
    // Checking the validity of the cipher key and handling possible errors.
    int number;
    string ch;

    if (key.length() != 5){
        cout << "Invalid key. Key should be a length of 5 numbers only, try again." << endl;
        cout << "->";
        return false;
    }

    for (auto i : key){
        if ( ! isdigit(i)){
            cout << "Invalid key. Key should contain integer numbers only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    for (auto i : key) {
        ch = i;
        number = stoi(ch);
        if (number < 1 || number > 5){
            cout << "Invalid key. Key should contain numbers of range [1, 5] only, try again." << endl;
            cout << "->";
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 5; ++j) {
            if (key[i] == key[j]){
                cout << "Invalid key. Key should not contain the same number twice, try again." << endl;
                cout << "->";
                return false;
            }
        }
    }
    return true;
}

int Helpers::route_key_validity() {
    // To make sure that the secret key of the route cipher is valid.
    int secretKey;
    cout << "Please enter the secret key: ";
    while (!(cin >> secretKey) || secretKey <= 0 ){
        cout << "Please enter a valid key (valid keys are integers bigger than 0)." << endl;
        cin.clear();
        cin.ignore();
    }
    return secretKey;
}

string Helpers::lower_case(std::string key) {
    for (char & i : key){
        i = tolower(i);
    }
    return key;
}

bool Helpers::simpleSub_Key_Validity(const string& key){
    // check the validity of the simple substitution key.
    for (char i : key) {
        if (!isalpha(i))return false;
    }
    return true;
}

string Helpers::complete_simple_sub_Key(string key){
    // complete the key of the simple substitution cipher if needed.
    string alpha = "abcdefghijklmnoprqstuvwxyz";
    int letterIndex;
    for (char i : key) {
        // iterate through the given key and remove it from the alpha.
        letterIndex = alpha.find(tolower(i));
        alpha.erase(alpha.begin()+letterIndex);
    }
    // add the remaining alpha to the key.
    key += alpha;
    return key;
}

bool Helpers::atbash_key_validity(const string& key){
    // Checking the validity of the atbash key.
    if((key == "2") or (key == "4")) return true;
    return false;
}