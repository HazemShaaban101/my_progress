#include <stdio.h>
#include <cs50.c>
#include <stdlib.h>


int main()
{
    char *key = get_string("", "");


    if ((strlen(key) <= 2) && (key[0] <= 57) && (key[0] >= 48) && (key[1] <= 57) && (key[1] >= 48))
    {
       char *text = get_string("", "plaintext: ");
        int length = strlen(text);
        key = atoi(key);
        printf("%i", key);
        for (int i = 0; i <= length; i++) {
            if ((text[i] >= 65) && (text[i] <= 90)) {
                text[i] = text[i] + key;
                if (text[i] > 90) {
                    text[i] = text[i] - 26;
                }
            }
            else if ((text[i] >= 97) && (text[i] <= 122)) {
                if (text[i] + key > 122) {
                    text[i] = text[i] - 26;
                    text[i] = text[i] + key;
                }
                else
                {
                    text[i] = text[i] + key;
                }
            }
        }
        printf("ciphertext: %s", text);
    }
    else
    {
        printf("Usage: ./caesar key");
    }

        return 0;
}
