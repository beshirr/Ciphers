#include "encryption.h"
#include "helpers.h"


void Encryption::baconian_encryption(string textToEncrypt){
    string encryptedText = "";
    // Store the Baconian cipher mappings for each letter
    map<char, string> encryptionMap = {
            {'A', "aaaaa"}, {'B', "aaaab"}, {'C', "aaaba"}, {'D', "aaabb"}, {'E', "aabaa"}, {'F', "aabab"}, {'G', "aabba"},
            {'H', "aabbb"}, {'I', "abaaa"}, {'J', "abaab"}, {'K', "ababa"}, {'L', "ababb"}, {'M', "abbaa"}, {'N', "abbab"},
            {'O', "abbba"}, {'P', "abbbb"}, {'Q', "baaaa"}, {'R', "baaab"}, {'S', "baaba"}, {'T', "baabb"}, {'U', "babaa"},
            {'V', "babab"}, {'W', "babba"}, {'X', "babbb"}, {'Y', "bbaaa"}, {'Z', "bbaab"}};

    for (int i = 0; i < textToEncrypt.length(); i++){
        if (isalpha(textToEncrypt[i])){
            // Append the Baconian code for the corresponding uppercase letter to the encrypted text
            encryptedText += encryptionMap[toupper(textToEncrypt[i])];
        }
        else{
            // If the character is not an alphabet, append it to the encrypted text
            encryptedText += textToEncrypt[i];
        }

    }
    cout << encryptedText << endl << endl;
}

void Encryption::xor_encryption(const string& message){
    string keyInput, key, output, hexaOutput;
    key = "";
    cout << "Welcome to the XOR cipher, a secret key of any number of characters (letters, digits) is required."
         << endl << endl;
    cout << "Enter the secret key" << endl;
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

    // Binary to hexadecimal map
    map <string, char> binary_to_hexa = {
            {"0000", '0'}, {"0001", '1'}, {"0010", '2'}, {"0011", '3'},
            {"0100", '4'}, {"0101", '5'}, {"0110", '6'}, {"0111", '7'},
            {"1000", '8'}, {"1001", '9'}, {"1010", 'A'}, {"1011", 'B'},
            {"1100", 'C'}, {"1101", 'D'}, {"1110", 'E'}, {"1111", 'F'}
    };

    for (int i = 0; i < message.length(); ++i) {
        // converting each character to its binary representation.
        bitset<8> binaryMsg (message[i]);
        bitset<8> binaryKey (key[i]);

        // Performing the XOR operation.
        bitset<8> xor_operation;
        xor_operation = binaryKey ^ binaryMsg;

        string binaryGroups, hexa;

        for (int j = 0; j < (xor_operation.to_string().length()); j += 4) {
            // converting each 4 bits to hexadecimal.
            binaryGroups = (xor_operation.to_string()).substr(j, 4);
            hexa = binary_to_hexa[binaryGroups];
            hexaOutput += hexa;
        }
        hexaOutput += " ";

        // converting binary back to characters.
        auto c = static_cast <char> (xor_operation.to_ulong());
        output += c;
    }

    cout << endl;
    cout << "Output: " << endl;
    cout << "- Plain text: " << output << endl;
    cout << "- Hexa: " << hexaOutput << endl << endl;
}

void Encryption::vignere_encryption(string message){
    int ascii1 = 0, ascii2 = 0;
    string keyWordInput, keyWord, encrypted;
    char  encoding;
    encrypted = "";

    while(message.length() > 80){
        cout << "Invalid message. Messages cannot be more than 80 characters, try again";
        cout << "->";
        getline(cin, message);
    }

    cout << "Welcome to vignere Cipher, A key of 1 - 8 letters is required." << endl << endl;
    cout << "Enter the key word" << endl;
    cout << "->";

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, keyWordInput);

    // Checking Validity
    while(not Helpers::keyword_validity(keyWordInput)){
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            encrypted += message[i];
        }
        else{
            ascii1 = int(toupper(message[i]));
            ascii2 = int(toupper(keyWord[i]));
            encoding = char(((ascii2 + ascii1) % 26) + 65);
            encrypted += encoding;
            counter++;
        }
    }
    cout << "Encrypted message: " << encrypted << endl << endl;
}

