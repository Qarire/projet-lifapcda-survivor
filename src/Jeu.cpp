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
    
}

Personnage Jeu::getPersonnage() const {

    return joueur;
}

Terrain Jeu::getTerrain() const {
    
    return map;
}


void Jeu::degats_collision(const Terrain &map, Monstre &mob, Personnage &joueur, Projectile &proj) {

    
}

