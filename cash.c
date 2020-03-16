#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float n;
    while (true)
    {
        n = get_float("How much change? ");
        if (n >= 0) 
        {
            break;
        }
    }
    int coins = round(n * 100);
    int change = 0;
    while (coins != 0)
    {
        if (coins >= 25)
        {
            coins = coins - 25;
            change = change + 1;
        }
        else if (coins >= 10)
        {
            coins = coins - 10;
            change = change + 1;
        }
        else if (coins >= 5)
        {
            coins = coins - 5;
            change = change + 1;
        }
        else if (coins >= 1)
        {
            coins = coins - 1;
            change = change + 1;
        }
    } 
    printf("%i\n", change);
}
