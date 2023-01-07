
#include <stdio.h>
#include <string.h>
#include <cs50.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string input = get_string("Message: ");
    unsigned long long letter_count = strlen(input);
    //printf("letter count: %d\n", letter_count);
    int bitmap[letter_count][8];

    for (int i = 0; i < letter_count; i++)
    {
        int buffer = input[i];
        //printf("%d\n", buffer);
        for (int j = 7; j >= 0; j--)
        {
            bitmap[i][j] = buffer % 2;
            buffer = buffer / 2;
        }
    }

    for (int i = 0; i < letter_count; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            print_bulb(bitmap[i][j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
