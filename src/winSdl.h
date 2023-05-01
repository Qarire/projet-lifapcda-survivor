#ifndef WINSDL_H
#define WINSDL_H

#include <SDL2/SDL.h>         
#include <SDL2/SDL_image.h>   
#include <SDL2/SDL_ttf.h>    
#include <SDL2/SDL_mixer.h>

#include "Jeu.h"
#include "menu.h"

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
    La classe gerant le jeu avec un affichage SDL
*/
class SDLSimple {

private :

	Jeu jeu;

    SDL_Window * window;
    SDL_Renderer * renderer;

    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;

    Mix_Chunk * s_jeu_musique;
    Mix_Chunk * s_menu_musique;
    Mix_Chunk * s_tire_projectile;
    Mix_Chunk * s_degat_projectile;
    Mix_Chunk * s_degat_monstre;
    Mix_Chunk * s_choix_menu;
    Mix_Chunk * s_fin_jeu;
    Mix_Chunk * s_start_effect;
    Mix_Chunk * s_clique_menu;
    
    bool withSound;

    Image im_personnage;
    Image im_terrain;
    Image im_monstre;
    Image im_projectile;
    Image im_remplirTerrain;
    Image im_menu;


    bool souris;
    bool touche;
public :

    int menu_active_channel; //Stocké le num du canal qui joue la musique du menu
    int jeu_active_channel; //Stocké le num du canal qui joue la musique du jeu

    SDLSimple ();
    ~SDLSimple ();
    void sdlBoucle (); //Boucle jeu
    void menuBoucle ();//Boucle menu
    void sdlAff ();    // Affiche jeu
    void menuAff();    //Affiche menu jeu
    void menuAfficheInfoDev() ; //Afficher INfo dev
    void menuAfficheDescription();  //Afficher une discription du jeu
    void menuAfficheGameOver(); //Afficher GAME OVER

};



#endif