/*
Purpose: An encryption-decryption program with 10 different ciphers
Authors:
    Zeyad Mohamed Arafat  zeyadarafat833@gmail.com
    John Ayman Demian     johnayman03@gmail.com
    Youssef Ahmed Beshir  youssefahmedbeshir@gmail.com
*/

#include "encryption.h"
#include "decryption.h"

int main() {
    string message, encrypted;
    cout << "Ahlan ya user ya habibi." << endl;

    while (true){
        cout << "What do you like to do?" << endl << endl;
        cout << "1- Cipher a message." << endl;
        cout << "2- Decipher a message." << endl;
        cout << "3- End." << endl;
        cout << "->";

        string menu;
        cin >> menu;

        if (menu == "3")
            break;


        else if (menu == "1"){
            cout << "Please enter the message to cipher." << endl;
            cout << "->";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, message);

            cout << "Which Cipher do you like to choose?" << endl;
            cout << "0- Affine cipher" << endl ;
            cout << "1- Route cipher" << endl;
            cout << "2- Atbash cipher" << endl;
            cout << "3- Vignere cipher" << endl;
            cout << "4- Baconian cipher" << endl;
            cout << "5- Simple substitution cipher" << endl;
            cout << "6- Polybius Square cipher" << endl;
            cout << "7- Morse code cipher" << endl;
            cout << "8- XOR cipher" << endl;
            cout << "9- Rail-fence cipher" << endl;
            cout << "->";

            string cipherChoice;
            cin >> cipherChoice;

            while(true){
                if (cipherChoice == "0"){
                    Encryption::encryptAffineCipher(message);
                    break;
                }
                else if (cipherChoice == "1"){
                    Encryption::route_cipher_encryption(message);
                    break;
                }
                else if (cipherChoice == "2"){
                    Encryption::atbash_encryption(message);
                    break;
                }
                else if (cipherChoice == "3"){
                    Encryption::vignere_encryption(message);
                    break;
                }
                else if (cipherChoice == "4"){
                    Encryption::baconian_encryption(message);
                    break;
                }
                else if (cipherChoice == "5"){
                    Encryption::simple_sub_encryption(message);
                    break;
                }
                else if (cipherChoice == "6"){
                    Encryption::polybius_square_encryption(message);
                    break;
                }
                else if (cipherChoice == "7"){
                    Encryption::morse_code_cipher(message);
                    break;
                }
                else if (cipherChoice == "8"){
                    Encryption::xor_encryption(message);
                    break;
                }
                else if (cipherChoice == "9"){
                    Encryption::rail_Fence_Encrypt(message);
                    break;
                }
                else{
                    cout << "Please enter a valid choice" << endl << endl;
                    break;
                }
            }
        }

        else if (menu == "2"){
            cout << "Please enter the message to decipher." << endl;
            cout << "->";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, encrypted);

            cout << "What cipher would you like to use?" << endl;
            cout << "0- Affine cipher" << endl ;
            cout << "1- Route cipher" << endl;
            cout << "2- Atbash cipher" << endl;
            cout << "3- Vignere cipher" << endl;
            cout << "4- Baconian cipher" << endl;
            cout << "5- Simple substitution cipher" << endl;
            cout << "6- Polybius Square cipher" << endl;
            cout << "7- Morse code cipher" << endl;
            cout << "8- XOR cipher" << endl;
            cout << "9- Rail-fence cipher" << endl;
            cout << "->";

            string cipher_choice;
            cin >> cipher_choice;

            while(true){
                if (cipher_choice == "0"){
                    Decryption::decryptAffineCipher(encrypted);
                    break;
                }
                else if (cipher_choice == "1"){
                    Decryption::route_cipher_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "2"){
                    Decryption::atbash_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "3"){
                    Decryption::vignere_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "4"){
                    Decryption::baconian_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "5"){
                    Decryption::simple_sub_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "6"){
                    Decryption::polybius_square_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "7"){
                    Decryption::morse_code_decipher(encrypted);
                    break;
                }
                else if (cipher_choice == "8"){
                    Decryption::xor_decryption(encrypted);
                    break;
                }
                else if (cipher_choice == "9"){
                    Decryption::rail_Fence_Decrypt(encrypted);
                    break;
                }
                else{
                    cout << "Please enter a valid choice" << endl << endl;
                    break;
                }
            }
        }
        else{
            cout << "Invalid choice." << endl << endl;
        }
    }
}
