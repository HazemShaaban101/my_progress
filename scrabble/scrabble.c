/* =================================================================*
 *                  code is made by hazem shaaban                   *
 *                it is submitted to cs50 as a lab                  *
 *                                                                  *
 *    the code calculates the score of each word, and compares      *
 *      the two scores and decides who won the scrabble game        *
 *                                                                  *
 * this might not be the best way to do it, but it does the job     *
 *                     for a beginner                               */
/*==================================================================*/

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int scores[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1,
                  1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
                 };
int compute_score(string text);



int main(void)
{
    int player1 = 0;
    int player2 = 0;

    string word1 = get_string("player 1: ");
    player1 = compute_score(word1);
    //printf("player1 score is %d\n", player1);
    string word2 = get_string("player 2: ");
    player2 = compute_score(word2);
    //printf("player2 score is %d\n", player2);

    if (player1 > player2)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1 < player2)
    {
        printf("Player 2 wins!\n");
    }
    else if (player1 == player2)
    {
        printf("Tie!\n");
    }
}


//compute score function, goes over letters of string
// one by one, and adds its value to the score total
//then returns that total.
int compute_score(string text)
{
    int score = 0;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        //adds to total only when it's and alphabet letter
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            text[i] = toupper(text[i]);
            int value = text[i];
            value = value - 65;
            //printf("%d ", scores[value]);
            score = score + scores[value];
        }
    }
    return score;
}