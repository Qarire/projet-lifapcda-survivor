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


Projectile::~Projectile() {

}

void Projectile::depDroite(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setX(p.getX() +1);
	}
}
void Projectile::depGauche(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setX(p.getX() -1);
	}
}
void Projectile::depHaut(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setY(p.getY() -1);
	}
}

void Projectile::depBas(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setY(p.getY() +1);
	}
}


void Projectile::depAuto (const Terrain &t) {
    if (t.positionValide(p.getX(),p.getY())) {
        depDroite(t);
    }

}


Vecteur Projectile::getpos() const {

    return p;
}

Vecteur Projectile::getvit() const {

    return v;
}




    
