#include <stdio.h>
#include <cs50.h>

int quarters, dimes, nickels, pennies;
int cash;
//get cent fuction, it asks for amount of cents
//and makes sure they are positive
int get_cents(void)
{
    do
    {
        cash = get_int("change owed:");
    }
    while (cash <= 0);
    return cash;
}
// calculate quarters function, it calculates the amount
// of quarters in the input cent number, then subtracts
// the quarters from the cents total
int calculate_quarters(int cashs)
{
    quarters = cashs / 25;
    printf("%d", quarters);
    cash = cashs - quarters * 25;
    return quarters;
}
// calculate dimes function, it calculates the amount
// of dimes in the input cent number, then subtracts
// the dimes from the cents total
int calculate_dimes(int cashs)
{
    dimes = cashs / 10;
    printf("%d", dimes);
    cash = cashs - dimes * 10;
    return dimes;
}
// calculate nickels function, it calculates the amount
// of nickels in the input cent number, then subtracts
// the nickels from the cents total
int calculate_nickels(int cashs)
{
    nickels = cashs / 5;
    printf("%d", nickels);
    cash = cashs - nickels * 5;
    return 0;
}
// calculate pennies function, it calculates the amount
// of pennies in the input cent number, then subtracts
// the pennies from the cents total, then calculates
// total of coins
int calculate_pennies(int cashs)
{
    pennies = cashs;
    printf("%d", pennies);
    printf("%d\n", quarters + dimes + nickels + pennies);
    return pennies;
}
//main function, it simply calls all the other functions
//in the order that satisfies the greedy algorithm
int main(void)
{
    while (cash <= 0)
    {
        get_cents();
        if (cash > 0)
        {
            calculate_quarters(cash);
            calculate_dimes(cash);
            calculate_nickels(cash);
            calculate_pennies(cash);
            return 0;
        }
    }
}

