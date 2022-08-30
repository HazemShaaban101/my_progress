#include <stdio.h>
#include <cs50.c>

int main()
{
    int counter = 0;
    while (true)
    {
        int user_input = get_int("Height:");
        if (user_input >= 1 && user_input <= 8)
        {
            while (counter != user_input + 1)
            {
                printf("%.*s", user_input - counter, "        ");
                printf("%.*s \n", counter, "########");
                ++counter;
            }
            return 0;
        }
    }
}