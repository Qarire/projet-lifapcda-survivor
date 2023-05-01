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
	col_mob_per=false;
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
		m_pos.setX(m_pos.getX() - DIST);
	}
}
void Monstre::depDroite(const Terrain &t)
{	
	if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setX(m_pos.getX() + DIST);
	}
}
void Monstre::depHaut(const Terrain &t){
{
	if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setY(m_pos.getY() - DIST);
	}
}
}

void Monstre::depBas(const Terrain &t)
{
    if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		m_pos.setY(m_pos.getY() + DIST);
	}
}


// poursuitePerso : vrsion 1
/* void Monstre::poursuitePerso(const Terrain &t, const Personnage &p){  
    if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
			  if (p.getPos().getX()>m_pos.getX()) depDroite(t);

			  if (p.getPos().getX()<m_pos.getX()) depGauche(t);

			  if (p.getPos().getY()>m_pos.getY()) depBas(t);

			  if (p.getPos().getY()<m_pos.getY()) depHaut(t);
	}
}
*/


// poursuitePerso : vrsion 2
/* void Monstre::poursuitePerso(const Terrain &t, const Personnage &p){  
    if (t.positionValide(m_pos.getX(),m_pos.getY()))
	{
		if ((p.getPos().getX()<m_pos.getX()) && (p.getPos().getY()<m_pos.getY()))
		{
			if ( t.getDistance( // On compare la distance entre  --- perso haut gauche, m bas droite
				p.getPos().getX(),p.getPos().getY(),p.getPos().getX(), m_pos.getY() ) 
					> t.getDistance(
						m_pos.getX(),m_pos.getY(),p.getPos().getX(), m_pos.getY()  )
				)
			{
				depHaut(t);
			} else depGauche(t);
		}

		if ((p.getPos().getX()>m_pos.getX()) && (p.getPos().getY()>m_pos.getY()) )
		{
			if ( t.getDistance( // On compare la distance entre  ---> monstre haut gauche, perso bas droite
					m_pos.getX(), m_pos.getY(),m_pos.getX(),p.getPos().getY() ) 
						> t.getDistance(
							p.getPos().getX(),p.getPos().getY(),m_pos.getX(),p.getPos().getY()  )
					)
				{
					depBas(t);
				} else depDroite(t);
		}

		if ( (p.getPos().getX()>m_pos.getX()) && (p.getPos().getY()<m_pos.getY()))
		{
			if ( t.getDistance( // On compare la distance entre  ---> monstre bas droite, perso haut gauche
					 p.getPos().getX(),p.getPos().getY(),m_pos.getX(),p.getPos().getY() ) 
						> t.getDistance(
							 m_pos.getX(), m_pos.getY(),m_pos.getX(),p.getPos().getY()  )
					)
				{
					depDroite(t);
				} else depHaut(t);
		}

		if ((p.getPos().getX()<m_pos.getX()) && (p.getPos().getY()>m_pos.getY()))
		{
			if ( t.getDistance( // On compare la distance entre  ---> monstre haut droite, perso bas gauche
					 p.getPos().getX(),p.getPos().getY(),m_pos.getX(),p.getPos().getY() ) 
						> t.getDistance(
							 m_pos.getX(), m_pos.getY(),m_pos.getX(),p.getPos().getY()  )
					)
				{
					depGauche(t);
				} else depBas(t);
		}

		// Monstre méme ligne ou colone que personnage 
		if ((p.getPos().getX()==m_pos.getX()) && (p.getPos().getY()<m_pos.getY())) depHaut(t);
		if ((p.getPos().getX()==m_pos.getX()) && (p.getPos().getY()>m_pos.getY())) depBas(t);
		if ((p.getPos().getX()<m_pos.getX()) && (p.getPos().getY()==m_pos.getY())) depGauche(t);
		if ((p.getPos().getX()>m_pos.getX()) && (p.getPos().getY()==m_pos.getY())) depDroite(t);
    }
}*/


// poursuitePerso : version 3

void Monstre::poursuitePerso(const Terrain& t, const Personnage& p) {  
	if (!t.positionValide(m_pos.getX(), m_pos.getY())) { 
	return;
	}
	// Obtenir la position du joueur et du monstre
	const int mX = m_pos.getX();
	const int mY = m_pos.getY();
	const int pX = p.getPos().getX();
	const int pY = p.getPos().getY();

	// Si le monstre et le joueur sont sur la même colonne ou ligne, se déplacer dans la direction correspondante
	if (pX == mX) {
		if (pY < mY) {
			depBas(t);  // Inverser la direction
		} else if (pY > mY) {
			depHaut(t);  // Inverser la direction
		}
		return;
	}
	if (pY == mY) {
		if (pX < mX) {
			depDroite(t);  // Inverser la direction
		} else if (pX > mX) {
			depGauche(t);  // Inverser la direction
		}
		return;
	}

	// Calculer la distance entre le joueur et le monstre dans chaque direction
	const int dxG = mX - pX;
	const int dxD = pX - mX;
	const int dyH = mY - pY;
	const int dyB = pY - mY;

	// Déterminer la direction de déplacement avec la distance la plus courte
	if (dxG > dyH && dxG > dyB) {  // Inverser les conditions pour rapprocher le monstre
		depGauche(t);
	} else if (dxD > dyH && dxD > dyB) {
		depDroite(t);
	} else if (dyH > dxG && dyH > dxD) {
		depHaut(t);
	} else {
		depBas(t);
	}
}

