#ifndef _MONSTRE
#define _MONSTRE

#include<iostream>
#include"terrain.h"

using namespace std;



class Monstre 
{
	private:
	/**
  	 @brief x,y : les composantes du monstre, pv: ses pint de vie
  	 * */
	int x,y;
	int pv;
	
	public :
	 /**
     	@brief Constructeur par défaut de la classe: initialise la position de monstre, ses points de vie
    	 **/
    	 
     	monstre();
    	 /**
    	 @brief destructeur par défaut de la classe: initialise la position de monstre, ses points de vie
   	  **/
   	  
   	  ~monstre();
   	   /**
   	  @brief fonctions permettant de gerer et modifier les coordonnées des monstre sur le terrain 
   	  **/
   	  
	void depGauche (const Terrain &t);
	void depDroite (const Terrain &t);
	void depHaut   (const Terrain &t);
	void depBas    (const Terrain &t);
	
	/**
     	@brief accesseur pour récuperer les coordonnées x,y des monstres, et leurs points de vie
     	**/
     	
	int getPV();
	int getX();
	int getY();
	 
	/**
     	@brief retourne un booleen qui indique si le monstre et mort ou pas
     	**/
	bool enVie();
	
	/**
     	@brief procédure qui permet au monstre de suivre le pernonnage
     	**/
	void poursuitePerso(const Terrain &t, const Personnage &p);
		 
};

#endif
