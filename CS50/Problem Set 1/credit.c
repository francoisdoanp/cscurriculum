#include <cs50.h>
#include <stdio.h>

bool luhn_algo(long number);
int return_length(long number);
int return_first_number(long number);

int main(void)
{
    long cc_num = get_long("Number: ");
    bool valid = luhn_algo(cc_num);
    int length = return_length(cc_num);
    int first_num = return_first_number(cc_num);
    int first_num_visa = first_num/10;

    if (valid == true)
    {
        if (length == 15 && (first_num == 34 || first_num == 37))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && (first_num == 51 || first_num == 52 || first_num == 53 || first_num == 54 || first_num == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 16 || length == 13) && first_num_visa == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int return_length(long number)
{
    int count = 0;
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    return count;
}

int return_first_number(long number)
{
    int length = return_length(number);
    int first_number;

    if (length == 15)
    {
        first_number = number / 10000000000000;
    }
    else if (length == 13)
    {
        first_number = number / 100000000000;
    }
    else 
    {
        first_number = number / 100000000000000;
    }
    return first_number;
}

bool luhn_algo(long number)
{
    int sum_multp = 0;
    int sum_nomultp = 0;
    int total;
    int counter = 0;

    while (number > 0)
    {
        int value = number % 10;

        if (counter % 2 == 0)
        {
            sum_nomultp += value;
        }
        else
        {
            int value_multiplied = value * 2;
            if (value_multiplied < 10)
            {
                sum_multp += value_multiplied;
            }
            else
            {
                while (value_multiplied > 0)
                {
                    sum_multp += value_multiplied % 10;
                    value_multiplied /= 10;
                }
            }
        }
        counter++;
        number /= 10;

        total = sum_nomultp + sum_multp;
    }   
    if (total % 10 ==0)
    {
         return true;
    }
    else
    {
         return false;
    }
}
