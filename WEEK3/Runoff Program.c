#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // loop through all candidates to check if the 'name' is present in the candidates[i].name array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            // updating the preferences array, where 'i' is the index of candidate to which name is matched
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // loop through voters
    for (int voter = 0; voter < voter_count; voter++)
    {
        // loop through preference
        for (int rank = 0; rank < candidate_count; rank++)
        {
            // calculating the candidate index from preferences array
            int cand_index = preferences[voter][rank];
            // if the candidate (which we have calculated now) is not eliminated yet than increment its vote and than breaking out of the nested loop so that we can do calculation for next voters vote
            // if the candidate is not eliminated than we are checking only top preference that is at 0 index or 1st preference and once we have incremented it we are breaking out of nested loop to calculate vote for next voter
            if (!candidates[cand_index].eliminated)
            {
                candidates[cand_index].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // looping through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate's vote are greater than the half of the voters than we are declaring that candidate as a winner by printing its name and returning true
        // E.g if we have 10 voter and 3 candidates than any candidate having 6 ((10 / 2) + 1) votes is a winner
        //
        if (candidates[i].votes > (voter_count / 2))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // defining a minimum vote variable for calculating min votes
    int min_vote = candidates[0].votes;
    // looping through all the candidates and checking if our min vote variable's value is greater than any of the candidates vote, if it is than we are assigning it the lower value which is of the candidates vote from which it was greater.
    for (int i = 0; i < candidate_count; i++)
    {
        if (min_vote > candidates[i].votes && !candidates[i].eliminated)
        {
            min_vote = candidates[i].votes;
        }
    }
    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // declaring counter variable to track the number of candidates having votes equal to minimum vote and are not eliminated yet
    int count = 0;
    // declaring counter variable to track the number of candidates that are not eliminated yet and could have votes greater than minimum votes
    int run = 0;
    // looping through the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // checking if the candidates have votes equal to min vote and is not eliminated than incrementing the counter variables
        if (min == candidates[i].votes && !candidates[i].eliminated)
        {
            count++;
            run++;
        }
        // checking if the candidates is not eliminated yet
        else if (!candidates[i].eliminated)
        {
            run++;
        }
    }
    // checking if we have same number of candidates having vote equal to min vote and are not eliminated and on the other side candidates that are also not eliminated but they may have votes greater than min vote, in the end if they are same then return true
    if (count == run)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // looping through candidates to check if any candidates having votes equal to min vote and is not eliminated yet than we are going to assign it a value of true which means now it is eliminated
    for (int i = 0; i < candidate_count; i++)
    {
        if ((min == candidates[i].votes) && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}