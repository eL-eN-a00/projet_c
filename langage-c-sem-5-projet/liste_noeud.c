#define _GNU_SOURCE
#include "liste_noeud.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

/* TODO */

/* structure d'une cellule de la liste chaînée */

typedef struct cellule_s {
    coord_t noeud;
    coord_t precedent;
    double cout;
    struct cellule_s* suivant;
} cellule_t;

/* structure de contrôle de la liste */

struct liste_noeud s {
    cellule_t* tete;
};

/* cycle de vie */

liste_noeud_t creer_liste(void) {
    liste_noeud_t l = malloc(sizeof(struct liste_noeud_s));
    if (l != NULL) {
        l->tete = NULL;
    }
    else {}
    return l;
}

void detruire_liste(liste_noeud_t* liste_ptr) {
    assert(liste_ptr != NULL);
    if (*liste_ptr == NULL) {
        return;
    }
    else {
        cellule_t* courant = (*liste_ptr)->tete;
        while (courant != NULL) {
            cellule_t* a_supprimer = courant;
            courant = courant->suivant;
            free(a_supprimer);
        }
        free(*liste_ptr);
        *liste_ptr = NULL;
    }
}

/* Consultation */

bool est_vide_liste(const liste_noeud_t l) {
    assert(l != NULL);
    return l->tete == NULL;
}

bool contient_noeud_liste(const liste_noeud_t l, coord_t n) {
    assert(l != NULL);
    cellule_t* courant = l->tete; 
}