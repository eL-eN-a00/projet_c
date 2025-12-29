#ifndef COORD_H
#define COORD_H

#include <stdbool.h>

// Type représentant un point du plan en coordonnées carthésiennes entières
typedef struct {
    int x; // abscisse
    int y; // ordonnée
} coord_t;

// creer_cord
// Précondition : aucune
// Postcondition : retourne un point dont l'abscisse vaut x et l'ordonnée vaut y
coord_t creer_cord(int x, int y);

// get_x
// Précondition : aucune
// Postcondition : retourne l'abscisse du point p
int get_x(coord_t p);

// get_y
// Précondition : aucune
// Postcondition : retourne l'ordonnée du point p
int get_y(coord_t p);

// set_x
// Précondition : p pointe vers une coord_t valide
// Postcondition : l'abscisse du point pointé par p vaut x
void set_x (coord_t *p, int x);

// set_y
// Précondition : p pointe vers une coord_t valide
// Postcondition : l'ordonnée du point pointé par p vaut y
void set_y (coord_t *p, int y);

// memes_coord
// Précondition : aucune
// Postcondition : retourne vrai si et seulement si p1 et p2 ont la même abscisse et la même ordonnée
bool memes_coord(coord_t p1, coord_t p2);

// translation
// Précondition : aucune
// Postcondition : retourne un nouveau point obtenu en translatant p de dx selon l'axe des x et de dy selon l'axe des y
coord_t translation(coord_t p, int dx, int dy);

// distance_euclidienne
// Précondition : aucune
// Postcondition : retourne la distance euclidienne entre p1 et p2
float distance_euclidienne(coord_t p1, coord_t p2);

#endif // COORD_H
