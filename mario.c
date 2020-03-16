#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    while (true)
    {  
        n = get_int("Height: ");
        if (n >= 1 && n <= 8)
        {
            break;
        }
    }
    for (int i = 0; i < n; i++)
    {
      for (int k = 0; k < (n - i - 1); k++)
      {
          printf(" ");
      }
      for (int j = 0; j < (i + 1); j++)
      {
          printf("#");
      }
      printf("\n");
    }
}
