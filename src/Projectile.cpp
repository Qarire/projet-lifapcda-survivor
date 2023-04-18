#include "Projectile.h"
#include "Vecteur.h"
#include <iostream>

using namespace std;

Projectile::Projectile() {
    p = Vecteur();   
    v = Vecteur();      
}

Projectile::Projectile(Vecteur pos, Vecteur vit, int hp){
    p = pos;                // Notamment le Vecteur pos du Personnage
    v = vit;  
    p_pv = hp;              
}


Projectile::~Projectile() {

}

int Projectile::getPV() const {
    return p_pv;
}

void Projectile::setPV(int hp){
    p_pv=hp;
}

bool Projectile::enVie() const{
    
    return (p_pv!=0) ;
}

void Projectile::depDroite(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setX(p.getX() + PR_DIST);
	}
}
void Projectile::depGauche(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setX(p.getX() - PR_DIST);
	}
}
void Projectile::depHaut(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setY(p.getY() - PR_DIST);
	}
}

void Projectile::depBas(const Terrain &t)
{	
	if (t.positionValide(p.getX(),p.getY()))
	{
		p.setY(p.getY() + PR_DIST);
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


//++
void Projectile::ProjectilePoursuiteMonstre(const Vecteur& arrivee, const Terrain &t)
{
    if (p.getX() != arrivee.getX() || p.getY() != arrivee.getY()) {
        if (p.getX() > arrivee.getX()) {
            depGauche(t);
        } else if (p.getX() < arrivee.getX()) {
            depDroite(t);
        }
        if (p.getY() > arrivee.getY()) {
            depHaut(t);
        } else if (p.getY() < arrivee.getY()) {
            depBas(t);
        }
    }
}

