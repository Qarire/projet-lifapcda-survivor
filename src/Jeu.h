#ifndef _JEU_H
#define _JEU_H

#include "Terrain.h"
#include "Personnage.h"
#include "Monstre.h"
#include "Projectile.h"
#include <vector>

class Jeu {
private:
    int temps;               /** @brief temps*/
    Terrain map;            /** @brief terrain*/
    Personnage joueur;      /** @brief le personnage*/
    vector<Projectile> proj;/** @brief tableau dynamique de projectiles*/
    vector<Monstre> mob;    /** @brief tableau dynamique de monstres*/

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

    vector<Monstre> getVectorMonstre() const;
    /** @brief recupere le tableau dynamique de monstre */

    vector<Projectile> getVectorProjectile() const;
    /** @brief recupere le tableau dynamique de projectile*/

    void degats_collision_mob(const Terrain &map, Monstre &mob, Personnage &joueur);
    /** @brief Procédure qui gère les degats infliger entre le personnage et un monstre
     @param le terrain, le monstre et le personnage **/

    void degats_collision_proj(const Terrain &map, Monstre &mob, Projectile &proj);
     /** @brief Procédure qui gère les degats infliger entre un monstre et un projectile
     *@param le terrain, le monstre et le projectile **/

    void genereMonstre(const Terrain &map);
    /** @brief Genere un monstre aleatoirement sur le terrain 
     *@param le terrain **/
    
    void genereProjectile(const Personnage &joueur);
    /** @brief genere un Projectile sur la coordonnée du personnage 
     * @param le personnage**/

    bool FinJeu (const Personnage &joueur);
    /** @brief Test si le jeu est terminer ou non 
     * @param le personnage **/

    bool actionClavier(const char touche);
    /** @brief gerer les actions du clavier 
     * @param   la touche sur laquelle onappuie  */

    void actionAutomatiques();
    /** @brief action automatique, notamment déplacement auto des monstres et tire projectile*/

    void verifierLimitesJoueur(const Terrain &map);
    /** @brief permet les déplacement du personnage à travers le bordure du terrain
     * @param le terrain    */

};

#endif

