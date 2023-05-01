#ifndef _PROJECTILE_H
#define _PROJECTILE_H
#define PR_DIST 5
#include "Vecteur.h"
#include "Terrain.h"


class Projectile {
    private :
	
	Vecteur p,v;  		/** @brief position du projectile */
	int p_pv;			/** @brief Points de vie du projictile  */
	bool hasTarget; 	/** @brief indique si le projectile a déjà choisi une cible */
    
	public:

		bool col_proj_mob;
		/** @brief booléan utiliser pour gérer le son de collisions **/

		bool enVie() const;
		/** @brief booléan utiliser pour détruir un projectile une fois qu'il touche un monstre **/

		Projectile();
		/** @brief Constructeur par défaut du projectile **/

		Projectile(Vecteur pos, Vecteur vit, int hp);
		/** @brief Constructeur par copie */

		~Projectile();
		/** @brief Destructeur du projectile **/

		Vecteur getpos() const;
    	/** @brief recupere la position du projectile **/
    	
		void setpos(Vecteur newpos);
		/** @brief Mutateur pour modifier la position d'un projectile*/

		void depDroite (const Terrain &t);
		/** @brief deplacement droite projectile
		 * @param le terrain	*/

		void depGauche (const Terrain &t);
		/** @brief deplacement gauche projectile
		 * @param le terrain	*/

		void depHaut (const Terrain &t);
		/** @brief deplacement haut projectile 
		 * @param le terrain	*/

		void depBas (const Terrain &t);
		/** @brief deplacement bas projectile 
		 * @param le terrain		*/

    	Vecteur getvit() const;
		/** @brief accesseur pour récuperer la vitesse */
		 
		void ProjectilePoursuiteMonstre(const Vecteur& arrivee, const Terrain &t);
		/** @brief fonction permet au projectile de suivre un monstre 
		 *  @param le terrain et le vecteur d'arrivé	*/

		int getPV() const;
		/** @brief accesseur pour récuperer les points de vie d'un monstre**/
	
		void setPV(int hp);
		/** @brief Mutateur pour modifier les points de vie d'un monstre*/
		/** @param un entier pour les points de vie **/

		bool getTarget() const;
		/** @brief accesseur pour récuperer le booléan hasTarget **/

		/** @brief Mutateur pour modifier le booléan hasTarget*/
		void setTarget(bool hasTarget);	
};

#endif
