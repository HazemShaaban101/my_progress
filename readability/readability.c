/* =================================================================*
 *                  code is made by hazem shaaban                   *
 *              it is submitted to cs50 as an assignment            *
 *                                                                  *
 *     this code determines the reading level of a paragraph of     *
 *              using the equation of Coleman-Liau index.           *
 *                                                                  *
 * this might not be the best way to do it, but it does the job     *
 *                     for a beginner                               */
/*==================================================================*/



#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
int count_letters(char *text);
int letters;
int characters = 0;
int count_words(char *text);
int words;
int count_sentences(char *text);
int sentences;
int index_calc(float letters_no, float words_no, float sentences_no);



int main(void)
{
    char *data = get_string("text: ");
    int LC = count_letters(data);
    int WC = count_words(data);
    int SC = count_sentences(data);
    index_calc(LC, WC, SC);
    //printf("%d letters\n", LC);
    //printf("%d words\n", WC + 1);
    //printf("and %d sentences\n", SC);
    return 0;
}


//function counts the number of characters and letters in string
// and returns the letter count
int count_letters(char *text)
{
    characters = strlen(text);
    //printf("%d\n", characters);
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

//function counts the amount of words in the string
//                by counting spaces.
int count_words(char *text)
{
    words = 0;
    for (int i = 0; i < characters; i++)
    {
        if ((text[i] != ' ') && (text[i + 1] == ' '))
        {
            words++;
        }
    }
    return words + 1;
}
// function counts number of sentences by counting commas
int count_sentences(char *text)
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

// function calculates index by calculating rates of letters/sentences per number of words
// and prints out an output based on the rounding of the index
int index_calc(float letters_no, float words_no, float sentences_no)
{
    float L = letters_no / words_no * 100.0;
    //printf("%.2f\n", L);
    float S = (sentences_no / words_no) * 100.0;
    //printf("%.2f\n", S);

    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int indexR = roundf(index);
    if (indexR < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (indexR > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", indexR);
    }
    return 0;
}