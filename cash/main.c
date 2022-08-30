#include <stdio.h>
#include <cs50.c>

int quarters, dimes, nickles, pennies;
int cash;

int calc_quarters(void)
{
    quarters = cash / 25;
    printf("%d quarters, ", quarters);
    cash = cash - quarters * 25;
    return 0;
}

int calc_dimes(void)
{
    dimes = cash / 10;
    printf("%d dimes, ", dimes);
    cash = cash - dimes * 10;
    return 0;
}

int calc_nickles(void)
{
    nickles = cash / 5;
    printf("%d nickles, ", nickles);
    cash = cash - nickles * 5;
    return 0;
}

int calc_pennies(void)
{
    pennies = cash;
    printf("%d pennies.\n", pennies);
    printf("number of coins: %d\n", quarters + dimes + nickles + pennies);
    return 0;
}

int main(void)
{
    while (true) {
        cash = get_int("change owed:");
        if (cash>0) {
            calc_quarters();
            calc_dimes();
            calc_nickles();
            calc_pennies();
            return 0;
        }
    }
}

