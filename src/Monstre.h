#ifndef _MONSTRE
#define _MONSTRE

#include<iostream>
#include"Terrain.h"
#include"Vecteur.h"
#include"Personnage.h"
#include <vector>
#define DIST 3
using namespace std;



class Monstre 
{
	private:
	/**
  	 @brief x,y : les composantes du monstre, pv: ses pint de vie
  	 * */
	Vecteur m_pos;
	int m_pv;
	
	public :
	 /**
     	@brief Constructeur par défaut de la classe: initialise la position de monstre, ses points de vie
    	 **/
    	 
     	Monstre();
    	 /**
    	 @brief destructeur par défaut de la classe: initialise la position de monstre, ses points de vie
   	  **/
	 	Monstre(Vecteur p, int hp);
		/** @brief Constructeur  */


   	  	~Monstre();
   	   	/**
   	  	@brief fonctions permettant de gerer et modifier les coordonnées des monstre sur le terrain 
   	  	**/
   	  
		void depGauche (const Terrain &t);
		void depDroite (const Terrain &t);
		void depHaut   (const Terrain &t);
		void depBas    (const Terrain &t);
	
	/**
     	@brief accesseur pour récuperer les points de vie d'un monstre
     	**/
	int getPV() const;
	
	void setPV(int hp);
	/** @brief Mutateur pour modifier les points de vie d'un monstre*/
	
	/**
     	@brief accesseur pour récuperer les coordonnées x,y d'un monstre
     	**/
	Vecteur getPos() const;
	 
	/**
     	@brief retourne un booleen qui indique si le monstre et mort ou pas
     	**/
	void setPos(Vecteur position);
	/** @brief modifie le vecteur position du monstre */
	bool enVie() const;
	/* @brief renvoie true si le monstre est en vie et false si le monstre est mort */
	
	void poursuitePerso(const Terrain &t, const Personnage &p);
	/**
     	@brief procédure qui permet au monstre de suivre le pernonnage
    **/	 

   void deplacementNaturel(const Terrain &t);
};

#endif
