# Cipher Program
## overview
The Cipher Program is a command-line utility designed to encrypt and decrypt messages using various cryptographic algorithms. 
It provides a simple and secure way to protect your sensitive information by encoding it into an unreadable format and decoding it back when needed.
## Features
* *Encryption and Decryption*: Supports both encryption and decryption of messages.
* *Multiple Algorithms*: Implements several encryption algorithms such as Polybius Square Cipher, Vigenère Cipher, and Route.
* *User-Friendly*: Easy-to-use command-line interface.
* *Customizable*: Allows users to choose different keys and settings for encryption.
## Supported Algorithms
- ### Affine Cipher
In affine cipher each letter in an alphabet is mapped to its numeric equivalent x, encrypted using a
simple mathematical function, and converted back to a letter. Letter A is given number 0 and letter
Z is given number 25. Each letter is encrypted with the function (5x + 8) mod 26. The decryption
function is 21(y − 8) mod 26. See examples at: https://cryptii.com/affine-cipher/.
- ### Route Cipher
Route Cipher is one of the simplest and most widely known encryption techniques. In this cipher, a
secret integer key is used to create a matrix whose number of columns is equal to the key and then
the message is written in as many rows as needed in this matrix. Then the encrypted message is
collected by going in a spiral path starting from the top right corner.
For example, let's encrypt a name of a city the UK, Brighton and Hove. The secret key will
be 3, and it will determine the width of the matrix. We will ignore all spaces and turn all letters to
capital. We will exclude any non-letter characters. Then we will fill the matrix row by row, from left
to right. If there are still empty cells in the matrix, we will them fill them with 'X'. Finally, we will
read the grid clockwise, going inwards, and starting from the top right corner.
The original message will be: BRIGHTONANDHOVE
The letters are then entered into the grid, which is 3-column wide: <br />
B R I <br />
G H T <br />
O N A <br />
N D H <br />
O V E <br />
Luckily, in our case, there is no need to add any additional characters at the bottom of the grid.
The letters are then read, and appended to the cipher text. The reading starts from the top right,
and spiral clockwise inwards.
Decryption involves going in the opposite process.
The produced encrypted text will be: ITAHEVONOGBRHND
Read more on: https://www.crypto-it.net/eng/simple/route-cipher.html
- ### Atbash Cipher
The Atbash cipher is a very common, simple cipher. Basically, when encoded, an "A" becomes a "Z",
"B" turns into "Y", etc. See http://rumkin.com/tools/cipher/atbash.php.
- ### Vignere Cipher
In this method, a keyword is repeatedly added character by character to each alphabetic letter in
the original message. The addition is carried out using the ASCII codes for each of the characters,
modulo 26 (the number of letters in the alphabet), and the result is added to the code for the letter
'A' in the ASCII code sequence. For example, if the original message is "due November 4" and the
keyword is "HWone", the message will be encrypted as follows: <br />
message:            DUE NOVEMBER 4 <br />
                    |||||||||||||| <br />
repeated keyword:   HWONEHWONEHWON <br />
                    |||||||||||||| <br />
encrypted message:  KQS RVRSZFLN 4 <br />

