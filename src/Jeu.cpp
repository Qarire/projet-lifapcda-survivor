#include "Jeu.h"
#include "Terrain.h"
#include "Personnage.h"
#include "Monstre.h"
#include "Projectile.h"
#include <vector>

#include <iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

Jeu::Jeu() {
    map = Terrain(140,30);
    joueur = Personnage(Vecteur(5,5),100);
    mob.push_back(Monstre());
    proj.push_back(Projectile());
}
Jeu::~Jeu(){
    
}
Personnage Jeu::getPersonnage() const {

    return joueur;
}

Terrain Jeu::getTerrain() const {
    
    return map;
}
/*
Monstre Jeu::getMonstre() const {
    
    return mob;
}*/

vector<Monstre> Jeu::getVectorMonstre() const {
    return mob;
}

vector<Projectile> Jeu::getVectorProjectile() const
{
    return proj;
}

void Jeu::genereMonstre(const Terrain &map) {

    srand((unsigned int)time(NULL));
    mob.push_back(Monstre(Vecteur(rand()%map.getDimx(),rand()%map.getDimy()),50)); //Création d'un monstre avec 50pv aleatoirement sur la map
                                                                                   // en fin de tableau
}



void Jeu::genereProjectile(const Personnage &joueur){ 

    proj.push_back(Projectile(joueur.getPos(),Vecteur())); //Création d'un projectile sur la position du joueur avec une vitesse par défaut
}


void Jeu::degats_collision(const Terrain &map, Monstre &mob, Personnage &joueur,const Projectile &proj) {

    if(proj.getpos() == mob.getPos())
    {
        int new_pv_mob = mob.getPV() - 25; //prend 25 points de degats par projectile
        mob.setPV(new_pv_mob);
    }

    if(joueur.getPos() == mob.getPos())
    {
        int new_pv_joueur = joueur.getPV() - 25; //prend 25 points de degats par projectile
        joueur.setPV(new_pv_joueur);
    }
}

bool Jeu::FinJeu (const Personnage &joueur){
    return(joueur.enVie());
}

bool Jeu::actionClavier(const char touche) {
    switch(touche) {
        case 'z' :
            joueur.depHaut(map);
            break;
        
        case 'd' :
            joueur.depDroite(map);
            break;
        
        case 'q' :
            joueur.depGauche(map);
            break;
        
        case 's' : joueur.depBas(map);

    }

    return false;
}

void Jeu::actionAutomatiques() {
    
    for(unsigned int i=0;i<mob.size();i++)
    {
        mob.at(i).poursuitePerso(map,joueur);
    }

}