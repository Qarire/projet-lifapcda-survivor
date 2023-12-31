#include "Personnage.h"
#include"Terrain.h"
#include<iostream>

using namespace std;
	
Personnage::Personnage()  // initialiser la position du joueur au milieu du terrain
{
	pos = Vecteur(25,25);
	pv = 100;
}

Personnage::Personnage(Vecteur p, int hp) {
	pos = p;
	pv = hp;
}


Personnage::~Personnage()   // destructeur
{
	pos.setX(0);
	pos.setY(0);
	pv=0;
}

//--------------------- Gérer les déplacements et la position du personnage : ----------------------- 
void Personnage::depGauche(const Terrain &t)
{	
	if (t.positionValide(pos.getX(),pos.getY()))
	{
		pos.setX(pos.getX() -10.1);
		if (pos.getX()<=0) {
			pos.setX(0);
		}
	}
	
}

void Personnage::depDroite(const Terrain &t)
{	
	if (t.positionValide(pos.getX(),pos.getY()))
	{
		pos.setX(pos.getX() +10.1);
		if (pos.getX()>=t.getDimx()) {
			pos.setX(t.getDimx());
		}
	}
	
}

void Personnage::depHaut(const Terrain &t)
{
	if (t.positionValide(pos.getX(),pos.getY()))
	{
		pos.setY(pos.getY() -10.1);
		if (pos.getY()<=0) {
			pos.setY(0);
		}
	}
	
}

void Personnage::depBas(const Terrain &t)
{
	if (t.positionValide(pos.getX(),pos.getY()))
	{
		pos.setY(pos.getY() +10.1);
		if (pos.getY()>=t.getDimy()) {
			pos.setY(t.getDimy());
		}
	}
	
}
//--------------------------------------------------------------------------------------------------



int Personnage::getPV() const
{
	return pv;
}

void Personnage::setPV(int hp)
{
	pv=hp;
}

Vecteur Personnage::getPos()const // Recuperer les coordonnées du personnage
{
	return pos;
}


bool Personnage::enVie() const  // tant que les pv du perso sont superieur à 0, il est en vie
{
	return ( getPV()>0);
}

void Personnage::setPos(Vecteur position) // Modifier le vecteur position du personnage
{
	pos = position;
}

/* void Personnage::setPos(const float x, const float y) // Modifier le vecteur position du personnage
{
	pos.setX(x);
	pos.setY(y);
}
*/