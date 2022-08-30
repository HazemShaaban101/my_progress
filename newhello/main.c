#include "cs50.c"

int main()
{
    string answer;
    answer = get_string((va_list *) "", "whats your name? ");
    printf("Hello, %s\n", answer);
    return 0;
}

