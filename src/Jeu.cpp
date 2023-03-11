#include "Jeu.h"
#include "Terrain.h"
#include "Personnage.h"
#include "Monstre.h"
#include "Projectile.h"
#include "vector"
#include <iostream>

using namespace std;

Jeu::Jeu() {

    map = Terrain();
    joueur = Personnage();
    mob.at(0) = Monstre();
    proj.at(0) = Projectile();
}

Personnage Jeu::getPersonnage() const {

    return joueur;
}

Terrain Jeu::getTerrain() const {
    
    return map;
}

void Jeu::genereMonstre(const Terrain &map) {

    mob.push_back(Monstre(Vecteur(rand()%map.getDimx(),rand()%map.getDimy()),1));
}



void Jeu::genereProjectile(const Personnage &joueur){ 

    proj.push_back(Projectile(joueur.getPos(),Vecteur()));
}


void Jeu::degats_collision(const Terrain &map, Monstre &mob, Personnage &joueur, Projectile &proj) {

    
}

