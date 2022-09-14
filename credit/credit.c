

/*                  code is made by hazem shaaban
 *              it is submitted to cs50 as an assignment
 *
 *          the code checks the authenticity of a credit card
 *          by doing some checks on the numbers of said card
 *
 * this might not be the best way to do it, but it does the job
 *                     for a beginner*/
/*=============================================================*/


#include <stdio.h>
#include <math.h>
#include <cs50.h>
bool checksum(int length, long long card);
int typeout(int length, long long card);
long long three = 1000000000000;
long long four = 10000000000000;
long long five = 100000000000000;
long long six = 1000000000000000;

/* main function*/
int main(void)
{
    while (true)
    {
        //get card number as input
        long long card = get_long_long("Number: ");
        //calculate length using log10
        int length = log10(card) + 1;
        /*do a checksum on the card number, checksum function
         * takes card number and length of that number*/
        if (checksum(length, card) == true)
        {
            /*if checksum clears, use typeout function to determine type of card
             * this also takes card number and length*/
            typeout(length, card);
        }
        else
        {
            //if checksum doesnt clear, print INVALID
            printf("INVALID\n");
        }
        return 0;
    }
}

/* checksum function, it first makes an array of chars, then puts each digit into an array cell
 * then does some math to do the checksum*/
bool checksum(int length, long long card)
{
    //make array with cells equal to number of digits in card
    char *arr = calloc(length, sizeof(char));
    int sum = 0;
    //transfer digits into array cells
    for (int i = 1; i <= length; i++, card /= 10)
    {
        //if cell is even, multiply it by two, if its more than
        // 9 it divides it into the sum of the two digits instead
        //if its odd, it just leaves it as it is
        if (i % 2 == 0)
        {
            arr[i] = (card % 10) * 2;
            if (arr[i] > 9)
            {
                arr[i] = arr[i] - 9;
            }
        }
        else
        {
            arr[i] = card % 10;
        }
        //sum variable adds all array cells
        sum = sum + arr[i];
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//typeout function determines the type of card by checking length and initials
int typeout(int length, long long card)
{
    if (length == 13)
    {
        if (card / three == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 14)
    {
        if (card / four == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 15)
    {
        if (card / five == 4)
        {
            printf("VISA\n");
        }
        else if ((card / four == 34) || (card / four == 37))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 16)
    {
        if (card / six == 4)
        {
            printf("VISA\n");
        }
        else if ((card / five > 50) && (card / five < 56))
        {
            printf("MASTERCARD\n");
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
    return 0;
}