#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while(true){
        int n = get_int("Height: ");
        if(n > 0 && n <= 8)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = i; j < n; j++)
                {
                    printf(" ");
                }
                for (int k = 1; k <= i; k++)
                {
                    printf("#");
                }
                printf ("\n");
            }
            break;
        }
    }
}