/* =================================================================*
 *                  code is made by hazem shaaban                   *
 *              it is submitted to cs50 as an assignment            *
 *                                                                  *
 *     the code takes in a key, and an input text, then rotates     *
 *           the letters of the input by steps equal to key         *
 *                                                                  *
 * this might not be the best way to do it, but it does the job     *
 *                     for a beginner                               */
/*==================================================================*/


#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool only_digits(string argv);
int make_key(string argv);
string rotate(int key, string text);



// main function, this makes sure the number of command lines is 1
// and reports back an error if it isn't, it also executes other functions.

int main(int argc, string argv[1])
{
    if (argc == 2)
    {
        int onlydigits = only_digits(argv[1]);
        if (onlydigits == 1)
        {
            int key = make_key(argv[1]);
            printf("key: %d\n", key);
            string plaintext = get_string("plaintext: ");
            string ciphertext = rotate(key, plaintext);
            printf("ciphertext:  %s\n", ciphertext);
            return 0;
        }
        // if there are letters in string, print error
        else if (onlydigits == 0)
        {
            return 1;
        }
    }

// if command line arguments is more than 1, print out error
    else if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}








// only_digits function checks if there is any non-numeric
// letters in the string then reports back the findings.

bool only_digits(string argv)
{
    char *rest;
    int key = strtoul(argv, &rest, 0);
    if (rest[0] != 0)
    {
        printf("Usage: ./caesar key\n");
        return 0;
    }
    else
    {
        printf("%d\n", key);
        return 1;
    }
}

//make_key function makes sure the key is always between 1 and 26,
// if it's more than that, it overflows and starts from 1 again.

int make_key(string argv)
{
    int key = atoi(argv);
    if (key > 26)
    {
        key = key - ((key / 26) * 26);
    }
    return key;
}

// rotate function changes string to its ciphered counterpart
// based on the key

string rotate(int key, string text)
{
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            if (text[i] + key > 122)
            {
                text[i] = text[i] - 26 + key;
            }
            else
            {
                text[i] = text[i] + key;
            }
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            if (text[i] + key > 90)
            {
                text[i] = text[i] - 26 + key;
            }
            else
            {
                text[i] = text[i] + key;
            }
        }
    }
    return text;
}