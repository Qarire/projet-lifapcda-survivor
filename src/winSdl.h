#ifndef WINSDL_H
#define WINSDL_H

#include <SDL2/SDL.h>         
#include <SDL2/SDL_image.h>   
#include <SDL2/SDL_ttf.h>    
#include <SDL2/SDL_mixer.h>

#include "Jeu.h"


//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface * m_surface;
    SDL_Texture * m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



/**
   @brief La classe gerant le jeu avec un affichage SDL
*/
class SDLSimple {

private :

	Jeu jeu;                     /** @brief le jeu*/

    SDL_Window * window;
    SDL_Renderer * renderer;

    /** @brief pour le fonts*/
    TTF_Font * font;
    TTF_Font * font2;
    Image font_im;
    SDL_Color font_color;


                /** @brief pointeurs sur différents sons */
    Mix_Chunk * s_jeu_musique;
    Mix_Chunk * s_menu_musique;
    Mix_Chunk * s_tire_projectile;
    Mix_Chunk * s_degat_projectile;
    Mix_Chunk * s_degat_monstre;
    Mix_Chunk * s_choix_menu;
    Mix_Chunk * s_fin_jeu;
    Mix_Chunk * s_start_effect;
    Mix_Chunk * s_clique_menu;
    
    bool withSound;   /** @brief booléan qui vérifier si le lib du son sont initialiser corectement*/

    /** @brief les images*/
    Image im_personnage;
    Image im_terrain;
    Image im_monstre;
    Image im_projectile;
    Image im_remplirTerrain;
    Image im_menu;

public :

    int menu_active_channel; /** @brief entier tocké le num du canal qui joue la musique du menu **/
    int jeu_active_channel;  /** @brief entier pour socké le num du canal qui joue la musique du  */

    SDLSimple ();                   /** @brief constructeur de la cleasse */
    ~SDLSimple ();                  /** @brief déstructeur de la classe */
    void sdlBoucle ();              /** @brief Boucle du jeu */
    void menuBoucle ();             /** @brief Boucle du menu */
    void sdlAff ();                 /** @brief procédure qui affiche jeu */
    void menuAff();                 /** @brief Affiche le menu du jeu */
    void menuAfficheInfoDev() ;     /** @brief Afficher le menu info devloppeurs */
    void menuAfficheDescription();  /** @brief Afficher un menu sur la discription du jeu */
    void menuAfficheGameOver();     /** @brief Afficher le menu de fin du jeu */

};

#endif