#include "decryption.h"
#include "helpers.h"


void Decryption::baconian_decryption(string textToDecrypt){
    string decryptedText = "", code = "";
    // Store the Baconian cipher mappings for each code
    map<string, string > decryptionMap = {
            {"aaaaa", "A"}, {"aaaab", "B"}, {"aaaba", "C"}, {"aaabb", "D"}, {"aabaa", "E"}, {"aabab", "F"}, {"aabba", "G"},
            {"aabbb", "H"}, {"abaaa", "I"}, {"abaab", "J"}, {"ababa", "K"}, {"ababb", "L"}, {"abbaa", "M"}, {"abbab", "N"},
            {"abbba", "O"}, {"abbbb", "P"}, {"baaaa", "Q"}, {"baaab", "R"}, {"baaba", "S"}, {"baabb", "T"}, {"babaa", "U"},
            {"babab", "V"}, {"babba", "V"}, {"babbb", "X"}, {"bbaaa", "Y"}, {"bbaab", "Z"}};

    for (int i = 0; i < textToDecrypt.length(); i++){
        if (isalpha(textToDecrypt[i])){
            // Append the character to the code
            code += textToDecrypt[i];
            if (code.length() % 5 == 0 ){
                decryptedText += decryptionMap[code];
                code = "";
            }

        }
        else{
            // If the character is not an alphabet, simply append it to the decrypted text
            decryptedText += textToDecrypt[i];
        }

    }
    cout << decryptedText << endl << endl;
}

