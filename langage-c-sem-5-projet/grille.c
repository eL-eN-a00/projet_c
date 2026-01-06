#define _GNU_SOURCE
#include "grille.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>

/**
 * coord_lin : fonction statique (de module) qui transforme des coordonnées
 * cartésiennes dans la grille en coordonnées "linéaires" permettant d'adresser
 * le tableau contenu dans la grille.
 *
 * @param grille grille avec le bon système de coordonnées
 * @param position position dans la grille en coordonnées cartésiennes entières
 * @return position dans le tableau en coordonnée linéaire
 */
static size_t coord_lin(grille_t grille, coord_t position) {
    int x = get_x(position); 
    int y = get_y(position); 
    return (y*grille.largeur+x); 
}

grille_t creer_grille(int largeur, int profondeur) {
    grille_t grille; 
    grille.largeur = largeur; 
    grille.profondeur = profondeur; 
    grille.hauteurs = (float*)(calloc(largeur*profondeur, sizeof(float))); 
    return grille; 
}

void detruire_grille(grille_t grille) {
    free(grille.hauteurs); 
}

bool dans_les_bornes(grille_t grille, coord_t position) {
    int x = get_x(position); 
    int y = get_y(position); 
    return grille.largeur > x >= 0 && grille.profondeur > y >= 0; 
}

int get_largeur(grille_t grille) {
    return grille.largeur; 
}

int get_profondeur(grille_t grille) {
    return grille.profondeur; 
}

coord_t inferieur_gauche(grille_t grille) {
    // int y = grille.profondeur; 
    //return creer_coord(0,y-1); 
    return creer_coord(0,0); 
}

coord_t superieur_droit(grille_t grille){
    int y = grille.profondeur;
    int x = grille.largeur; 
    //return creer_coord(x-1,0); 
    return creer_coord (x-1,y-1); 
}

void set_hauteur(grille_t grille, coord_t position, float hauteur) {
    size_t indice = coord_lin (grille, position); 
    grille.hauteurs[indice] = hauteur; 
}

float get_hauteur(grille_t grille, coord_t position) {
    size_t indice = coord_lin (grille, position); 
    return grille.hauteurs[indice]; 
}

size_t get_voisins(grille_t grille, coord_t position, float seuil, coord_t** voisins) {
    int x = get_x(position); 
    int y = get_y (position);
    size_t taille_voisins = 0; 
    *voisins = malloc(4 * sizeof(coord_t));
    
    if ((x > 0) && (fabs (get_hauteur(grille, position) - get_hauteur(grille, creer_coord (x-1,y))) <= seuil)) {
        *(voisins)[taille_voisins] = creer_coord (x-1,y); 
        taille_voisins++;
    }
    if ((x < grille.largeur - 1) && (fabs (get_hauteur(grille, position) - get_hauteur(grille, creer_coord (x+1,y))) <= seuil)) {
        *(voisins)[taille_voisins] = creer_coord (x+1,y);
        taille_voisins++;
    }
    if ((y > 0) && (fabs (get_hauteur(grille, position) - get_hauteur(grille, creer_coord (x,y-1))) <= seuil))  {
        *(voisins)[taille_voisins] = creer_coord (x,y-1);
        taille_voisin++;
    }
    if ((y < grille.profondeur - 1) && (fabs (get_hauteur(grille, position) - get_hauteur(grille, creer_coord (x,y+1))) <= seuil)) {
        *(voisins)[taille_voisins] = creer_coord (x,y+1);
        taille_voisins++;
    }
    return taille_voisins; 
}
