#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void)
{
    // declaring and initializing variables
    int firstSum = 0, checkSum = 0, pwt, soit, i, mod = 10;
    long fDivide = 10, sDivide = 1, cardNum;

    // getting value from user
    cardNum = get_long("Enter credit card number: ");

    // calculating length of the input
    int length = floor(log10(labs(cardNum))) + 1;

    // calculating first sum
    for(i = 1; i <= length; i++)
    {
        // pwt = product with two
        pwt = (2 * ((cardNum / fDivide) % mod));
        // soit = sum of individual terms
        soit = (pwt / 10) + (pwt % 10);
        firstSum += soit;
        fDivide *= 100;
    }

    // calculating checksum sum
    for(i = 1; i <= length; i++)
    {
        // pwt = product with two
        pwt = ((cardNum / sDivide) % mod);
        checkSum += pwt;
        sDivide *= 100;
    }
    checkSum += firstSum;

    // checking the last digit of the checksum
    if(checkSum % 10 == 0)
    {
        if(length == 15)
        {
            // AMEX CARD
            if((cardNum / 10000000000000) == 34 || (cardNum / 10000000000000) == 37)
            {
                printf("AMEX\n");
            }
            // INVALID
            else
            {
                printf("INVALID\n");
            }
        }
        else if(length == 16)
        {
            // MASTER CARD
            if((cardNum / 100000000000000) >= 51 && (cardNum / 100000000000000) <= 55)
            {
                printf("MASTERCARD\n");
            }
            // VISA
            else if((cardNum / 1000000000000000) == 4)
            {
                printf("VISA\n");
            }
            // INVALID
            else
            {
                printf("INVALID\n");
            }
        }
        else if(length == 13)
        {
            // VISA CARD
            if((cardNum / 1000000000000) == 4)
            {
                printf("VISA\n");
            }
            // INVALID
            else
            {
                printf("INVALID\n");
            }
        }
        // INVALID
        else
        {
            printf("INVALID\n");
        }

    }
    // INVALID
    else
    {
        printf("INVALID\n");
    }
}