#include <iostream>
#include "Vecteur.h"
#include "Terrain.h"
#include "Monstre.h"
using namespace std;


Monstre::Monstre(){
    m_pos = Vecteur();
	m_pv = 50;
}

Monstre::Monstre(Vecteur p, int hp){
    m_pos=p;
    m_pv=hp;
}

Monstre::~Monstre(){
    m_pos.setX(0);
	m_pos.setY(0);
	m_pv=0;
}
int Monstre::getPV() const {
    return m_pv;
}

void Monstre::setPV(int hp){
    m_pv=hp;
}

Vecteur Monstre::getPos() const{
    return m_pos;
}
void Monstre::setPos(Vecteur position) // Modifier le vecteur position du personnage
{
	m_pos = position;
}



bool Monstre::enVie() const{
    if (m_pv==0){
        return false;
    }
    else return true;
}


void Monstre::depGauche(const Terrain &t)
{	
	if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setX(m_pos.getX() -0.5);
	}
}
void Monstre::depDroite(const Terrain &t)
{	
	if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setX(m_pos.getX() +0.5);
	}
}
void Monstre::depHaut(const Terrain &t){
{
	if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setY(m_pos.getY() -0.5);
	}
}
}

void Monstre::depBas(const Terrain &t)
{
    if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setY(m_pos.getY() +0.5);
	}
}

void Monstre::poursuitePerso(const Terrain &t, const Personnage &p){
    if (t.positionValide(m_pos.getX(),m_pos.getY())){
        if (p.getPos().getX()>m_pos.getX()) depDroite(t);
        if (p.getPos().getX()<m_pos.getX()) depGauche(t);
        if (p.getPos().getY()>m_pos.getY()) depBas(t);
        if (p.getPos().getY()<m_pos.getY()) depHaut(t);
    }
    

}