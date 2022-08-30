#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// declaring function for rotating a character at a time
char rotate(char c, int n);

// declaring function to validating the command line arguments
bool only_digits(string c);

int main(int argc, string argv[])
{
    // counting cmnd line arguments and calling a function with a return type of bool in the condition
    if (argc == 2 && only_digits(argv[1]))
    {
	    // converting the key from string to int
        int key = atoi(argv[1]);
	    // taking plaintext from the user
        string pt = get_string("plaintext: ");
	    // calculating the length of the plaintext
        int len = strlen(pt);
        printf("ciphertext: ");
	    // for loop to call rotate function on the current index and printing back the result (encrypted character) using printf function, this for loop calls function for one digit at a time
        for (int i = 0; i < len; i++)
        {
            printf("%c", rotate(pt[i], key));
        }
	    // printing new line after the word is printed completely
        printf("\n");
    }
    else
    {
	    // printing the usage msg if the cmnd line arguments are not correct
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
bool only_digits(string c)
{
    // calculating the length of 2nd argument of the command
    int len = strlen(c);
    // checking if the character is a digit or not
    for(int i = 0; i < len; i++)
    {
        if (!isdigit(c[i]))
        {
            // if it is not a digit returning the false which will print the usage msg
            return false;
        }
    }
    // otherwise continue the program
    return true;
}

char rotate(char c, int n)
{
    // if the character is uppercase then calculating its decimal value and return it back to the main
    if(isupper(c))
    {
        return ((c + n - 65) % 26 + 65);
    }
    // if the character is lowercase then calculating its decimal value and return it back to the main
    else if(islower(c))
    {
        return ((c + n - 97) % 26 + 97);
    }
    // if it is not an aphabetical character then print it same
    else
    {
        return c;
    }
}
