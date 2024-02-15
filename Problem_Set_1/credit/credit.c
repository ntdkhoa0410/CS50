#include <cs50.h>
#include <math.h>
#include <stdio.h>

// function declarations
void get_input();
void check_sum(long no);
void check_valid();

// variable declarations
long number;
int length = 0, sum_odd = 0, sum_even = 0, sum;
long remain, quotient;

int main(void)
{
    get_input();
    check_sum(number);
    check_valid();
}

void get_input(void)
{
    do
    {
        number = get_long("Enter card number: ");
    }
    while (number < 0);
}

void check_sum(long no)
{
    do
    {
        quotient = no / 10;
        remain = no % 10;
        length = length + 1;
        if (length % 2 != 0)
        {
            sum_odd = sum_odd + remain;
        }
        else
        {
            sum_even = sum_even + (remain * 2) % 10 + (remain * 2) / 10;
        }
        no = quotient;
    }
    while (no != 0);
    sum = sum_odd + sum_even;
}

void check_valid()
{

    if (length != 15 && length != 16 && length != 13)
    {
        printf("INVALID\n");
    }
    else if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        int startNumber = number / pow(10, length - 2);
        if ((startNumber == 34 || startNumber == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        else if ((startNumber >= 51 && startNumber <= 55) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            startNumber = number / pow(10, length - 1);
            if (startNumber == 4 && (length == 16 || length == 13))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}