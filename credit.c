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
    //if size == 15 and (ftd == 34 or ftd == 37) then vendor = Amex
    //if (size == 13 or size == 16) and ftd == 4 then vendor = VISA
    //if size == 16 and (ftd == 51 or ftd == 52 or ftd == 53 or ftd == 54 or ftd == 55) then vendor = MasterCard
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
        return 1;
    }
    //else vendor = INVALID
    //printf("%ld\n",credit/temp);
}
//American Express uses 15-digit numbers, 
//MasterCard uses 16-digit numbers, 
//Visa uses 13- and 16-digit numbers
//All American Express numbers start with 34 or 37;
//most MasterCard numbers start with 51, 52, 53, 54, or 55
//all Visa numbers start with 4
