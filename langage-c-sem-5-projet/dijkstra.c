#include "dijkstra.h"
#include "animation.h"
#include <math.h>

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
    float distance = sqrt(dx*dx + dy*dy);

    //Calcul denivelé
    float hauteur_courant = get_hauteur(grille, courant);
    float hauteur_suivant = get_hauteur(grille, suivant); 
    float denivele = hauteur_suivant - hauteur_courant; 

    return distance + fmaxf (0, denivele); 
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
    if (get_x(source)==get_x(noeud) && get_y(source)==get_y(noeud)) {
        double cout = cout_noeud_liste (visites, noeud);
        inserer_noeud_liste(*chemin, source, source, cout);
    }
    else {
        coord_t precedent = precedent_noeud_liste (visites, noeud); 
        double cout = cout_noeud_liste (visites, noeud);

        //Appel récursif de la fonction
        construire_chemin_vers (chemin, visites, source, precedent);

        // Ajout du noeud (pour avoir le chemin de la source vers la destination) 
        inserer_noeud_liste(*chemin, noeud, precedent, cout);
    }
}

float dijkstra(
        grille_t grille, 
        coord_t source, coord_t destination, 
        float seuil,
        liste_noeud_t** chemin
    ) {

    //Initialiser les listes 
    liste_noeud_t* Visiter = creer_liste(); 
    liste_noeud_t* A_Visiter = creer_liste(); 
    inserer_noeud_liste(A_Visiter, source, source, 0.0);

    //Traiter les noeuds tant qu'il existe un noeud dans A_Visite
    coord_t courant = source;  
    while (!est_vide_liste(A_Visiter)) {
        
        //Trouver le cout minimal dans A_Visiter
        courant = min_noeud_liste(A_Visiter); 


        //Ajouter le noeud courant dans Visiter 
        coord_t precedent =  precedent_noeud_liste(A_Visiter, courant) ;
        double cout_courant = cout_noeud_liste(A_Visiter, courant);
        inserer_noeud_liste(Visiter, courant, precedent, cout_courant);

        // On sort de la boucle si on trouve la destination (evite des calculs inutiles
        if (get_x(courant) == get_x(destination) && get_y(courant) == get_y(destination)) {
            break;
        }

        //Supprimer courant de A_Visiter
        supprimer_noeud_liste(A_Visiter, courant); 

        //Trouver les voisins de courant non visités
        coord_t* voisins = NULL; 
        size_t nombre_voisins = get_voisins(grille, courant , seuil, &voisins);
        for (int i=0; i < nombre_voisins; i++) {
            
            //Verifier que le voisin n'a pas encore était visité
            if (!contient_noeud_liste(Visiter, voisins[i])){

                // Ajout du voisin dans A_Visiter
                if (!contient_noeud_liste(A_Visiter, voisins[i])){
                    inserer_noeud_liste(A_Visiter, voisins[i], courant, INFINITY);
                }
                
                //Calcul du cout pour aller de la source vers ce vosisin en passant par courant
                double new_cout = cout_courant + (double) calcul_cout(grille, courant, voisins[i]); //Cout source->courant + Cout courant->voisin

                //Cout actuel du voisin
                double old_cout = cout_noeud_liste(A_Visiter, voisins[i]);
                
                //Mettre à jour le cout uniquement si celui-ci est inférieur à celui determiné précédement
                if (new_cout < old_cout) {
                    inserer_noeud_liste(A_Visiter, voisins[i], courant, new_cout);
                }
            }        
        }
        free(voisins);
    }

    //On verifie que la destination a bien été visitée
    if (contient_noeud_liste(Visiter, destination)) {
        construire_chemin_vers (chemin, Visiter, source, destination);
        return (float) cout_noeud_liste(Visiter, destination);
    }
    else {
        inserer_noeud_liste(*chemin, destination, source, INFINITY); 
        return INFINITY; 
    }
}
