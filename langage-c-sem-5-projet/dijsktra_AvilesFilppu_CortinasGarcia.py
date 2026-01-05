# ALGORITHME DE DIJSKTRA

# VALEURS INITIALES DE TEST
v = {0, 1, 2, 3, 4} #liste des arrêtes
E = [{1}, {2, 3}, {0}, set(), set()] #liste des sommets accessibles depuis l'arête

#FONTIONS UTILES
def succ(S, E):  
    """
    Renvoie l'ensemble des successeurs immédiats des sommets donnés

    Paramètres :
    S : ensemble de sommets des quels on cherche les successeurs immédiats 
    E : les successeurs de chaque sommet du graphe

    Retour : successeurs immédiats de S (set)
    """
    R = set()
    for s in S:
        R = R.union(E[s])
    return R
# print(succ({3}, E))

def pred(S, E):
    """
    Renvoie l'ensemble des prédécesseurs immédiats des sommets donnés

    Paramètres :
    S : ensemble de sommets des quels on cherche les prédécesseurs immédiats
    E : les successeurs de chaque sommet du graphe

    Retour : prédécesseurs immédiats de S (set)
    """
    R = set()
    for i in range(len(E)):
        if bool(S.intersection(E[i])):
            R.add(i)
    return R
# print(pred({3}, E))

def succ_star(S, E):
    """
    Renvoie la fermeture transitive des successeurs des sommets donnés, c'est à dire tout les sommets atteignables depuis celui donnée 

    Paramètres :
    S : ensemble de sommets des quels on cherche les successeurs
    E : les successeurs de chaque sommet du graphe

    Retour : successeurs de S - tout sommet atteignable depuis S (set)
    """
    S0 = S
    for s in S:
        S1 = S0.union(succ(S0, E))
        while S1 != S0 :
            S0 = S1
            S1 = succ_star(S0, E)
    return S1
# print(succ_star({1}, E))

def pred_star(S, E_inv):
    """
    Renvoie la fermeture transitive des prédécesseurs des sommets donnés, c'est à dire tout les sommets depuis lequels ceux données sont atteignables 

    Paramètres :
    S : ensemble de sommets des quels on cherche les prédécesseurs
    E_inv : les successeurs inversés de chaque sommet du graphe

    Retour : prédécesseurs de S - tout sommet depuis lequels S est atteignable (set)
    """
    S0 = S
    S1 = S0.union(pred(S0, E_inv))
    while S1 != S0 :
            S0 = S1
            S1 = pred_star(S0, E_inv)
    return S1
# print(pred_star({1}, E))


#ALGORITHME DE DIJSKTRA
def dijkstra(depart, arrivee, V, E):
    """
    Utilise l'Algorithme de Dijsktra pour déterminer le plus court chemin entre deux sommets données

    Paramètres: 
    départ : sommet d'origine
    arrivée : sommet d'arrivée
    V : liste des sommets du graphe
    E : les successeurs et le poids de chaque sommet du graphe

    Retour: distance minimale  du chemin entre départ et arrivée, liste des sommets correspondant au chemin suivi (tuple)
    """
    couts = {v: float('inf') for v in V}
    couts[depart] = 0
    visites = set()
    pred = {v: None for v in V}
    for _ in range(len(V)): # Chercher le sommet non visité avec le plus petit coût
        min_cout = float('inf')
        u = None
        for sommet in V: 
            if sommet not in visites and couts[sommet] < min_cout:
                min_cout = couts[sommet]
                u = sommet
        if u is None:
            break
        visites.add(u) #update dus coûts
        for voisin in E[u - 1]:  # u - 1 pour accéder à la bonne case car commence à index 0
            voisin_noeud, poids = list(voisin)
            if couts[voisin_noeud] > couts[u] + poids: # si un chemin plus court est trouvé, on le update
                couts[voisin_noeud] = couts[u] + poids
                pred[voisin_noeud] = u
    chemin = [] # Reconstruction du chemin
    current = arrivee
    if couts[arrivee] == float('inf'):
        return None, []  # Aucun chemin trouvé
    while current is not None:
        chemin.insert(0, current)
        current = pred[current]
    return couts[arrivee], chemin

#VALEURS DE TEST 
v_412 = {1, 2, 3, 4, 5}
suiv_412 = [{(5, 4), (2, 15)}, set(), {(4, 2), (2, 3)}, {(1, 10), (4, 3)}, {(4, 5), (3, 7)}]
v_63 = {1,2,3,4,5,6}
suiv_63 = [{(2,4),(5,6)},{(2,5)},{(2,15),(6,10)},{(3,7),(2,8)},{(4,3)},{(2,3),(5,2),(6,7)}] 

#TESTS
cout, chemin = dijkstra(1, 2, v_412, suiv_412)
assert 14 == cout
assert [1, 5, 3, 2] == chemin
cout63,chemin63 = dijkstra(6,3,v_63,suiv_63)
assert 12 == cout63
assert [6, 5, 4, 3] == chemin63
