#include "Projectile.h"
#include "Vecteur.h"
#include <iostream>

using namespace std;

Projectile::Projectile() {
    p = Vecteur();   
    v = Vecteur();      
}

Projectile::Projectile(Vecteur pos, Vecteur vit){
    p = pos;                // Notamment le Vecteur pos du Personnage
    v = vit;                
}

Projectile::~Projectile(){
    p = nullptr;
    v = nullptr;
}

Vecteur Projectile::getpos() const {

    return p;
}

Vecteur Projectile::getvit() const {

    return v;
}




    
