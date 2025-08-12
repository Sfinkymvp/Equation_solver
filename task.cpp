#include <stdio.h>
#include <math.h>


typedef struct {
    float a, b, c;
    float d;
    float x1, x2;
} Equation;


void quadratic_equation(Equation *);
void entering_coefficients(Equation *);
float finding_discriminant(Equation *);
void roots(Equation *);
void print_roots(Equation *);


int main()
{
    Equation eq;

    entering_coefficients(&eq);

    if (eq.a == 0) {
        printf("the equation is not quadratic!\n");
        return 0;
    }

    quadratic_equation(&eq);
    
    print_roots(&eq);

    return 0;
}


void quadratic_equation(Equation * eq)
{
    eq->d = finding_discriminant(eq);

    roots(eq);
}


void entering_coefficients(Equation * eq)
{
    printf("Enter coefficients\n");

    scanf("%f%f%f", &eq->a, &eq->b, &eq->c);
}


float finding_discriminant(Equation * eq)
{
    return eq->b * eq->b - (4 * eq->a * eq->c);
}


void roots(Equation * eq) 
{
    if (eq->d > 0) {
        eq->x1 = (-eq->b - sqrt(eq->d)) / (2 * eq->a);
        eq->x2 = (-eq->b + sqrt(eq->d)) / (2 * eq->a);
    } else if (eq->d == 0) {
        eq->x1 = (-eq->b) / (2 * eq->a);
        eq->x2 = 0;
    } else {
        eq->x1 = eq->x2 = 0;
    }
}


void print_roots(Equation * eq)
{
    if (eq->d > 0) {
        printf("Two roots:\n");
        printf("%.2f %.2f\n", eq->x1, eq->x2);
    } else if (eq->d == 0) {
        printf("One root:\n");
        printf("%.2f\n", eq->x1);
    } else {
        printf("no roots\n");
    }
}
