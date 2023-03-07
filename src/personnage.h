#ifndef _PERSONNAGE_H
#define _PERSONNAGE_H

#include "Projectile.h"
#include "Terrain.h"

class Personnage {
private :
	int x,y; /* @brief les coordonnées x,y de notre personnage */
	int pv; /* @brief les points de vie de notre personnage */
	Projectile proj; /* @brief le projectile qu'il va tirer sur les monstres */
	
public :
	Personnage(); /* @brief constructeur du personnage */
	~Personnage(); /* @brief destructeur */
	void depGauche(const Terrain &t);
	/* @brief procédure pour se déplacer à gauche 
	@param le terrain */
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
	int getX() const;
	/* @brief renvoie la position en X du personnage */
	int getY() const;
	/* @brief renvoie la position en Y du personnage */
	bool enVie() const;
	/* @brief renvoie true si le personnage est en vie et false si le personnage est mort */
}


#endif
