#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    // for player 1
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    // for player 2
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    // if both scores are same
    else
    {
        printf("Tie!\n");
    }
}

// function for calculating score
int compute_score(string word)
{
    // declaring and initializing variables
    int score = 0, len = strlen(word);
    // loop is for iterating over the characters of the word
    for (int i = 0; i < len; i++)
    {
        // if the character is in uppercase
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        // if the character is in lowercase
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }
    // after calculating the score, returning it
    return score;
}