void Encryption::encryptAffineCipher(const string& text) {
    // Check if the input text contains only letters and spaces
    bool valid_input = all_of(text.begin(), text.end(), [](char c) { return isalpha(c) || c == ' '; });
    if (!valid_input) {
        cout << "Input text contains non-letter characters other than spaces. Encryption cannot be performed." << endl;
        return;
    }
    // Map to store the affine characters
    map<char, int> affine_map = {
            {'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4},
            {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9},
            {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14},
            {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19},
            {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24},
            {'z', 25}
    };

    // Map to store the reverse mapping for decryption
    map<int, char> reverse_affine_map;
    for (const auto& pair : affine_map) {
        reverse_affine_map[pair.second] = pair.first;
    }
    // set variables
    string clear_text, cipher_text;
    int a, b, result;

    // Input loop for obtaining valid values of a and b
    while (true) {
        cout << "Enter (a, b): ";
        cin >> a >> b;

        // Check if both a and b are positive integers
        if (a > 0 && b > 0) {
            break; // Exit the loop if both are valid
        } else {
            cout << "Please enter positive numbers only." << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }
    // Process the input text
    for (char i : text) {
        if (isalpha(i)) {
            clear_text += tolower(i); // Convert to lowercase
        }
    }

    // Apply the affine cipher and build the cipher text
    for (char i : clear_text) {
        result = (a * affine_map[i] + b) % 26;
        cipher_text += toupper(reverse_affine_map[result]); // Convert to uppercase
    }

    cout << "Cipher text: " << cipher_text << endl << endl;
}

void Encryption::polybius_square_encryption(const string& message){
    // App data
    char poly[6][6] = {{' ', ' ', ' ', ' ', ' ', ' '},
                       {' ', 'A', 'B', 'C', 'D', 'E'},
                       {' ', 'F', 'G', 'H', 'I', 'K'},
                       {' ', 'L', 'M', 'N', 'O', 'P'},
                       {' ', 'Q', 'R', 'S', 'T', 'U'},
                       {' ', 'V', 'W', 'X', 'Y', 'Z'}};

    string keyInput;
    cout << "Welcome to the polybius cipher, A key of numbers from 1 to 5 in any order is required" << endl << endl;
    cout << "Enter the key: " << endl;
    cout << "->";
    cin >> keyInput;

    while (!Helpers::poly_key_validity(keyInput)){
        cin >> keyInput;
    }

    // Assigning keyInput to the poly square
    string key = " ";
    key += keyInput;

    for (int i = 0; i < 6; ++i) {
        poly[0][i] = key[i];
        poly[i][0] = key[i];
    }

    string encrypted;
    encrypted = "";

    // Main cipher loop.
    for (auto ch : message){
        if (not isalpha(ch)){
            encrypted += ch;
        }
        for (int i = 1; i < 6; ++i) {
            for (int j = 1; j < 6; ++j) {
                if (toupper(ch) == poly[i][j]){
                    encrypted += poly[i][0];
                    encrypted += poly[0][j];
                }
            }
        }
    }
    cout << "Encrypted message -> " <<encrypted << endl << endl;
}

void Encryption::route_cipher_encryption(const string& sentence_to_encrypt){

    // Explain to the user what he needs to do in order to encrypt the text.
    cout << "Welcome to the route cipher encryptedText in order to encrypt some text you need to choose a secret key" << endl << endl;

    int secretKey = Helpers::route_key_validity();            // getting the secret key and checking its validity.

    int characterCounter = 0;                        // this counter will help create the matrix of the cipher.
    // stripping the text from any spaces.
    string strippedSentence = Helpers::strip(sentence_to_encrypt);

    // calculating the number of rows in the matrix.
    int nRows = ceil(static_cast<float>(strippedSentence.length()) / static_cast<float>(secretKey));
    string cipherMatrix[nRows][secretKey];

    // filling the matrix with the character of the text.
    for(int i = 0; i < nRows; i++){
        for (int j = 0; j < secretKey; j++){
            if(characterCounter < strippedSentence.length()){
                cipherMatrix[i][j] = strippedSentence[characterCounter];
                characterCounter++;
            }
                // filling the rest of the matrix with x's.
            else {
                cipherMatrix[i][j] = "x";
            }
        }
    }

    // the rest of the function is for the spiral iteration.
    // there is a pattern in the iteration, you go down then left then up then right and repeat,
    // all inside the 2d array(matrix).
    int direction = 0;          // creating a direction variable to switch between directions.

    // four variables to indicate the start from each direction.
    int startDown = nRows - 1;
    int startUp = 0;
    int startRight = secretKey - 1;
    int startLeft = 0;

    string encryptedSentence;
    int counter = 0;            // the counter to stop the spiral iteration when done.

    while(counter < secretKey * nRows){
        if(direction == 0){ // direction 0 means going down in the matrix.
            // the start point is the top right corner [startUp][startRight].
            // while going down we are moving in the most right column (startRight)
            // and change the row index from 0(startUp) to (startDown).
            for (int i = startUp; i <= startDown; i++){
                encryptedSentence += cipherMatrix[i][startRight];
                counter++; // increasing the counter to stop the while loop.
            }
            startRight--; // changing the startRight value, so we don't get the same column when going down again.
            direction = 1; // changing the direction as planned in the iteration pattern.
        }
            // all the other loops work with the same logic.

        else if (direction == 1){       // direction 1 means going left in the matrix.
            for (int i = startRight; i >= startLeft; i--){
                encryptedSentence += cipherMatrix[startDown][i];
                counter++;
            }
            startDown--;
            direction = 2;
        }

        else if (direction == 2){       // direction 2 means going up in the matrix.
            for (int i = startDown; i >= startUp; i--){
                encryptedSentence += cipherMatrix[i][startLeft];
                counter++;
            }
            startLeft++;
            direction = 3;
        }

        else if (direction == 3){       // direction 3 means going right in the matrix.
            for (int i = startLeft; i <= startRight; i++){
                encryptedSentence += cipherMatrix[startUp][i];
                counter++;
            }
            startUp++;
            direction = 0;
        }
    }

    cout << encryptedSentence << endl << endl; // printing the encrypted text.

}

void Encryption::morse_code_cipher(const string& text) {
    // set morse map
    map <char , string>  morse_cipher = {
            {'a' , ".-"}, {'b' , "-..."}, {'c' , "-.-."} ,{'d' , "-.."} , {'e',"."} ,
            {'f' , "..-." },{'g' , "--."} , {'h',"...."},{'i',".."}, {'j',".---"} , {'k',"-.-" },
            {'l',".-.."},{'m',"--"},{'n' , "-."},{'o',"---"},{'p',".--."},{'q',"--.-"},
            {'r' , ".-."} , {'s' , "..."} , {'t' , "-" } , {'u',"..-" } , {'v',"...-" } , {'w',".--" } ,
            {'x' , "-..-" } , {'y',"-.--" } , {'z',"--.."},{'1',".----"},{'2',"..---"},{'3',"...--"},
            {'4',"....-"},{'5',"....."},{'6',"-...."},{'7',"--..."},{'8',"---.."},{'9',"----."},{'0',"-----"} } ;
    // set main variables
    string clear_text , cipher_text;
    cipher_text = "" ;
    // check input validation
    for (char i : text)
    {
        // clear text to contain only letters and numbers
        if(isalpha(i) || isdigit(i)){
            clear_text += tolower(i) ;
            // If the character is a space
        } else if (i == ' ') {
            // Add a space to the clear_text directly
            clear_text += " ";
        }
    }
    // collect char
    for (char i : clear_text)
    {
        if (i == ' ') {
            cipher_text += "   "; // Add three spaces for word separation
        } else {
            cipher_text += morse_cipher[i]; // Add Morse code for the current character
            cipher_text += " "; // Add one space between letters
        }
    }
    // print result
    if (cipher_text == ""){
        cout << "The entered text contains only special charcters can not ciphered ,pls enter letters or numbers. "<< endl << endl;
    } else

        cout <<"ciphered text : " <<cipher_text << endl << endl;
}

void Encryption::rail_Fence_Encrypt(const string& message) {
    // check validation of the entered text contain letters to cipher and ignore others
    int letter_count = count_if(message.begin(), message.end(), [](char c) {
        return isalpha(c);
    });
    if (letter_count == 0) {
        cout << "Input text must contain at least one letter. Encryption cannot be performed." << endl;
        return;
    }
    // set main variables
    string clear_text = message,text, key, encryptedText;
    int num;
    // this loop to clear text from non-alphabetic letters before start
    for (char i : clear_text) {
        if (isalpha(i)){
            text += i ;
        }
    }
    // print welcome message
    cout << "welcome to Rail Fence encrypt program " << endl;

    // let user select the key
    cout << "please choose the key 3 or 4 :  " ;
    cin.ignore();
    getline(cin , key ) ;

    //check validation of key
    while (key != "3" && key != "4") {
        cout << "Invalid key. Please choose the key 3 or 4: ";
        getline(cin, key);
    }
    num = stoi(key);
    if (num == 3) {
        // make 3 lists
        vector <char> list1 , list2 , list3;
        // make first list to collect the first row by adding 4 each loop
        for (int i = 0; i < text.length() ; i+=4) {
            list1.push_back(text[i]);
        }
        // make second to collect second row by adding 2 each loop
        for (int j = 1 ; j < text.length(); j+=2) {
            list2.push_back(text[j]);
        }
        // make third to collect third row by adding 4 each loop
        for (int y = 2; y < text.length(); y+=4) {
            list3.push_back(text[y]);
        }
        // print the result of three lists
        cout << "Cipher text : ";
        for (char c : list1) {
            cout << c;
        }
        for (char c : list2) {
            cout << c;
        }
        for (char c : list3) {
            cout << c;
        }
        cout << endl;
    }
    else if (num == 4) {
        // make 4 lists
        vector <char> list1 , list2 , list3 , list4 ;
        // first to collect first row by adding 6 each loop
        for (int i = 0; i < text.length() ; i+=6) {
            list1.push_back(text[i]);
        }
        // second one to collect second row
        // but flag to iterate each loop between 4 , 2
        bool addFour = true;
        for (int j = 1; j < text.length();) {
            list2.push_back(text[j]);
            // here add 4 first time
            if (addFour) {
                j += 4;
                // and 2 in second time
            } else {
                j += 2;
            }
            addFour = !addFour; // Toggle the flag
        }
        // third one to collect third row
        // but flag to iterate each loop between 2 , 4
        bool addTwo = true ;
        for (int y = 2 ; y < text.length(); ) {
            list3.push_back(text[y]);
            // here add 2 first time
            if (addTwo) {
                y += 2;
                // and 4 in second time
            } else {
                y += 4;
            }
            addTwo = !addTwo; // Toggle the flag
        }
        // fourth one to collect last row by adding 6 each loop
        for (int u = 3; u < text.length(); u+=6) {
            list4.push_back(text[u]);
        }
        // print the result of four lists
        cout << "Cipher text : ";
        for (char c : list1) {
            cout << c;
        }
        for (char c : list2) {
            cout << c;
        }
        for (char c : list3) {
            cout << c;
        }
        for (char c : list4) {
            cout << c;
        }
        cout << endl;

    }
}

void Encryption::simple_sub_encryption(const string& textToEncrypt){
    // Welcome message with explanation
    cout << "Welcome to the simple substitution encryption, in order to get your text encrypted you need to enter a secret key" << endl;
    cout << "the key is any sequence of alphabetic characters (maximum 25 character)" << endl;
    string key, encryptedText;
    encryptedText = "";
    string alpha = "abcdefghijklmnoprqstuvwxyz";
    int encryptionIndex;

    cout << "please enter a secret key: ";
    cin >> key;
    key = Helpers::lower_case(key);

    // Checking validity
    while (!(Helpers::simpleSub_Key_Validity(key))){
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (Helpers::simpleSub_Key_Validity(key)) {
        if (key.length() < 25) {
            // If key length is less than 25, complete the key with remaining alphabet characters
            key = Helpers::complete_simple_sub_Key(key);
        }
        for (char i : textToEncrypt) {
            if (isalpha(i)){
                // Find index of character in the alphabet
                encryptionIndex = alpha.find(tolower(i));
                // Encrypt the character using the key
                encryptedText += key[encryptionIndex];
            }
            else{
                // If character is not an alphabet, add it to the encrypted text
                encryptedText += i;
            }
        }
    }
    cout << encryptedText << endl << endl;
}

void Encryption::atbash_encryption(string textToEncrypt){
    // explain the cipher to the user.
    cout << "Welcome to atbash encryption, in order to get some text encrypted you need to enter a secret key" << endl;
    cout << "valid keys are (2, 4)" << endl;
    string key, encryptedText;
    encryptedText = "";

    cout << "please enter a secret key: ";
    cin >> key; // get the key form user.

    while (!Helpers::atbash_key_validity(key)){ // check the validity of the key (if not valid ask the user to input it again).
        cout << "please enter a valid key" << endl;
        cin >> key;
    }

    if (key == "2"){ // if the key is "2", split the alphabet to two halfs.
        string firstAlpha = "ABCDEFGHIJKLM", secondAlpha = "ZYXWVUTSRQPON";
        for (char i : textToEncrypt){ // iterate through each character of the text.
            if (isalpha(i)){ // if the character is alpha search for it in one of the halfs and get its index.
                if (int(toupper(i)) <= 77){
                    int letterIndex = firstAlpha.find(toupper(i));
                    // add the same index from the other half.
                    encryptedText += secondAlpha[letterIndex];
                }
                else{
                    int letterIndex = secondAlpha.find(toupper(i));
                    encryptedText += firstAlpha[letterIndex];
                }
            }
            else{// if the character is not alpha leave it as it is.
                encryptedText += i;
            }
        }

    }
    else if (key == "4"){ // if the key is "4", split the alphabet to four parts.
        // the same logic goes for the key "4" as in the key "2".
        string firstAlpha = "ABCDEF", secondAlpha = "MLKJIH", thirdAlpha = "NOPQRS", fourthAlpha = "ZYXWVU";
        for (int i = 0; i < textToEncrypt.length(); i++){
            if (isalpha(textToEncrypt[i])){
                if (int(toupper(textToEncrypt[i])) > 84){
                    int letterIndex = fourthAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += thirdAlpha[letterIndex];
                }
                else if (int(toupper(textToEncrypt[i])) == 84){
                    encryptedText += "T";
                }
                else if (int(toupper(textToEncrypt[i])) > 77){
                    int letterIndex = thirdAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += fourthAlpha[letterIndex];
                }
                else if (int(toupper(textToEncrypt[i])) > 71){
                    int letterIndex = secondAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += firstAlpha[letterIndex];
                }
                else if (int(toupper(textToEncrypt[i])) == 71){
                    encryptedText += "G";
                }
                else if (int(toupper(textToEncrypt[i])) < 71){
                    int letterIndex = firstAlpha.find(toupper(textToEncrypt[i]));
                    encryptedText += secondAlpha[letterIndex];
                }
            }
            else{
                encryptedText += textToEncrypt[i];
            }

        }

    }
    cout << encryptedText << endl << endl;
}
