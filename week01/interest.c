/* Calculate interest. */
#include <stdio.h>

double add(double amount, double interestRate) {
    amount = amount + amount*interestRate /100.0;
    return amount;
}

int main() {
    double a; 
    double i;
    printf("Enter saved amount: \n");
    scanf("%lf", &a);
    printf("Enter interest rate: \n");
    scanf("%lf", &i);
    double total = add(a, i);
    printf("Adding %lf%% interest to %lf gives %lf\n", i, a, total);
    return 0;
}