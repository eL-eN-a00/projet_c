#include "dijkstra.h"
#include "animation.h"
#include <math.h>
#include <stdlib.h> 
#include <stddef.h>

/**
 * cout : calcule le coût pour rejoindre le noeud suivant depuis le noeud
 * courant. Ce coût est égal à la distance euclidienne entre les deux noeuds,
 * plus le dénivelé entre ces deux noeuds s'il est positif.
 * 
 * Pré-conditions :
 *  - dans_les_bornes(grille, courant)
 *  - dans_les_bornes(grille, suivant)
 * Post-conditions :
 *  - cout > 0, potentiellement infini (INFINITIY)
 *
 * @param grille heightmap contenant les hauteurs
 * @param courant noeud duquel on part pour calculer le coût
 * @param suivant noeud auquel on arrive pour calculer le coût
 * @return coût pour passer de courant à suivant
 */
static float calcul_cout(grille_t grille, coord_t courant, coord_t suivant) {

    //Calcul distance euclidinne
    int dx = get_x(courant) - get_x(suivant); 
    int dy = get_y(courant) - get_y(suivant);
    float distance = (float)sqrt(dx*dx + dy*dy);

    //Calcul denivelé
    float hauteur_courant = get_hauteur(grille, courant);
    float hauteur_suivant = get_hauteur(grille, suivant); 
    float denivele = hauteur_suivant - hauteur_courant; 

    return distance + fmaxf (0.0f, denivele); 
}

/**
 * construire_chemin_vers - Construit le chemin depuis le noeud de départ donné vers le
 * noeud donné. On passe un chemin en entrée-sortie de la fonction, qui est mis à jour
 * par celle-ci.
 *
 * Ce sous-programme fonctionne récursivement :
 *  1. Si le noeud est égal au noeud de départ, on a fini
 *  2. Sinon, on construit le chemin du départ au noeud précédent (appel récursif)
 *  3. Dans tous les cas, on ajoute le noeud au chemin, avec les caractéristiques associées dans visites
 *
 * @param chemin [in/out] chemin dans lequel enregistrer les étapes depuis le départ vers noeud
 * @param visites [in] liste des noeuds visités créée par l'algorithme de Dijkstra
 * @param source noeud de départ du chemin
 * @param noeud noeud vers lequel on veut construire le chemin depuis le départ
 */
// TODO: construire_chemin_vers
static void construire_chemin_vers (liste_noeud_t** chemin, liste_noeud_t* visites, coord_t source, coord_t noeud) {
    // cas de base : on est arrivés à la source
    if (chemin == NULL || *chemin == NULL ) {}
    else {
        if (get_x(source)==get_x(noeud) && get_y(source)==get_y(noeud)) {
            double cout = cout_noeud_liste (visites, source);
            inserer_noeud_liste(*chemin, source, source, cout);
        } else {
            coord_t precedent = precedent_noeud_liste (visites, noeud); 

            // sécurité : éviter la boucle infinie si le graphe est mal formé
            if (get_x(precedent) == get_x(noeud) && get_y(precedent) == get_y(noeud)) {}
            else {
                double cout = cout_noeud_liste(visites, noeud);

                //Appel récursif d'abord pour construire la fonction dans le bon sens
                construire_chemin_vers (chemin, visites, source, precedent);

                // Ajout après l'appel récursif
                inserer_noeud_liste(*chemin, noeud, precedent, cout);
            }
        }
    }
}

float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin
    ) {

    //Creer le chemin s'il n'existe pas 
    if (chemin != NULL) {
        *chemin = creer_liste();
    } else {}

    //Initialiser les listes 
    liste_noeud_t* Visiter = creer_liste(); 
    liste_noeud_t* A_Visiter = creer_liste(); 
    inserer_noeud_liste(A_Visiter, source, source, 0.0);

    //Traiter les noeuds tant qu'il existe un noeud dans A_Visite
    while (!est_vide_liste(A_Visiter)) {

        
        // Extraire le meilleur noeud
        coord_t courant = min_noeud_liste(A_Visiter); 


        // Récupérer ses infos avant de le supprimer
        coord_t precedent =  precedent_noeud_liste(A_Visiter, courant) ;
        double cout_courant = cout_noeud_liste(A_Visiter, courant);

        // Le supprimer de la liste de travail immédiatement
        supprimer_noeud_liste(A_Visiter, courant);

        // L'ajouter aux noeuds finalisés
        inserer_noeud_liste(Visiter, courant, precedent, cout_courant);

        // On sort de la boucle si on trouve la destination (evite des calculs inutiles
        if (get_x(courant) == get_x(destination) && get_y(courant) == get_y(destination)) {
            break;
        }

        //Trouver les voisins de courant non visités
        coord_t* voisins = NULL; 
        size_t nombre_voisins = get_voisins(grille, courant , seuil, &voisins);
        if (voisins != NULL) { 
            for (size_t i = 0; i < nombre_voisins; i++) {
                
                //Verifier que le voisin n'a pas encore était visité
                if (!contient_noeud_liste(Visiter, voisins[i])){
                    //Calcul du cout pour aller de la source vers ce vosisin en passant par courant
                    double n_cout = cout_courant + (double) calcul_cout(grille, courant, voisins[i]); //Cout source->courant + Cout courant->voisin

                    // Ajout du voisin dans A_Visiter
                    if (!contient_noeud_liste(A_Visiter, voisins[i])){
                        inserer_noeud_liste(A_Visiter, voisins[i], courant, n_cout);
                    }
                    else {
                        //Cout actuel du voisin
                        double old_cout = cout_noeud_liste(A_Visiter, voisins[i]);
                        
                        //Mettre à jour le cout uniquement si celui-ci est inférieur à celui determiné précédement
                        if (n_cout < old_cout) {
                            inserer_noeud_liste(A_Visiter, voisins[i], courant, n_cout);
                        }
                    }
                }        
            }
        }
        free(voisins);
    }

    float score_final = INFINITY;

    // Verification de la réussite
    if (contient_noeud_liste(Visiter, destination)) {
        score_final = (float) cout_noeud_liste(Visiter, destination);
        if (chemin != NULL) {
            construire_chemin_vers(chemin, Visiter, source, destination);
        }
        else {}
    }
    else {
        // Si échec, on insère la destination avec un coût infini seulement si le chemin est demandé
        if (chemin != NULL && *chemin != NULL) {
            inserer_noeud_liste(*chemin, destination, source, INFINITY);
        }
        else {}
    }
    detruire_liste(&Visiter);
    detruire_liste(&A_Visiter);

    return score_final;

}