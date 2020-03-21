#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //colected input from user
    long credit = get_long("Number: ");
    //size - the number of digits in credit card number
    int size = 0;
    long temp = credit;
    //found size
    while (temp!=0)
    {
        temp=temp/10;
        size++;
    }
    int i = size-2;
    temp = 10;
    while (i>1)
    {
        temp=temp*10;
        i--;
    }
    //ftd - first two digits
    int ftd = credit/temp;
    int luhn_sum_even = 0;
    int luhn_sum_odd = 0;
    i = 1;
    long x;
    long y;
    int digit;
    while (i<=size)
    {
        x = credit % ((long) pow(10,i));
        y = x / ((long) pow(10,(i - 1)));
        if (i % 2 != 0)
        {
            digit = y;
            luhn_sum_odd = luhn_sum_odd + digit;
            i++;
        } else {            
            digit = y * 2;
            if (digit>=10)
            {
                digit = digit % 10 + 1;
            }
            luhn_sum_even = luhn_sum_even + digit;
            i++;
        }
    }
    if ((luhn_sum_even + luhn_sum_odd) % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
       //if size == 15 and (ftd == 34 or ftd == 37) then vendor = Amex
    if (size == 15 && (ftd == 34 || ftd == 37))
    {
        printf("AMEX\n");
        return 0;
    }
       //if (size == 13 or size == 16) and ftd == 4 then vendor = VISA
    else if ((size == 13 || size == 16) && (ftd/10) == 4)
    {
        printf("VISA\n");
        return 0;
    }
    //if size == 16 and (ftd == 51 or ftd == 52 or ftd == 53 or ftd == 54 or ftd == 55) then vendor = MasterCard
    else if (size == 16 && (ftd == 51 || ftd == 52 || ftd == 53 || ftd == 54 || ftd == 55))    
    {
        printf("MASTERCARD\n");
        return 0;
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}   
