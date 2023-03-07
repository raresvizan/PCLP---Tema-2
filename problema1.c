#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generareKeywords(char **key) {
    // memorez cuvintele intr-un mod care ma ajuta la verificare
    //  keywords de un cuvant
    key[0] = "from";
    key[1] = "in";
    key[2] = "unit";
    key[3] = "or";
    key[4] = "while";
    key[5] = "int";
    key[6] = "float";
    key[7] = "double";
    key[8] = "string";
    // keywords care pot fi de un cuvant sau 2
    key[9] = "for";
    key[10] = "is";
    // keywords care pot fi doar de 2 cuvinte
    key[11] = "first";
    key[12] = "list";
}

void cautareKeywords(char *s, char **key, char *underline) {
    char *p1, *p2;
    int i, j, caz = 0, st, dr;
    /*
    folosesc strtok pentru a verifica fiecare cuvant din string.
    folosesc doi pointeri p1, p2 pentru a memora cand e nevoie si cuvantul
    actual si cel anterior.
    variabila caz ia valoarea:
    0 -> initial si dupa fiecare verificare a unui posibil keyword;
    1 -> cand keywordul gasit este format de un singur cuvant;
    2 -> cand keywordul gasit poate fi format din 1 sau 2 cuvinte;
    variabilele st, dr memoreaza pozitiile intre care highlightul va fi adaugat
    */
    p2 = strtok(s, " ");
    while (p2 != NULL) {
        // verific daca exista un keyword compus din 2 cuvinte
        if (caz == 2) {
            // caut keywordul "for each"
            if (strcmp(p1, "for") == 0) {
                if (strcmp(p2, "each") == 0) {
                    // maresc zona de highlight
                    dr = p2 - s + strlen(p2);
                    // adaug higlight
                    for (i = st; i < dr; i++) {
                        underline[i] = '_';
                    }
                }
            }  // caut keywordul "is a"
            else if (strcmp(p1, "is") == 0) {
                if (strcmp(p2, "a") == 0) {
                    dr = p2 - s + strlen(p2);
                    for (i = st; i < dr; i++) {
                        underline[i] = '_';
                    }
                }
            }  // caut keywordul "first of" sau "list of"
            else if (strcmp(p1, "first") == 0 || strcmp(p1, "list") == 0) {
                if (strcmp(p2, "of") == 0) {
                    dr = p2 - s + strlen(p2);
                    for (i = st; i < dr; i++) {
                        underline[i] = '_';
                    }
                }
            }
        }
        caz = 0;
        // verific daca p2 este keyword de 1 cuvant
        for (i = 0; i < 9 && caz == 0; i++) {
            if (strcmp(p2, key[i]) == 0) {
                caz = 1;
                // stabilesc zona de highlight
                st = p2 - s;
                dr = st + strlen(p2);
                // adaug highlight in zona gasita
                for (j = st; j < dr; j++) {
                    underline[j] = '_';
                }
            }
        }
        // verific daca p2 este keyword de 1 cuvant sau 2
        for (i = 9; i < 11 && caz == 0; i++) {
            if (strcmp(p2, key[i]) == 0) {
                caz = 2;
                // stabilesc zona de highlight
                st = p2 - s;
                dr = st + strlen(p2);
                /*
                adaug highlight in zona gasita, deoarece cuvantul gasit este un
                keyword oricum
                */
                for (j = st; j < dr; j++) {
                    underline[j] = '_';
                }
                /*
                memorez cuvantul in p1 pentru a verifica daca formeaza un
                keyword cu cuvantul urmator
                */
                p1 = p2;
            }
        }
        // verific daca p2 este keyword de 2 cuvinte
        for (i = 11; i < 13; i++) {
            if (strcmp(p2, key[i]) == 0) {
                caz = 2;
                // stabilesc pozitia de incepere a highlightului
                st = p2 - s;
                /*
                memorez cuvantul in p1 pentru a verifica daca formeaza un
                keyword cu cuvantul urmator
                */
                p1 = p2;
            }
        }
        p2 = strtok(NULL, " ");
    }
}

void afisare(int n, char *s) {
    /*
    key[][] - matricea in care memorez cuvintele cheie
    underline[] - vectorul care contine highlightul
    */
    char **key, *underline;
    int i;
    key = malloc(13 * sizeof(char *));
    for (i = 0; i < 13; i++) {
        key[i] = malloc(10);
    }
    // generez matricea de keywords
    generareKeywords(key);
    underline = calloc(n + 1, n + 1);
    // incep cautarea keywords in string
    cautareKeywords(s, key, underline);
    // completez cu spatii restul vectorului care nu contine highlight
    for (i = 0; i < n; i++) {
        if (underline[i] != '_') {
            underline[i] = ' ';
        }
    }
    // afisez highlightul stringului
    puts(underline);
    free(key);
    free(underline);
}

int main() {
    int n, i;
    char **text, citire[102];
    // citesc n - numarul de linii de text
    scanf("%d", &n);
    getchar();
    text = malloc(n * sizeof(char *));
    // citesc fiecare linie de text
    for (i = 0; i < n; i++) {
        fgets(citire, 102, stdin);
        citire[strlen(citire) - 1] = '\0';
        text[i] = malloc(strlen(citire) + 1);
        strcpy(text[i], citire);
    }
    for (i = 0; i < n; i++) {
        // afisez linia de text ce urmeaza a fi verificata
        puts(text[i]);
        // incep verificarea
        afisare(strlen(text[i]), text[i]);
    }
    free(text);
    return 0;
}