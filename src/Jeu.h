#ifndef _JEU_H
#define _JEU_H

#include "Terrain.h"
#include "Personnage.h"
#include "Monstre.h"
#include "Projectile.h"
#include "vector"

class Jeu {
private:
    Terrain map;
    Personnage joueur;
    vector<Projectile> proj;
    vector<Monstre> mob;

public:
    Jeu();
    /** @brief Constructeur par défaut **/

    ~Jeu();
    /** @brief Destructeur par défaut **/

    Personnage getPersonnage() const;
    /** @brief recupere le Personnage **/

    Terrain getTerrain() const;
    /** @brief recupere le Terrain **/

    Monstre getMonstre() const;
    /** @brief recupere le Monstre **/

    void degats_collision (const Terrain &map, Monstre &mob, Personnage &joueur,const Projectile &proj);
    /** @brief Procédure qui gère les degats infliger entre un différente entité **/

    void genereMonstre(const Terrain &map);
    /** @brief Genere un monstre aleatoirement sur le terrain **/

    void genereProjectile(const Personnage &joueur);
    /** @brief genere un Projectile sur la coordonnée du personnage **/

    void FinJeu (const Personnage &joueur);
    /** @brief Test si le jeu est terminer ou non **/





};


#endif
