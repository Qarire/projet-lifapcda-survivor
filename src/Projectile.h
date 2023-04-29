#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#define PR_DIST 5
#include "Vecteur.h"
#include "Terrain.h"


class Projectile {
    private :
	
	Vecteur p,v;  // position du projectile
	int p_pv;		// Points de vie du projictile 
	bool hasTarget; // indique si le projectile a déjà choisi une cible
    public:

		bool enVie() const;
		/** @brief booléan utiliser pour détruir un projectile une fois qu'il touche un monstre **/

		Projectile();
		/** @brief Constructeur par défaut du projectile **/

		Projectile(Vecteur pos, Vecteur vit, int hp);
		/** @brief Constructeur */

		~Projectile();
		/** @brief Destructeur du projectile **/

		Vecteur getpos() const;
    	/** @brief recupere la position du projectile **/
    	
		/** @brief Mutateur pour modifier la position d'un projectile*/
		void setpos(Vecteur newpos);

		void depDroite (const Terrain &t);
		/** @brief deplacement droite projectile*/

		void depGauche (const Terrain &t);
		/** @brief deplacement gauche projectile*/

		void depHaut (const Terrain &t);
		/** @brief deplacement haut projectile*/

		void depBas (const Terrain &t);
		/** @brief deplacement bas projectile*/

		void depAuto (const Terrain &t);
		/** @brief deplacement auto projectile*/
		
    	Vecteur getvit() const;
		/** @brief accesseur pour récuperer la vitesse */
		 
		void ProjectilePoursuiteMonstre(const Vecteur& arrivee, const Terrain &t);
		/** @brief fonction permet au projectile de suivre un monstre */

		/** @brief accesseur pour récuperer les points de vie d'un monstre**/
		int getPV() const;
	
		/** @brief Mutateur pour modifier les points de vie d'un monstre*/
		void setPV(int hp);

		/** @brief accesseur pour récuperer le booléan hasTarget**/
		bool getTarget() const;

		/** @brief Mutateur pour modifier le booléan hasTarget*/
		void setTarget(bool hasTarget);	
};

#endif
