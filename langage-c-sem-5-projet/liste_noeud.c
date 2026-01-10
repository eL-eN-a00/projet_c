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

struct liste_noeud_s {
    cellule_t* tete;
};

/* cycle de vie */

liste_noeud_t* creer_liste(void) {
    liste_noeud_t* l = malloc(sizeof(struct liste_noeud_s));
    if (l != NULL) {
        l->tete = NULL;
    }
    return l;
}

void detruire_liste(liste_noeud_t** liste_ptr) {
    assert(liste_ptr != NULL);
    if (*liste_ptr == NULL) {}
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

bool est_vide_liste(const liste_noeud_t* l) {
    assert(l != NULL);
    return l->tete == NULL;
}

bool contient_noeud_liste(const liste_noeud_t* l, coord_t n) {
    assert(l != NULL);
    cellule_t* courant = l->tete;
    bool contient_noeud = false;
    while (courant != NULL && !contient_noeud) {
        if (get_x(courant->noeud) == get_x(n) && get_y(courant->noeud) == get_y(n)) {
            contient_noeud = true;
        }
        courant = courant->suivant;
    }
    return contient_noeud;
}

bool contient_arrete_liste(const liste_noeud_t* l, coord_t source, coord_t destination) {
    assert(l != NULL);
    cellule_t* courant = l->tete;
    bool contient_arrete = false;
    while (courant != NULL && !contient_arrete) {
        if (get_x(courant->noeud) == get_x(destination) && get_y(courant->noeud) == get_y(destination)) {
            coord_t prec = courant->precedent;
            contient_arrete = (get_x(prec) == get_x(source) && get_y(prec) == get_y(source));
        }
        courant = courant->suivant;
    }
    return contient_arrete;
}

double cout_noeud_liste(const liste_noeud_t* l, coord_t n) {
    assert(l != NULL);
    cellule_t* courant = l->tete;
    bool noeud_trouve = false;
    double cout = INFINITY;
    while (courant != NULL && !noeud_trouve) {
        if (get_x(courant->noeud) == get_x(n) && get_y(courant->noeud) == get_y(n)) {
            noeud_trouve = true;
            cout = courant->cout;
        }
        courant = courant->suivant;
    }
    return cout;
}

coord_t precedent_noeud_liste(const liste_noeud_t* l, coord_t n) {
    assert(l != NULL);
    cellule_t* courant = l->tete;
    coord_t preced =  creer_coord(-1, -1);
    bool preced_trouve = false;
    while (courant != NULL && !preced_trouve) {
        if (get_x(courant->noeud) == get_x(n) && get_y(courant->noeud) == get_y(n)) {
            preced_trouve = true;
            preced = courant->precedent;
        }
        courant = courant->suivant;
    }

    return preced; //coordonnées négatives si non trouvé
}

coord_t min_noeud_liste(const liste_noeud_t* l) {
    assert(l != NULL && !est_vide_liste(l));
    cellule_t* courant = l->tete;
    cellule_t* min_cell = l->tete;
    while (courant != NULL) {
        if (courant->cout < min_cell->cout) {
            min_cell = courant;
        }
        courant = courant->suivant;
    }
    return min_cell->noeud;
}

/* Modification */

void inserer_noeud_liste(liste_noeud_t* l, coord_t n, coord_t prec, double cout) {
    assert(l != NULL);
    cellule_t* courant = l->tete;
    bool noeud_trouve = false;
    //  recherche si le noeud existe déjà pour mise à jour
    while (courant != NULL && !noeud_trouve) {
        if (get_x(courant->noeud) == get_x(n) && get_y(courant->noeud) == get_y(n)) {
            courant->cout = cout;
            courant->precedent = prec;
            noeud_trouve = true;
        }
        courant = courant->suivant;
    }
    // sinon, ajout en tête de liste
    if (!noeud_trouve) {
        cellule_t* nouvelle = malloc(sizeof(cellule_t));
        if (nouvelle != NULL) {
            nouvelle->noeud = n;
            nouvelle->precedent = prec;
            nouvelle->cout = cout;
            nouvelle->suivant = l->tete;
            l->tete = nouvelle;
        }
    }
    else {}
}

void supprimer_noeud_liste(liste_noeud_t* l, coord_t n) {
    assert(l != NULL);
    cellule_t* courant = l->tete;
    cellule_t* precedent_cell = NULL;

    while (courant != NULL) {
        if (get_x(courant->noeud) == get_x(n) && get_y(courant->noeud) == get_y(n)) {
            if (precedent_cell == NULL) {
                l->tete = courant->suivant;
            } else {
                precedent_cell->suivant = courant->suivant;
            }
            free(courant);
            return;
        }
        precedent_cell = courant;
        courant = courant->suivant;
    }
}