#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name andc vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // looping through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if name matches with the candidate than increment the vote of the matched candidate and return true
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }
    // otherwise if the name does not matches than return false to print the msg 'Invalid vote'
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // initializing a temp variable for storing the maximum vote number
    int temp_count = 0;
    // looping through the candidates to get the highest vote and storing it in temp variable
    for (int i = 0; i < candidate_count; i++)
    {
        if (temp_count < candidates[i].votes)
        {
            temp_count = candidates[i].votes;
        }
    }
    // looping through the candidates to print the name of candidates than got highest vote
    for (int i = 0; i < candidate_count; i++)
    {
        if (temp_count == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}