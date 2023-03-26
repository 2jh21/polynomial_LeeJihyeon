#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 101

typedef struct {
    int coef;
    int expon;
} poly;

poly terms[MAX_TERMS] = { {4,3},{3,2},{2,1},{1,0},{3,2},{2,1},{8,0} };

int avail = 7;

void attach(int coef, int expon) {
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++;
}

void poly_mul(int As, int Ae, int Bs, int Be, int* Cs, int* Ce) {
    *Cs = avail;

    for (int i = As; i <= Ae; i++) {
        for (int j = Bs; j <= Be; j++) {
            attach(terms[i].coef * terms[j].coef, terms[i].expon + terms[j].expon);
        }
    }

    *Ce = avail - 1;
}

void print_poly1(int s, int e) {
    for (int i = s; i < e; i++)
        printf("%dx^%d+", terms[i].coef, terms[i].expon);
    printf("%dx^%d\n", terms[e].coef, terms[e].expon);
}

void print_poly2(int s, int e) {
    int i = s;
    for (i; i <= e; i++) {
        int j = i + 1;
        while (j <= e) {
            if (terms[i].expon == terms[j].expon) {
                terms[i].coef += terms[j].coef;
                terms[j].coef = 0;
            }
            j++;
        }
    }

    for (int i = s; i <= e; i++) {
        if (terms[i].coef != 0) {
            printf("%dx^%d", terms[i].coef, terms[i].expon);
            if (i != e) printf("+");
        }
    }
    printf("\n");
}

int main() {
    int As = 0, Ae = 3, Bs = 4, Be = 6, Cs, Ce;
    poly_mul(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly1(As, Ae);
    print_poly1(Bs, Be);
    printf("-----------------------------------------------------------\n");
    print_poly2(Cs, Ce);

    printf("\n");

    avail = Ce + 1;
    attach(7, 6);
    attach(5, 3);
    attach(9, 2);
    attach(1, 0);
    attach(5, 3);
    attach(2, 2);
    attach(1, 1);
    attach(10, 0);
    As = Ce + 1, Ae = As + 3, Bs = Ae + 1, Be = Bs + 3;
    poly_mul(As, Ae, Bs, Be, &Cs, &Ce);
    print_poly1(As, Ae);
    print_poly1(Bs, Be);
    printf("-----------------------------------------------------------\n");
    print_poly2(Cs, Ce);

    system("pause");

    return 0;
}

