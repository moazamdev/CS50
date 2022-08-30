#include <cs50.h>
#include <stdio.h>

// declaring collatz function
int collatz(int n);
int main(void)
{
    // getting a number from user
    int n = get_int("Enter positive integer: ");
    // checking if the number is positive
    if(n > 0)
    {
        // if number is positive than call the function and print the value
        printf("Steps: %i\n", collatz(n));
    }
}

// defining the function body
int collatz(int n)
{
    // setting the base case
    if (n == 1)
    {
        return 0;
    }
    // if the number is even
    else if ((n % 2) == 0)
    {
        return 1 + collatz(n / 2);
    }
    // if the number is odd
    else
    {
        return 1 + collatz((3 * n) + 1);
    }

}