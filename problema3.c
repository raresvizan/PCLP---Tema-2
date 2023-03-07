#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int (*funPtr)();

unsigned int extragereBiti(unsigned int n, int nr, int poz) {
    unsigned int rez, extrage, sterge;
    // marchez cati biti trebuie extrasi
    extrage = (1 << nr) - 1;
    // mut bitii care trebuie extrasi in dreapta
    sterge = n >> poz;
    rez = extrage & sterge;
    return rez;
}

unsigned int adunare(unsigned int a, unsigned int b) {
    int bit_a[4], bit_b[4], i;
    unsigned int rez = 0;
    // memorez bitii numerelor a,b in 2 vectori
    for (i = 3; i >= 0; i--) {
        bit_a[i] = a & 1;
        a = a >> 1;
        bit_b[i] = b & 1;
        b = b >> 1;
    }
    // p -> 1 daca trebuie adaugat la urmatoarea adunare de bit
    int p = 0;
    for (i = 3; i >= 0; i--) {
        // cazul 1+1
        if (bit_a[i] == 1 && bit_b[i] == 1) {
            rez = rez | (p << (3 - i));
            p = 1;
        }  // cazul 1+0 sau 0+1
        else if (bit_a[i] == 1 || bit_b[i] == 1) {
            if (p == 0) {
                rez = rez | (1 << (3 - i));
            }
        }  // cazul 0+0
        else {
            if (p == 1) {
                rez = rez | (1 << (3 - i));
                p = 0;
            }
        }
    }
    // cazul cand adunarea depaseste 4 biti
    if (p == 1) {
        rez = rez | (1 << 4);
    }
    // extrag doar 4 biti din rezultatul adunarii
    rez = extragereBiti(rez, 4, 0);
    return rez;
}
unsigned int interschimbare(unsigned int a, unsigned int b) {
    int bit_a[4], i;
    unsigned int rez = 0, p1, p2;
    // memorez bitii numerului a intr-un vector
    for (i = 3; i >= 0; i--) {
        bit_a[i] = a & 1;
        a = a >> 1;
    }
    // extrag bitii lui b conform cerintei
    p1 = extragereBiti(b, 2, 2);
    p2 = extragereBiti(b, 2, 0);
    // interschimb bitii de pe pozitiile p1,p2 din a
    int aux = bit_a[p1];
    bit_a[p1] = bit_a[p2];
    bit_a[p2] = aux;
    // construiesc rezultatul
    for (i = 0; i < 4; i++) {
        if (bit_a[i] == 1) {
            rez = rez | (1 << (3 - i));
        }
    }
    return rez;
}
unsigned int rotatieStanga(unsigned int a, unsigned int b) {
    int bit_a[4], i, ult, j;
    unsigned int rez = 0;
    // memorez bitii numerului a intr-un vector
    for (i = 3; i >= 0; i--) {
        bit_a[i] = a & 1;
        a = a >> 1;
    }
    for (i = 0; i < b; i++) {
        // memorez primul bit
        ult = bit_a[0];
        // bitii se muta cu o pozitie spre stanga
        for (j = 0; j < 3; j++) {
            bit_a[j] = bit_a[j + 1];
        }
        // ultimul bit ia valoarea primului
        bit_a[3] = ult;
    }
    // construiesc rezultatul
    for (i = 0; i < 4; i++) {
        if (bit_a[i] == 1) {
            rez = rez | (1 << (3 - i));
        }
    }
    return rez;
}
unsigned int xor(unsigned int a, unsigned int b) {
        int bit_a[4], bit_b[4], i;
        unsigned int rez = 0;
        // memorez bitii numerelor a,b in 2 vectori
        for (i = 3; i >= 0; i--) {
            bit_a[i] = a & 1;
            a = a >> 1;
            bit_b[i] = b & 1;
            b = b >> 1;
        }
        // caut ca bitii sa fie diferiti
        for (i = 3; i >= 0; i--) {
            if ((bit_a[i] == 1 && bit_b[i] == 0) ||
                (bit_a[i] == 0 && bit_b[i] == 1)) {
                rez = rez | (1 << (3 - i));
            }
        }
        return rez;
    }

    int main() {
    int n, i, poz, nbiti;
    unsigned int m, a, b, op, rez;
    funPtr fp[] = {adunare, interschimbare, rotatieStanga, xor};
    /*
    a,b - numerele formate din cei 4 biti
    op - codul operatiei
    nbiti - numarul de biti ai numarului -1
    poz - pozitia bitilor care trebuie extrasi
    rez - rezultatul operatiei
    */
    scanf("%d", &n);
    scanf("%u", &m);
    // extrag cei N*6+4 biti
    m = extragereBiti(m, n * 6 + 4, 0);
    nbiti = n * 6 + 4 - 1;
    poz = 3;
    // extrag primii 4 biti reprezentand primul numar
    a = extragereBiti(m, 4, nbiti - poz);
    for (i = 0; i < n; i++) {
        poz = poz + 2;
        // extrag cei 2 biti pentru operatie
        op = extragereBiti(m, 2, nbiti - poz);
        poz = poz + 4;
        // extrag urmatorii 4 biti reprezentand al doilea numar
        b = extragereBiti(m, 4, nbiti - poz);
        // apelez functia de pe poz op in vector
        rez = fp[op](a, b);
        // rezultatul operatiei devine primul numar pt urmatoarea operatie
        a = rez;
    }
    // cazul fara operatii => rez ramane numarul initial
    if (n == 0) {
        rez = m;
    }
    printf("%d", rez);
    return 0;
}