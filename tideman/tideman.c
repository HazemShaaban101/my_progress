#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool circle(int i, int loser);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    if (pair_count < 1)
    {
        printf("failed! no pairs");
        return;
    }
    int strength[pair_count];
    for (int i = 0; i < pair_count; i++)
    {
        strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }
    for (int i = 0; i < pair_count; i++)
    {
        int counter = 0;
        for (int j = 0; j < pair_count - 1; j++)
        {
            if (strength[j] < strength[j + 1])
            {
                pair cached = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = cached;

                int floating = strength[j];
                strength[j] = strength[j + 1];
                strength[j + 1] = floating;
            }
            else
            {
                counter++;
            }
        }
        if (counter == pair_count - 1)
        {
            //printf ("sorted\n");
            break;
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (!circle(i, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}
// check if there is a circle in this pair
bool circle(int i, int loser)
{
    for (int j = i; j > 0; j--)
    {
        if (locked[pairs[j].winner][pairs[j].loser])
        {
            if (loser == pairs[j].winner)
            {
                return true;
            }
        }
    }
    return false;
}
// Print the winner of the election
void print_winner(void)
{
    //I honestly don't know why it doesn't print the winner when there is a loop
    // what a waste of time

    // this counts the times a candidate won over another candidate
    int counter[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[i][j] == true)
            {
                counter[i]++;
            }
        }
    }
    // this finds out who won most times
    int biggest = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (counter[i] > biggest)
        {
            biggest = counter[i];
        }
    }
    // this prints whoever won the most times
    for (int i = candidate_count - 1; i >= 0; i--)
    {
        if (counter[i] == biggest)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
    return;
}