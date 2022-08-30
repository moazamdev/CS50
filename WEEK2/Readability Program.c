#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

// decalring function headers
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// decalring a global variable to avoid repetition
int count;

int main(void)
{
    // getting value from user
    string para = get_string("Text: ");

    // calling functions and storing values
    int letters = count_letters(para);
    int words = count_words(para);
    int sentences = count_sentences(para);

    // type conversion and calculating L, S and index
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences / (float) words * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // printing the grade
    if (index < 1) printf("Before Grade 1\n");
    else if (index > 16) printf("Grade 16+\n");
    else printf("Grade %i\n", index);
}

// function for counting only alphabetical letters
int count_letters(string text)
{
    count = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}
// function for counting words
int count_words(string text)
{
    count = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if (i == 0)
        {
            count++;
        }
        else if (text[i - 1] == ' ')
        {
            count++;
        }
    }
    return count;
}
// function for counting sentences ending on . ! ?
int count_sentences(string text)
{
    count = 0;
    for(int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}