void Decryption::xor_decryption(string message){
    // Checking validity
    while(!Helpers::isHexa(message)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, message);
    }
    // Removing Spaces
    message = Helpers::strip(message);
    string keyInput, key, output;
    key = "";

    cout << "Welcome to the XOR cipher, a secret key of any number of characters (letters, digits) is required."
         << endl << endl;
    cout << "Enter the secret key." << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyInput);

    // Setting the key, (Assigning each character in the message to the key).
    int counter = 0;
    for (int i = 0; i < message.length(); ++i) {
        if (counter == keyInput.length()){
            counter = 0;
        }
        key += keyInput[counter];
        counter++;
    }

    // Hexa to binary map
    map <char, string> hexa_to_binary = {
            {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"},
            {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"},
            {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"},
            {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}
    };

    string hexa_group, binaryStr;
    int k = 0;
    for (int i = 0; i < message.length(); i += 2) {
        // Converting each two hexadecimal bits to binary
        hexa_group = message.substr(i, 2);

        for (char j : hexa_group) {
            binaryStr += hexa_to_binary[j];
        }

        bitset<8> binary(binaryStr);
        bitset<8> kk (key[k]);
        k++;

        binaryStr = "";
        // Performing the XOR operation
        bitset<8> xor_operation;
        xor_operation = binary ^ kk;
        // Converting back to characters
        auto c = static_cast <char> (xor_operation.to_ulong());
        output += c;
    }
    cout << "Message: " << output << endl << endl;
}

void Decryption::vignere_decryption(string message){
    int ascii1 = 0, ascii2 = 0;
    string keyWordInput, keyWord, decrypted;
    char decoding;
    decrypted = "";

    while(message.length() > 80){
        cout << "Invalid message. Messages cannot be more than 80 characters, try again" << endl;
        cout << "->";
        getline(cin, message);
    }

    cout << "Welcome to vignere Cipher, A key of 1 - 8 letters is required." << endl << endl;
    cout << "Enter the key word" << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyWordInput);

    while(!Helpers::keyword_validity(keyWordInput)){
        getline(cin, keyWordInput);
    }

    // Setting the key, (Assigning each character to the key)
    int counter = 0;
    for (int i = 0; i < message.length(); ++i) {
        if (counter == keyWordInput.length()){
            counter = 0;
        }
        keyWord += keyWordInput[counter];
        counter++;
    }

    for (int i = 0; i < message.length(); i++){
        if (!(isalpha(message[i]))){
            decrypted += message[i];
        }
        else{
            ascii1 = int(toupper(message[i]));
            ascii2 = int(toupper(keyWord[i]));
            decoding = char(((ascii1 - ascii2 + 26) % 26) + 65);
            decrypted += decoding;
            counter++;
        }
    }
    cout << "Message: "<< decrypted << endl << endl;
}

void Decryption::decryptAffineCipher(const string& text) {
    // Check if the input text contains only letters and spaces
    bool valid_input = all_of(text.begin(), text.end(), [](char c) { return isalpha(c) || c == ' '; });
    if (!valid_input) {
        cout << "Input text contains non-letter characters other than spaces. Decryption cannot be performed." << endl;
        return;
    }

    // Your existing code remains unchanged below this point
    map<char, int> affine_map = {
            {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
            {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
            {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
            {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
            {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24},
            {'z', 25}
    };

    map<int, char> reverse_affine_map;
    for (const auto& pair : affine_map) {
        reverse_affine_map[pair.second] = pair.first;
    }

    string clear_text, decipher_text;
    int b, c, result;

    while (true) {
        cout << "Enter (b, c): ";
        cin >> b >> c;

        if (b > 0 && c > 0) {
            break;
        } else {
            cout << "Please enter positive numbers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    for (char i : text) {
        if (isalpha(i)) {
            clear_text += tolower(i);
        }
    }

    for (char i : clear_text) {
        result = Helpers::modulo(c * (affine_map[i] - b), 26);
        decipher_text += toupper(reverse_affine_map[result]);
    }

    cout << "Deciphered text: " << decipher_text << endl << endl;
}

void Decryption::polybius_square_decryption(string &encrypted) {
    // App data
    string poly[6][6] = {{" ", "",  "",  "",  "",  ""},
                         {"",  "A", "B", "C", "D", "E"},
                         {"",  "F", "G", "H", "I", "K"},
                         {"",  "L", "M", "N", "O", "P"},
                         {"",  "Q", "R", "S", "T", "U"},
                         {"",  "V", "W", "X", "Y", "Z"}};

    while (!Helpers::poly_decrypted_validity(encrypted)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, encrypted);
    }

    cout << "Welcome to the polybius cipher, A key of numbers from 1 to 5 in any order is required" << endl << endl;
    cout << "Enter the key." << endl;
    cout << "->";
    string keyInput;
    cin >> keyInput;

    while (!Helpers::poly_key_validity(keyInput)) {
        cout << "Enter the key." << endl;
        cout << "->";
        cin >> keyInput;
    }

    // Assigning the cipher key to the poly square.
    string key = " ";
    key += keyInput;

    for (int i = 0; i < 6; ++i) {
        poly[0][i] = key[i];
        poly[i][0] = key[i];
    }

    // Assign each letter to its index according to the key.
    map<vector<string>, string> alphaKeys;

    for (int i = 1; i < 6; ++i) {
        for (int j = 1; j < 6; ++j) {
            alphaKeys[{poly[i][0], poly[0][j]}] = poly[i][j];
        }
    }

    string decrypted;
    for (int i = 0; i < encrypted.length();) {
        if (i == encrypted.length() - 1){
            decrypted += encrypted[i];
            break;
        }
        for (int j = i + 1; j < encrypted.length(); j += 2) {
            string row, column;
            row = encrypted[i];
            column = encrypted[j];
            if (!isdigit(encrypted[i])){
                decrypted += encrypted[i];
                i ++;
                j --;
            }

            else{
                decrypted += alphaKeys[{row, column}];
                i += 2;
            }
        }
    }

    cout << "Decrypted message --> "<< decrypted << endl << endl;
}

void Decryption::route_cipher_decryption(const string& encrypted_sentence){

    // Explain to the user what he needs to do in order to decrypt the text.
    cout << "Welcome to the route cipher decryption in order to decrypt some text you need to enter the secret key" << endl << endl;


    int secretKey = Helpers::route_key_validity();       // getting the secret key and checking its validity.
    string strippedSentence = Helpers::strip(encrypted_sentence);    // stripping the text from any spaces.

    // calculating the number of rows in the matrix.
    int nRows = ceil(static_cast<float>(strippedSentence.length()) / static_cast<float>(secretKey));
    string cipherMatrix[nRows][secretKey];
    int direction = 0;// creating a direction variable to switch between directions.

    // four variables to indicate the start from each direction.
    int startDown = nRows - 1;
    int startUp = 0;
    int startRight = secretKey - 1;
    int startLeft = 0;

    string decrypted_sentence;
    int counter = 0;

    // filling the matrix with the character of the text in a spiral way.
    while(counter < secretKey * nRows){
        // the start point is the top right corner [startUp][startRight].
        // while going down we are moving in the most right column (startRight)
        // and change the row index from 0(startUp) to (startDown).
        if(direction == 0){
            for (int i = startUp; i <= startDown; i++){
                cipherMatrix[i][startRight] = strippedSentence[counter]; // adding the characters of the text to the matrix.
                counter++; // increasing the counter to stop the while loop.
            }
            startRight--; // changing the startRight value, so we don't get the same column when going down again.
            direction = 1; // changing the direction as planned in the iteration pattern.
        }
            // all the other loops work with the same logic.


        else if (direction == 1){ // direction 1 means going left in the matrix.
            for (int i = startRight; i >= startLeft; i--){
                cipherMatrix[startDown][i] = strippedSentence[counter];
                counter++;
            }
            startDown--;
            direction = 2;
        }

        else if (direction == 2){ // direction 2 means going up in the matrix.
            for (int i = startDown; i >= startUp; i--){
                cipherMatrix[i][startLeft] = strippedSentence[counter];
                counter++;
            }
            startLeft++;
            direction = 3;
        }

        else if (direction == 3){ // direction 3 means going right in the matrix.
            for (int i = startLeft; i <= startRight; i++){
                cipherMatrix[startUp][i] = strippedSentence[counter];
                counter++;
            }
            startUp++;
            direction = 0;
        }
    }

    // reading the characters in the matrix in the right order.
    for (int i = 0; i < nRows; i++){
        for (int j = 0; j < secretKey; j++){
            decrypted_sentence += cipherMatrix[i][j]; // adding characters to the decrypted sentence
        }
    }
    cout << decrypted_sentence << endl << endl; // printing the decrypted text
}

void Decryption::morse_code_decipher(const string& text) {
    bool valid_input = all_of(text.begin(), text.end(), [](char c) {
        return  c == ' ' || c == '.' || c == '-';
    });

    if (!valid_input) {
        cout << "Input text not contains spaces, periods, or hyphens. Encryption cannot be performed." << endl;
        return;
    }
    // set the morse table
    map<string, char> morse_decipher = {
            {".-", 'a'}, {"-...", 'b'}, {"-.-.", 'c'}, {"-..", 'd'}, {".", 'e'},
            {"..-.", 'f'}, {"--.", 'g'}, {"....", 'h'}, {"..", 'i'}, {".---", 'j'}, {"-.-", 'k'},
            {".-..", 'l'}, {"--", 'm'}, {"-.", 'n'}, {"---", 'o'}, {".--.", 'p'}, {"--.-", 'q'},
            {".-.", 'r'}, {"...", 's'}, {"-", 't'}, {"..-", 'u'}, {"...-", 'v'}, {".--", 'w'},
            {"-..-", 'x'}, {"-.--", 'y'}, {"--..", 'z'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
            {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}, {"-----", '0'}};
    // set main variables
    string decipher_text, morse_char;
    decipher_text = "";
    // make for loop to check validation of input
    for (char i : text) {
        //if text contain (. , -) add it to convert
        if (i == '.' || i == '-') {
            morse_char += i;
            // if space add it to separation
        } else if (i == ' ') {
            if (!morse_char.empty()) {
                // convert all char
                decipher_text += morse_decipher[morse_char];
                morse_char = "";
            } else {
                decipher_text += " "; // Add space for word separation
            }
        }
    }
    // check all char converted
    if (!morse_char.empty()) {
        decipher_text += morse_decipher[morse_char];
    }
    // print result
    cout <<"deciphered text : " <<decipher_text << endl << endl;
}

void Decryption::rail_Fence_Decrypt(const string& message) {
    // set main variables
    string clear_text = message,text, key, decryptedText;
    int num;
    // this loop to remove non-alphabetic letters from text before start
    for (char i : clear_text) {
        if (isalpha(i)){
            text += i ;
        }
    }
    // print welcome message
    cout << "welcome to Rail Fence encrypt program " << endl;
    // let user choose the key
    cout << "please choose the key 3 or 4: " ;
    cin.ignore();
    getline(cin , key ) ;

    while (key != "3" && key != "4") {
        cout << "Invalid key. Please choose the key 3 or 4: ";
        getline(cin, key);
    }
    num = stoi(key) ;
    if(num == 3 ) {
        int len = text.length();
        // set decrypt text with len = len of clear text
        decryptedText.resize(len);
        int pos = 0;
        //make for loop to iterates in the text
        for (int i = 0; i < 3 ; ++i) {
            int index = i;
            // put flag
            bool down = true;
            while (index < len) {
                decryptedText[index] = text[pos++];
                // when i == 0 or 2 it will take the letters from first row
                if (i == 0 || i ==  2)
                    index += 4;
                else {
                    // this line when i == 1 it will take the letters from second row
                    if (down)
                        index += 2 * (2 - i );
                        // and this when i == 1 it will take the letters from third row
                    else
                        index += 2 * i;
                    // switch flag to change the row
                    down = !down;
                }
            }
        }
        // print the result
        if (decryptedText == ""){
            cout <<"The encrypted text you entered not contains any letter to be deciphered,pls enter valid text " << endl << endl ;
        } else
            cout << "Decrypt text is :  " << decryptedText << endl ;
    }
    else if (num == 4) {
        int len = text.length();
        // set decrypt text with len = len of clear text
        decryptedText.resize(len);
        int pos = 0;
        //make for loop to iterates in the text
        for (int i = 0; i < 4 ; ++i) {
            int index = i;
            // put flag
            bool down = true;
            while (index < len) {
                decryptedText[index] = text[pos++];
                // this line when i == 0 or 3 it will take the letters from first and fourth row
                if (i == 0 || i ==  3)
                    index += 2 * 3;
                else {
                    // this line when i == 1 or 2 it will take the letters from second row
                    if (down)
                        index += 2 * (3 - i );
                        // and this when i == 1 or 2 it will take the letters from third row
                    else
                        index += 2 * i;
                    // switch flag to change the row
                    down = !down;
                }
            }
        }
        // print the result
        if (decryptedText == ""){
            cout << "The encrypted text you entered not contains any letter to be deciphered , pls enter valid text : " << endl << endl ;
        } else
            cout << "Decrypt text is :  " << decryptedText << endl ;
    }
}

void Decryption::simple_sub_decryption(const string& textToDecrypt){
    // Welcome message with explanation
    cout << "welcome to the simple substitution decryption, in order to get your text decrypted you need to enter the secret key" << endl;
    cout << "the key is any sequence of alphabetic characters (maximum 25 character)" << endl;
    string key, encryptedText;
    encryptedText = "";
    string alpha = "abcdefghijklmnoprqstuvwxyz";
    int decryptionIndex;

    cout << "please enter the secret key: ";
    cin >> key;
    key = Helpers::lower_case(key);

    while (!(Helpers::simpleSub_Key_Validity(key))){
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (Helpers::simpleSub_Key_Validity(key)) {
        if (key.length() < 25) {
            // If key length is less than 25, complete the key with remaining alphabet characters
            key = Helpers::complete_simple_sub_Key(key);
        }
        for (char i : textToDecrypt) {
            if (isalpha(i)){
                // Find index of character in the alphabet
                decryptionIndex = key.find(tolower(i));
                encryptedText += alpha[decryptionIndex];
            }
            else{
                // If character is not an alphabet, add it to the encrypted text
                encryptedText += i;
            }
        }
    }
    cout << encryptedText << endl << endl;
}

void Decryption::atbash_decryption(string textToDecrypt){
    // this is the same as the encryption function, but the printed messages are different.
    cout << "Welcome to atbash decryption, in order to get some text decrypted you need to enter the secret key" << endl;
    cout << "valid keys are (2, 4)" << endl;
    string key, decryptedText;
    decryptedText = "";

    cout << "please enter a secret key: ";
    cin >> key;

    while (!Helpers::atbash_key_validity(key)){
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (key == "2"){
        string firstAlpha = "ABCDEFGHIJKLM", secondAlpha = "ZYXWVUTSRQPON";
        for (char i : textToDecrypt){
            if (isalpha(i)){
                if (int(toupper(i)) <= 77){
                    int letterIndex = firstAlpha.find(toupper(i));
                    decryptedText += secondAlpha[letterIndex];
                }
                else
                {
                    int letterIndex = secondAlpha.find(toupper(i));
                    decryptedText += firstAlpha[letterIndex];
                }
            }
            else{
                decryptedText += i;
            }
        }

    }
    else if (key == "4"){
        string firstAlpha = "ABCDEF", secondAlpha = "MLKJIH", thirdAlpha = "NOPQRS", fourthAlpha = "ZYXWVU";
        for (int i = 0; i < textToDecrypt.length(); i++){
            if (isalpha(textToDecrypt[i])){
                if (int(toupper(textToDecrypt[i])) > 84){
                    int letterIndex = fourthAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += thirdAlpha[letterIndex];
                }
                else if (int(toupper(textToDecrypt[i])) == 84){
                    decryptedText += "T";
                }
                else if (int(toupper(textToDecrypt[i])) > 77){
                    int letterIndex = thirdAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += fourthAlpha[letterIndex];
                }
                else if (int(toupper(textToDecrypt[i])) > 71){
                    int letterIndex = secondAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += firstAlpha[letterIndex];
                }
                else if (int(toupper(textToDecrypt[i])) == 71){
                    decryptedText += "G";
                }
                else if (int(toupper(textToDecrypt[i])) < 71){
                    int letterIndex = firstAlpha.find(toupper(textToDecrypt[i]));
                    decryptedText += secondAlpha[letterIndex];
                }
            }
            else{
                decryptedText += textToDecrypt[i];
            }

        }

    }
    cout << decryptedText << endl << endl;
}
