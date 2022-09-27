/* =================================================================*
 *                  code is made by hazem shaaban                   *
 *              it is submitted to cs50 as an assignment            *
 *                                                                  *
 *     the code is made to repalce every letter in the alphabet     *
 *  with an equivalent counterpart, the key has to be made out of   *
 *  26 different alphabetical characters, meaning no repetition is  *
 *  allowed, the letter case of the key doesn't matter, and the     *
 *          ciphered text follows the case of the plain text.       *
 *                                                                  *
 * this might not be the best way to do it, but it does the job     *
 *                     for a beginner.                              */
/*==================================================================*/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
string rotation(string key, string text);
int key_check(string key);

int main(int argc, string argv[])
{
    //==========================================//
    // these are 3 checks regarding the key.
    // #1 command line must have one argument.
    // #2 length of key must be 26.
    // #3 key must contain only alphabet characters,
    //    and can't contain repeated characters.
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (key_check(argv[1]) == 1)
    {
        printf("fail");
        return 1;
    }
    //==========================================//

    string key = argv[1];
    string plaintext = get_string("plaintext: ");
    string ciphertext = rotation(key, plaintext);
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}
// this function rotates each char based on the key,
// it also retains the letter case of the plain text
//       so the key letter case has no effect
string rotation(string key, string text)
{
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            if (islower(text[i]) == 0)
            {
                text[i] = key[text[i] - 65];
                text[i] = toupper(text[i]);
            }
            else
            {
                text[i] = key[text[i] - 97];
                text[i] = tolower(text[i]);
            }
        }
    }
    return text;
}

// this function is the master of the show
// it checks if all characters are alphabet characters,
// it also checks if there is any repeated characters
int key_check(string key)
{
    int length = strlen(key);
    for (int i = 0; i < length; i++)
    {
        key[i] = toupper(key[i]);
        if ((key[i] < 'A') || (key[i] > 'Z' && key[i] < 'a') || key[i] > 'z')
        {
            return 1;
        }
        for (int n = i - 1; n >= 0; n--)
        {
            if (key[i] == key[n])
            {
                return 1;
            }
        }
    }
    return 0;
}