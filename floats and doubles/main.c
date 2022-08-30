

/* this is a program that shows the accuracy of a float, a double, and a long double,
 * by calculating the answer to 0.1 + 0.2
 *
 * a float is accurate for 8 significant digits, while double is accurate for 16,
 * there is no way to go past 16 digits, even a long double failed even though it was a little closer */

#include <stdio.h>

int main() {

    float F1=0.2;
    float F2=0.1;
    double D1=0.2;
    double D2=0.1;
    long double LD1=0.2;
    long double LD2=0.1;
    printf("float answer is %.17f \n", F1+F2);
    printf("double answer is %.17lf \n", D1+D2);
    printf("long double answer is %.17Lf \n", LD1+LD2);
    printf ("size of float is %zu \n", sizeof(F1));
    printf ("size of double is %zu \n", sizeof(D1));
    printf ("size of long double is %zu \n", sizeof(LD1));

    return 0;
}
