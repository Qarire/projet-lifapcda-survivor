#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

#include "Projectile.h"
#include "Terrain.h"
#include "Vecteur.h"

using namespace std;

class Personnage {

private :
	Vecteur pos; /* @brief les coordonnées x,y de notre personnage */
	Vecteur pos_txt;
	int pv; /* @brief les points de vie de notre personnage */
	
public :
	Personnage();
	 /* @brief constructeur du personnage */

	 Personnage(Vecteur p, int hp);
	/** @brief constructeur par copie*/

	
	~Personnage(); 
	/* @brief destructeur */
	
	
	
	void depGauche(const Terrain &t);
	/* @brief procédure pour se déplacer à gauche 
	@param le terrain */
	void depDroite(const Terrain &t);
	/* @brief procédure pour se déplacer à droite 
	@param le terrain */
	void depHaut(const Terrain &t);
	/* @brief procédure pour se déplacer en haut 
	@param le terrain */
	void depBas(const Terrain &t);
	/* @brief procédure pour se déplacer en bas 
	@param le terrain */

	int getPV() const;
	/* @brief renvoie les points de vie du personnage */
	void setPV(int hp);
	/** @brief modifie les points de vie du personnage */
	Vecteur getPos()const;
	/* @brief renvoie la position du personnage */
	bool enVie() const;
	/* @brief renvoie true si le personnage est en vie et false si le personnage est mort */
	void setPos(Vecteur position);
	/** @brief modifie le vecteur position du personnage */
};


#endif
