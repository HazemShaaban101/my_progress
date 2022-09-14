#include <cs50.c>
#include <stdio.h>
#include <string.h>
#include <math.h>
int count_letters(char* text); int letters; int characters = 0;
int count_words(char* text); int words;
int count_sentences(char* text); int sentences;
int index_calc(float letters_no, float words_no, float sentences_no);



int main() {
    char *data = get_string("", "text: ");
    int LC = count_letters(data);
    int WC = count_words(data);
    int SC = count_sentences(data);
    index_calc(LC, WC, SC);
    printf("%d letters\n", LC);
    printf("%d words\n", WC + 1);
    printf("and %d sentences\n", SC);
}



int count_letters(char* text)
{
    characters = strlen(text);
    printf ("%d\n", characters);
    letters = 0;
    for (int i = 0; i < characters; i++)
    {
        if (((text[i] < 91) && (text[i] > 64)) || ((text[i] < 123) && (text[i] > 96)))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(char* text)
{
    words = 0;
    for (int i = 0; i < characters; i++)
    {
        if ((text[i] != ' ') && (text[i + 1] == ' '))
        {
            words++;
        }
    }
    return words;
}

int count_sentences(char* text)
{
    sentences = 0;
    for (int i = 0; i < characters; i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences++;
        }
    }
    return sentences;
}

int index_calc(float letters_no, float words_no, float sentences_no)
{
    float L = (letters_no / words_no) * 100;
    float S = (words_no / sentences_no) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    //index = round(index);
    if (index < 1)
    {
        printf ("Before Grade 1\n %d\n", index);
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}