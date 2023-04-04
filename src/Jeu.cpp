#include "Jeu.h"


#include <ctime>
#include <iostream>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

using namespace std;

Jeu::Jeu() {
    map = Terrain(1900,1024);
    joueur = Personnage(Vecteur(950,512),100);
    mob.push_back(Monstre(Vecteur(45,25),1));
    proj.push_back(Projectile(joueur.getPos(),Vecteur()));
}
Jeu::~Jeu(){
}
/*  
int Jeu::gettemps() const
{
    return temps;
}

void Jeu::settemps(int t)
{
    temps=t;
}
*/

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
    //Création d'un monstre avec x pv aleatoirement sur la map en fin de tableau*/
    mob.push_back(Monstre(Vecteur(rand()%map.getDimx(),rand()%map.getDimy()),1));
        

}

void Jeu::genereProjectile(const Personnage &joueur){ 

    proj.push_back(Projectile(joueur.getPos(),Vecteur())); //Création d'un projectile sur la position du joueur avec une vitesse par défaut
}


void Jeu::degats_collision_mob(const Terrain &map, Monstre &mob, Personnage &joueur) {

    int new_pv_mob;
    int new_pv_joueur;
    
    if(joueur.getPos() == mob.getPos())
    {
        new_pv_joueur = joueur.getPV() - 20; //prend x points de degats par mob
        joueur.setPV(new_pv_joueur);
        
        new_pv_mob = mob.getPV() - 1 ;
        mob.setPV(new_pv_mob);
    }


}

void Jeu::degats_collision_proj(const Terrain &map, Monstre &mob, Projectile &proj) {

    int new_pv_mob;

    if(proj.getpos() == mob.getPos())
    {
        new_pv_mob = mob.getPV() - 1; //prend x points de degats par projectile
        mob.setPV(new_pv_mob);
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
            break;

        case 'o' :
            genereProjectile(joueur);
            break;

    }

    return false;
}

void Jeu::actionAutomatiques() {
    
    
    

    vector<Monstre>::iterator it;
    int i=0;
    
    for (auto it = mob.begin(); it != mob.end(); ++it)
    {
        
        if(!mob.at(i).enVie())
        {
            mob.erase(it);
        }
        
        mob.at(i).poursuitePerso(map,joueur);
           
        degats_collision_mob(map,mob.at(i),joueur);
        
        for(unsigned int y=0; y<proj.size(); y++) {
            
            proj.at(y).depAuto(map);
            degats_collision_proj(map,mob.at(i),proj.at(y));
        }

        i++;
    }
    
   
    
    
}