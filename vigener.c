#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // checking if number of provided argument is right, if not - exit
    if (argc != 2) {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    // checking if a single argument consists of letters, if not - exit
    for (int i=0, n=strlen(argv[1]); i < n; i++) {
        if (!((argv[1][i] >= 65 && argv[1][i] <= 90) || (argv[1][i] >= 97 && argv[1][i] <= 122))) {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }
    // asking user to provide plaintext string
    string plaintext = get_string("plaintext:  ");
    // setting variables for further calculations
    int p_char, c_char, k_char, l_boundary_plaintext, l_boundary_keyword, key;
    int p_len = strlen(plaintext);
    int k_len = strlen(argv[1]);
    // setting start of output
    printf("ciphertext: ");
    // cycling through each character of provided plaintext to turn it into ciphertext
    int i=0, n=strlen(plaintext), j=0, k=0;
    while (i<n) {
    // for (int i=0, n=strlen(plaintext), j=0; i<n; i++) {
        // variable which contains current plain-text char
        p_char = (int) plaintext[i];
        // variable which contains current keyword char
        k_char = (int) argv[1][j];
        // checking if char belongs to upper-case letters
        if (p_char >= 65 && p_char <= 90) {
            l_boundary_plaintext = 65;
        // checking if char belongs to lower-case letters
        } else if (p_char >= 97 && p_char <= 122) {
            l_boundary_plaintext = 97;
        // if char is a symbol, then printing it as it is
        } else {
            printf("%c", p_char);
            i++;
            continue;
        }
        // checking if keyword char belongs to lower-case letters
        if (k_char <= 90) {
            l_boundary_keyword = 65;
        } else {
            l_boundary_keyword = 97;
        }
        // getting integer key from keyword character
        key = ((int) argv[1][j]) - l_boundary_keyword;
        // calculating ciphertext char
        // Using formula: start_of_ascii_offset + (position_of_char - start_of_ascii_offset + cipher_key) % number_of_letters_in_latin_alphabet
        c_char = l_boundary_plaintext + (((p_char - l_boundary_plaintext) + key) % 26);
        printf("%c", c_char);
        // printf("i - %i, j - %i, p_char - %i, k_char - %i, key - %i\n", i, j, p_char, k_char, key);
        // setting position of keyword character for next cycle
        i++;
        k++;
        if (k >= (k_len - 1)) {
            j = k % k_len;
        } else {
            j++;
        }
    }
    printf("\n");
    return 0;
}
