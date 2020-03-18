#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long credit = get_long("Number: ");
    int size = 0;
    long temp = credit;
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
    printf("%ld\n",credit/temp);
}
//American Express uses 15-digit numbers, 
//MasterCard uses 16-digit numbers, 
//Visa uses 13- and 16-digit numbers
//All American Express numbers start with 34 or 37;
//most MasterCard numbers start with 51, 52, 53, 54, or 55
//all Visa numbers start with 4
