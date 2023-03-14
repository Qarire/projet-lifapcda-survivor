#include "Personnage.h"
#include"Terrain.h"
#include<iostream>

using namespace std;
	
Personnage::Personnage()  // initialiser la position du joueur au milieu du terrain
{
	pos.setX(dimx/2);
	pos.setY(dimy/2);
	setPV(100);
}

Personnage::~Personnage()   // destructeur
{
	Vecteur init; //mettre tous à zero
	init.x=0;
	init.y=0;
	pos.setX(init.x);
	pos.setY(init.y);
	setPV(0); 
}
//--------------------- Gérer les déplacements et la position du personnage : ----------------------- 
void Personnage::depGauche(const Terrain &t)
{	
	Vecteur dep;
	dep.x=1; dep.y=0;
	pos.setPos(pos.getPos()-dep);
}

void Personnage::depDroite(const Terrain &t)
{	
	Vecteur dep;
	dep.x=1; dep.y=0;
	pos.setPos(pos.getPos()+dep);
}

void Personnage::depHaut(const Terrain &t)
{
	Vecteur dep;
	dep.x=0; dep.y=1;
	pos.setPos(pos.getPos()+dep);
}

void Personnage::depBas(const Terrain &t)
{
	Vecteur dep;
	dep.x=0; dep.y=1;
	pos.setPos(pos.getPos()-dep);
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
	x=position.x;
	y=position.y;
}

