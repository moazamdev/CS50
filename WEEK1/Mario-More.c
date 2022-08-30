#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while(true)
    {
        int n = get_int("Enter number: ");
        if(n > 0 && n < 9)
        {
            for (int i = 0; i < n; i++) {
                // print spaces
                for (int j = 1; j < n - i; j++) {
                    printf(" ");
                }
                // print stars
                for (int k = 0; k <= i; k++) {
                    printf("#");
                }
                printf("  ");
                for (int j = 0; j <= i; j++) {
                    printf("#");
                }
                printf("\n");
            }
            break;
        }
    }
}