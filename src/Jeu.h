#ifndef _JEU_H
#define _JEU_H

#include "Terrain.h"
#include "Personnage.h"
#include "Monstre.h"
#include "Projectile.h"
#include "vector"

class Jeu {
private:
    int temps;
    Terrain map;
    Personnage joueur;
    vector<Projectile> proj;
    vector<Monstre> mob;

public:
    /** @brief recupere le temps **/
    int gettemps()const;

/** @brief modifier le temps **/
    int settemps(int t);

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

    vector<Monstre> getVectorMonstre() const;
    /** @brief recupere le tableau dynamique de monstre */

    vector<Projectile> getVectorProjectile() const;
    /** @brief recupere le tableau dynamique de projectile*/

    void degats_collision (const Terrain &map, Monstre &mob, Personnage &joueur,const Projectile &proj);
    /** @brief Procédure qui gère les degats infliger entre un différente entité **/

    void genereMonstre(const Terrain &map);
    /** @brief Genere un monstre aleatoirement sur le terrain **/

    void genereProjectile(const Personnage &joueur);
    /** @brief genere un Projectile sur la coordonnée du personnage **/

    bool FinJeu (const Personnage &joueur);
    /** @brief Test si le jeu est terminer ou non **/


    bool actionClavier(const char touche);
    /** @brief action clavier */

    void actionAutomatiques();
    /** @brief action automatique, notamment déplacement auto des monstres et tire projectile*/
    
    void dessinBordures(const Terrain &map);
     /** @brief Dessiner les bordures de la map */
};


#endif
