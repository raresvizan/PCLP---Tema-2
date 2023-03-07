#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    int priority;
} dictionary_entry;

void adaugareCuvant(dictionary_entry **dict, int *n, char *s) {
    // index - pozitia noului cuv adaugat in dictionar
    int index = *n;
    // maresc dictionarul
    *n = *n + 1;
    *dict = realloc(*dict, (*n) * sizeof(dictionary_entry));
    (*dict)[index].word = malloc(strlen(s) + 1);
    // adaug cuvantul si setez prioritatea
    strcpy((*dict)[index].word, s);
    (*dict)[index].priority = 1;
}

int semnePunctuatie(char *s) {
    if (s[0] == ',' || s[0] == '.' || s[0] == ':' || s[0] == '!' ||
        s[0] == '?') {
        return 1;
    }
    return 0;
}

void cautareCuvant(dictionary_entry **dict, int *n, char *s, int flag) {
    int i, pr_max = -1, index, exista = 0;
    /*
    flag - 1 cazul cuv*; 0 cazul obisnuit de autocmp.
    exista - cazul cuv*; 1 cuv exista in dict; 0 nu exista
    pr_max - prioritatea maxima gasita pentru cuv cautat
    index - pozitia in dictionar a cuv cu care se completeaza
    */
    for (i = 0; i < *n; i++) {
        // cazul cuv* - verific daca exista in dictionar
        if (flag == 1 && strcmp(s, (*dict)[i].word) == 0) {
            exista = 1;
            // exista in dictionar deci cresc prioritatea
            (*dict)[i].priority++;
            break;
        }
        // cazul obisnuit - caut cuv de prioritate maxima
        if (strlen(s) <= strlen((*dict)[i].word)) {
            if (strncmp(s, (*dict)[i].word, strlen(s)) == 0) {
                // compar prioritatile
                if (pr_max < (*dict)[i].priority) {
                    pr_max = (*dict)[i].priority;
                    index = i;
                } else if (pr_max == (*dict)[i].priority) {
                    if (strcmp((*dict)[i].word, (*dict)[index].word) < 0) {
                        index = i;
                    }
                }
            }
        }
    }
    // cazul cuv*; cuv nu exista si trebuie adaugat in dictionar
    if (flag == 1) {
        if (exista == 0) {
            adaugareCuvant(dict, n, s);
        }
    }  // cazul obisnuit de autocmp.
    else {
        // cuvantul nu exista in dictionar => il adaug
        if (pr_max == -1) {
            adaugareCuvant(dict, n, s);
        }  // cuvantul exista => inlocuiesc cuvantul si cresc prioritatea
        else {
            strcpy(s, (*dict)[index].word);
            (*dict)[index].priority++;
        }
    }
}

int main() {
    int n, m, i;
    char citire[21];
    dictionary_entry *dict;
    // citesc n - numarul initial de cuv din dictionar
    scanf("%d", &n);
    dict = calloc(n, n * sizeof(dictionary_entry *));
    // citesc dictionarul initial
    for (i = 0; i < n; i++) {
        scanf("%s", citire);
        dict[i].word = malloc(strlen(citire) + 1);
        strcpy(dict[i].word, citire);
        dict[i].priority = 0;
    }
    char *s;
    s = malloc(21);
    // citesc m - numarul de cuv pentru autocomplete
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        scanf("%s", s);
        // cazul semnelor de punctuatie
        if (semnePunctuatie(s)) {
            printf("%s ", s);
        }  // cazul cuvant*
        else if (s[strlen(s) - 1] == '*') {
            s[strlen(s) - 1] = '\0';
            cautareCuvant(&dict, &n, s, 1);
            printf("%s ", s);
        }  // cazul cuvant sau cuv
        else {
            cautareCuvant(&dict, &n, s, 0);
            printf("%s ", s);
        }
    }
    free(dict);
    free(s);
    return 0;
}