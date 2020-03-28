#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // checking if number of provided argument is right, if not - exit
    if (argc != 2) {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // checking if a single argument consists of digits, if not - exit
    for (int i=0, n=strlen(argv[1]); i < n; i++) {
        if (!(isdigit(argv[1][i]))) {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // converting provided argument to integer
    int key = atoi(argv[1]);
    // asking user to provide plaintext string
    string plaintext = get_string("plaintext:  ");
    // setting variables for further calculations
    int p_char, c_char, l_boundary;
    // setting start of output
    printf("ciphertext: ");
    // cycling through each character of provided plaintext to turn it into ciphertext
    for (int i=0, n=strlen(plaintext); i<n; i++) {
        // variable which contains current plain-text char
        p_char = (int) plaintext[i];
        // checking if char belongs to upper-case letters
        if (p_char >= 65 && p_char <= 90) {
            l_boundary = 65;
        // checking if char belongs to lower-case letters
        } else if (p_char >= 97 && p_char <= 122) {
            l_boundary = 97;
        // if char is a symbol, then printing it as it is
        } else {
            printf("%c", p_char);
            continue;
        }
        // calculating ciphertext char
        // Using formula: start_of_ascii_offset + (position_of_char - start_of_ascii_offset + cipher_key) % number_of_letters_in_latin_alphabet
        c_char = l_boundary + (((p_char - l_boundary) + key) % 26);
        printf("%c", c_char);
    }
    printf("\n");
    return 0;
}
