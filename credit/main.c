

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
#include <cs50.c>
const long long length_low = 1000000000000;
const long long length_visa = 100000000000000;
const long long length_mastercard = 10000000000000000;
const long long length_amex = 1000000000000000;
int main() {

    //printf ("number: %lld\n", card);
    //printf ("divider: %lld\n", length_low);
    while (true)
    {
        long long card = get_long_long("Number: ");
        if (card / length_low > 0) {
            if (card / length_visa == 0) {
                printf("might be visa\n");
            } else if ((card / length_amex == 0) && (card / (length_visa) > 0)) {
                printf("might be amex or visa\n");
            } else if ((card / length_mastercard == 0) && (card / (length_amex) > 0)) {
                printf(" might be master card or visa\n");
            } else {
                printf("INVALID\n");
            }
        } else {
            printf("INVALID\n");
        }
        return 0;
    }
}