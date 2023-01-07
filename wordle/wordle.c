#include <cs50.c>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   2
#define YELLOW  6
#define RED     12
#define RESET   15

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[], HANDLE hConsole);

int main(int argc, string argv[])
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // ensure proper usage
    // TODO #1
    // checks if usage is correct
    if (argc != 2)
    {
        printf("usage: ./wordle wordsize\n");
        return 1;
    }

    int wordsize = 0;

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2
    // checks if word size is within range
    if (!(strcmp(argv[1], "5")) && !(strcmp(argv[1], "6")) && !(strcmp(argv[1], "7")) && !(strcmp(argv[1], "8")))
    {
        printf("wordsize must be between 5 and 8\n");
        return 1;
    }
    // if its within range, input the wordsize to the variable wordsize as an int
    else
    {
        wordsize = (int) atoi(argv[1]);
    }

    // open correct file, each file has exactly LISTSIZE words
    char wl_filename[6];
    sprintf(wl_filename, "%i.txt", wordsize);
    FILE *wordlist = fopen(wl_filename, "r");
    if (wordlist == NULL)
    {
        printf("Error opening file %s.\n", wl_filename);
        return 1;
    }

    // load word file into an array of size LISTSIZE
    char options[LISTSIZE][wordsize + 1];

    for (int i = 0; i < LISTSIZE; i++)
    {
        fscanf(wordlist, "%s", options[i]);
    }

    // pseudorandomly select a word for this game
    srand(time(NULL));
    string choice = options[rand() % LISTSIZE];

    // allow one more guess than the length of the word
    int guesses = wordsize + 1;
    bool won = false;

    // print greeting, using ANSI color codes to demonstrate
    SetConsoleTextAttribute(hConsole, GREEN);
    printf("This is WORDLE50\n");
    SetConsoleTextAttribute(hConsole, RESET);
    printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);

    // main game loop, one iteration for each guess
    for (int i = 0; i < guesses; i++)
    {
        // obtain user's guess
        string guess = get_guess(wordsize);

        // array to hold guess status, initially set to zero
        int status[wordsize];

        // set all elements of status array initially to 0, aka WRONG
        // TODO #4

        for (int x = 0; x < wordsize; x++)
        {
            status[x] = 0;
        }

        // Calculate score for the guess
        int score = check_word(guess, wordsize, status, choice);

        printf("Guess %i: ", i + 1);

        // Print the guess
        print_word(guess, wordsize, status, hConsole);

        // if they guessed it exactly right, set terminate loop
        if (score == EXACT * wordsize)
        {
            won = true;
            break;
        }
    }

    // Print the game's result
    // TODO #7
    if (won)
    {
        printf("you won!\n");
        return 0;
    }
    // that's all folks!
    printf("hard luck next time\n");
    printf("guess was: %s\n", choice);
    return 0;
}

string get_guess(int wordsize)
{
    string guess = "";

    // ensure users actually provide a guess that is the correct length
    // TODO #3
    string input = "";
    input = get_string("","guess: ");
    while (strlen(input) != wordsize)
    {
        input = get_string("","Input a 5-letter word: ");
    }
    *input = tolower(*input);
    guess = input;
    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5
    for (int i = 0; i < wordsize; i++)
    {
        for (int j = 0; j < wordsize; j++)
        {
            if (guess[i] == choice[j])
            {
                if (i == j)
                {
                    score = score + 2;
                    status[i] = 2;
                    break;
                }

                else
                {
                    status[i] = 1;
                    score++;
                }
            }
        }
    }

    // HINTS
    // iterate over each letter of the guess
    // iterate over each letter of the choice
    // compare the current guess letter to the current choice letter
    // if they're the same position in the word, score EXACT points (green) and break so you don't compare that letter further
    // if it's in the word, but not the right spot, score CLOSE point (yellow)
    // keep track of the total score by adding each individual letter's score from above

    return score;
}

void print_word(string guess, int wordsize, int status[], HANDLE hConsole)
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    for (int i = 0; i < wordsize; i++)
    {
        //printf("%d\n",status[i]);
        if (status[i] == 2)
        {
            SetConsoleTextAttribute(hConsole, GREEN);
            printf("%c  ", guess[i]);
        }

        else if (status[i] == 1)
        {
            SetConsoleTextAttribute(hConsole, YELLOW);
            printf("%c  ", guess[i]);
        }
        else if (status[i] == 0)
        {
            SetConsoleTextAttribute(hConsole, RED);
            printf("%c  ", guess[i]);
        }
        SetConsoleTextAttribute(hConsole, RESET);
    }
    printf("\n");
    return;
}