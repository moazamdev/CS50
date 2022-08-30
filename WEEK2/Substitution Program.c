#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // counting the cmnd arguments, if they are not correct then print usage msg and return 1
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // storing the key argument for later use
    string key = argv[1];
    // calculating the length of key
    int len = strlen(key);
    // checking if the key contains only alphabets, if not then print msg and return 1
    for (int i = 0; i < len; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }
    }
    // checking if the key contains repeated characters, if it has then print msg and return 1
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if ((i != j) && key[i] == key[j])
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }
    // checking if the key contains 26 characters, if not then print msg and return 1
    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // getting plaintext from user
    string pt = get_string("plaintext: ");
    printf("ciphertext: ");
    // calculating length of plaintext
    int ptlen = strlen(pt);

    // loop will run for length of the plaintext
    for (int i = 0; i < ptlen; i++)
    {
        // if the character is uppercase than map it with its key character
        if (isupper(pt[i]))
        {
            printf("%c", (toupper(key[pt[i] - 'A'])));
        }
        // if the character is lowercase than map it with its key character
        else if (islower(pt[i]))
        {
            printf("%c", (tolower(key[pt[i] - 'a'])));
        }
        // if the character is not a alphabet than print it same
        else
        {
            printf("%c", pt[i]);
        }
    }
    printf("\n");
    return 0;
}