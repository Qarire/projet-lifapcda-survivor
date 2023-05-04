#include <cassert>
#include <time.h>
#include <stdlib.h>
#include "winSdl.h"
#include<unistd.h>
#include <iostream>
#include<time.h>
#include <ctime>

using namespace std;

// ============= CLASS IMAGE =============== //

Image::Image () : m_surface(nullptr), m_texture(nullptr), m_hasChanged(false) {
}

Image::~Image()
{
    SDL_FreeSurface(m_surface);
    SDL_DestroyTexture(m_texture);

    m_surface = nullptr;
    m_texture = nullptr;
    m_hasChanged = false;
}

void Image::loadFromFile (const char* filename, SDL_Renderer * renderer) {
    m_surface = IMG_Load(filename);
    if (m_surface == nullptr) {
        string nfn = string("../") + filename;
        cout << "Error: cannot load "<< filename <<". Trying "<<nfn<<endl;
        m_surface = IMG_Load(nfn.c_str());
        if (m_surface == nullptr) {
            nfn = string("../") + nfn;
            m_surface = IMG_Load(nfn.c_str());
        }
    }
    if (m_surface == nullptr) {
        cout<<"Error: cannot load "<< filename <<endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(m_surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(m_surface);
    m_surface = surfaceCorrectPixelFormat;

    m_texture = SDL_CreateTextureFromSurface(renderer,surfaceCorrectPixelFormat);
    if (m_texture == NULL) {
        cout << "Error: problem to create the texture of "<< filename<< endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::loadFromCurrentSurface (SDL_Renderer * renderer) {
    m_texture = SDL_CreateTextureFromSurface(renderer,m_surface);
    if (m_texture == nullptr) {
        cout << "Error: problem to create the texture from surface " << endl;
        SDL_Quit();
        exit(1);
    }
}

void Image::draw (SDL_Renderer * renderer, int x, int y, int w, int h) {
    int ok;
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = (w<0)?m_surface->w:w;
    r.h = (h<0)?m_surface->h:h;

    if (m_hasChanged) {
        ok = SDL_UpdateTexture(m_texture,nullptr,m_surface->pixels,m_surface->pitch);
        assert(ok == 0);
        m_hasChanged = false;
    }

    ok = SDL_RenderCopy(renderer,m_texture,nullptr,&r);
    assert(ok == 0);
}

SDL_Texture * Image::getTexture() const {return m_texture;}

void Image::setSurface(SDL_Surface * surf) {m_surface = surf;}

// ============= CLASS SDLJEU =============== //

SDLSimple::SDLSimple () : jeu() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if (TTF_Init() != 0) {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if( !(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        cout << "No sound !!!" << endl;
        //SDL_Quit();
        //exit(1);
        withSound = false;
    }
    else withSound = true;

	int dimx = jeu.getTerrain().getDimx();
	int dimy = jeu.getTerrain().getDimy();

    // Creation de la fenetre
    window = SDL_CreateWindow("Survivor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx+10, dimy+10, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }
    
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

     // IMAGES
    im_personnage.loadFromFile("data/wizard_.png",renderer);
    im_monstre.loadFromFile("data/ghost.png", renderer);
    im_terrain.loadFromFile("data/Black_blocs.jpg", renderer);
    im_projectile.loadFromFile("data/projectile.png", renderer);
    im_remplirTerrain.loadFromFile("data/jqkj.webp", renderer);
    im_menu.loadFromFile("data/High_resolution_wallpaper_background_ID_77701691879.jpg", renderer);
   

  // FONTS
     font = TTF_OpenFont("data/leadcoat.ttf", 72);
    if (font == nullptr)
        font = TTF_OpenFont("../data/contrast.ttf",72);
    if (font == nullptr) {
            cout << "Failed to load contrast.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	    }


      // SONS
    if (withSound)
    {
       s_menu_musique = Mix_LoadWAV("data/Son/menuTrap.mp3");
        if (s_menu_musique == nullptr) 
            s_menu_musique = Mix_LoadWAV("../data/Son/menuTrap.mp3");
        if (s_menu_musique == nullptr) {
                cout << "Failed to load menuTrap.mp3 SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
        s_start_effect = Mix_LoadWAV("data/Son/horror.wav");
        if (s_start_effect == nullptr) 
            s_start_effect = Mix_LoadWAV("../data/Son/horror.wav");
        if (s_start_effect == nullptr) {
                cout << "Failed to load horror.wav SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
        s_choix_menu = Mix_LoadWAV("data/Son/click-for-game-menu-131903.mp3");
        if (s_choix_menu == nullptr) 
            s_choix_menu = Mix_LoadWAV("../data/Son/click-for-game-menu-131903.mp3");
        if (s_choix_menu == nullptr) {
                cout << "Failed to load click-for-game-menu-131903.mp3 SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
        s_fin_jeu = Mix_LoadWAV("data/Son/fail.wav");
        if (s_fin_jeu == nullptr) 
            s_fin_jeu = Mix_LoadWAV("../data/Son/fail.wav");
        if (s_fin_jeu == nullptr) {
                cout << "Failed to load fail.wav SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
        s_jeu_musique = Mix_LoadWAV("data/Son/ambients-for-rituals-04-114793.mp3");
        if (s_jeu_musique == nullptr) 
            s_jeu_musique = Mix_LoadWAV("../data/Son/ambients-for-rituals-04-114793.mp3");
        if (s_jeu_musique == nullptr) {
                cout << "Failed to load ambients-for-rituals-04-114793.mp3 SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
         s_degat_monstre = Mix_LoadWAV("data/Son/damage.wav");
        if (s_degat_monstre == nullptr) 
            s_degat_monstre = Mix_LoadWAV("../data/Son/damage.wav");
        if (s_degat_monstre == nullptr) {
                cout << "Failed to load damage.wav SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
        s_degat_projectile = Mix_LoadWAV("data/Son/metal-hit-84608.wav");
        if (s_degat_projectile == nullptr) 
            s_degat_projectile = Mix_LoadWAV("../data/Son/metal-hit-84608.wav");
        if (s_degat_projectile == nullptr) {
                cout << "Failed to load metal-hit-84608.mp3 SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
        s_tire_projectile = Mix_LoadWAV("data/Son/fire-magic-6947.wav");
        if (s_tire_projectile == nullptr) 
            s_tire_projectile = Mix_LoadWAV("../data/Son/fire-magic-6947.wav");
        if (s_tire_projectile == nullptr) {
                cout << "Failed to load fire-magic-6947.mp3 SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
    }
}

SDLSimple::~SDLSimple () {
    if (withSound) Mix_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLSimple::sdlAff () {

    const Terrain& ter = jeu.getTerrain();
    const Personnage& per = jeu.getPersonnage();
    const vector<Monstre> &mon = jeu.getVectorMonstre();
	const vector<Projectile> &proj= jeu.getVectorProjectile();
    
	SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
     SDL_RenderClear(renderer);


    //Arriere plan Menu
    font_im.setSurface(TTF_RenderText_Solid(font,"** Survivor **",font_color));
	//font_im.loadFromCurrentSurface(renderer);

    //Dessiner l'arrière plan

    int img_dimx =325;
    int img_dimy= 325;
     for(unsigned int x=0; x<jeu.getTerrain().getDimx(); x+=img_dimx) {
        for(unsigned int y=0; y<jeu.getTerrain().getDimy(); y+=img_dimy) 
        {
            im_remplirTerrain.draw(renderer, x,y,img_dimx ,img_dimy);
        }
    }

    //Dessin Personnage
    im_personnage.draw(renderer, per.getPos().getX()-25, per.getPos().getY()-25, 50 ,50);
    
    //Dessin des Monstres
    for(unsigned int i=0;i<mon.size();i++)
    {
        if (mon.at(i).col_mob_per) Mix_PlayChannel(-1,s_degat_monstre,0);
        im_monstre.draw(renderer, mon.at(i).getPos().getX()-12,mon.at(i).getPos().getY()-12,24,24);
    }

    // Affichage des PV
    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    int pv=per.getPV();
    char pv_string[50];
    sprintf(pv_string, " L I F E : %d",pv);
	font_im.setSurface(TTF_RenderText_Solid(font,pv_string,font_color));
	font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTitre;
    positionTitre.x = 20;positionTitre.y = 140;positionTitre.w =150;positionTitre.h = 30;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTitre);

    // Affichage LE NOMBRE DE MONSTRES TUER
    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    int dead=jeu.nb_monstres_tuer;
    char dead_string[50];
    sprintf(dead_string, " M O N S T E R S  D E A D : %d",dead);
	font_im.setSurface(TTF_RenderText_Solid(font,dead_string,font_color));
	font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTitreDead;
    positionTitreDead.x = 20;positionTitreDead.y = 20;positionTitreDead.w =300;positionTitreDead.h = 30;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTitreDead);
    
    //Dessin du terrain
    for(unsigned int i=0;i<ter.getDimx();i++) // 1ere ligne horizontale
	{
		im_terrain.draw(renderer,i,0,10,10);
	}

	for(unsigned int j=0;j<ter.getDimy();j++) //Les 2 lignes verticales
	{
		//win.print(0,j,'*');
        im_terrain.draw(renderer,0,j,10,10);

		//win.print(ter.getDimx()-1,j,'*');
        im_terrain.draw(renderer,ter.getDimx()-1,j,10,10);
	}

	for(unsigned int i=0;i<ter.getDimx();i++) // 2e ligne horizontale
	{
        im_terrain.draw(renderer,i,ter.getDimy()-1,10,10);
	}

    //Dessin projectile

    for(unsigned int i=0;i<proj.size();i++)
	{
        //if (proj.at(i).col_proj_mob) Mix_PlayChannel(-1,s_degat_projectile,0); //colision = son
        im_projectile.draw(renderer,proj.at(i).getpos().getX(),proj.at(i).getpos().getY(),10,10);
	}
    
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////FONCTIONS MEMBRES MENU ////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void SDLSimple::menuAff () {

SDL_RenderClear(renderer);
SDL_SetRenderDrawColor(renderer, 255, 255,255, 255); // Couleur noire
im_menu.draw(renderer, 0,0,1800 ,900);                  //Image menu
font_color.r = 255; font_color.g = 255; font_color.b = 255;

// Afficher le 1er choix : JEU SURVIVOR
font_im.setSurface(TTF_RenderText_Solid(font, "JEU SURVIVOR :", font_color));
font_im.loadFromCurrentSurface(renderer);
SDL_Rect positionTitre;
positionTitre.x = 775; positionTitre.y = 100; positionTitre.w = 400; positionTitre.h = 100;
SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTitre);

// Afficher le 2eme choix : APPUYEZ SUR ENTREZ POUR JOUER !
font_im.setSurface(TTF_RenderText_Solid(font, " JOUER (1)", font_color));
font_im.loadFromCurrentSurface(renderer);
SDL_Rect positionbouton;
positionbouton.x = 850; positionbouton.y = 300; positionbouton.w = 200; positionbouton.h = 50;
SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionbouton);

// Afficher le 3ème choix : A PROPOS DU JEU
font_im.setSurface(TTF_RenderText_Solid(font, "A PROPOS DU JEU (2)", font_color));
font_im.loadFromCurrentSurface(renderer);
SDL_Rect positionA;
positionA.x = 800; positionA.y = 450; positionA.w = 300; positionA.h = 50;
SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionA);

// Afficher le 4ème choix : INFO DEVELOPPEURS
font_im.setSurface(TTF_RenderText_Solid(font, "INFO DEVELOPPEURS (3)", font_color));
font_im.loadFromCurrentSurface(renderer);
SDL_Rect positionInfo;
positionInfo.x = 800; positionInfo.y = 600; positionInfo.w = 300; positionInfo.h = 50;
SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionInfo);

// Afficher le 5ème choix : QUITER
font_im.setSurface(TTF_RenderText_Solid(font, "QUITTER (Esc)", font_color));
font_im.loadFromCurrentSurface(renderer);
SDL_Rect positionQuitter;
positionQuitter.x = 850; positionQuitter.y = 750; positionQuitter.w = 200; positionQuitter.h = 50;
SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionQuitter);


SDL_Rect recta;
recta.x = 725; // Coordonnées x du coin supérieur gauche
recta.y = 200; // Coordonnées y du coin supérieur gauche
recta.w = 450; // Largeur du rectangle
recta.h = 650; // Hauteur du rectangle
SDL_RenderDrawRect(renderer, &recta); // Dessiner le rectangle

SDL_RenderPresent(renderer);// Mettre à jour l'affichage
}

void SDLSimple::menuAfficheInfoDev() {
    SDL_RenderClear(renderer);
    im_menu.draw(renderer, 0,0,1800 ,900);                  //Image menu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;

    //Afficher le titre
    font_im.setSurface(TTF_RenderText_Solid(font, "INFO DEVELOPPEURS :", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTitre;
    positionTitre.x = 400;
    positionTitre.y = 100;
    positionTitre.w = 900;
    positionTitre.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTitre);

    //Afficher le texte d'information
    font_im.setSurface(TTF_RenderText_Solid(font, "Ce jeu a ete developpe par : ", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexte1;
    positionTexte1.x = 450;
    positionTexte1.y = 300;
    positionTexte1.w = 850;
    positionTexte1.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTexte1);

     font_im.setSurface(TTF_RenderText_Solid(font, " NEDJAR Amine ", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexte2;
    positionTexte2.x = 450;
    positionTexte2.y = 450;
    positionTexte2.w = 800;
    positionTexte2.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTexte2);

     font_im.setSurface(TTF_RenderText_Solid(font, " KANE Ousmane ", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexte3;
    positionTexte3.x = 450;
    positionTexte3.y = 600;
    positionTexte3.w = 800;
    positionTexte3.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTexte3);

     font_im.setSurface(TTF_RenderText_Solid(font, " DIA Abdou-Karim ", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexte4;
    positionTexte4.x = 450;
    positionTexte4.y = 750;
    positionTexte4.w = 800;
    positionTexte4.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTexte4);

    SDL_RenderPresent(renderer);

    bool quitter = false;
    while (!quitter) {
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement)) {
            switch (evenement.type) {
                case SDL_KEYDOWN:
                    if (evenement.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        quitter = true;
                    }
                    break;
                case SDL_QUIT:
                    Mix_PlayChannel(-1,s_choix_menu,0);
                    quitter = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void SDLSimple::menuAfficheDescription() {
    SDL_RenderClear(renderer);
    im_menu.draw(renderer, 0,0,1800 ,900);                  //Image menu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;

    //Afficher le titre
    font_im.setSurface(TTF_RenderText_Solid(font, "DESCRIPTION DU JEU : ", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTitre;
    positionTitre.x = 700;
    positionTitre.y = 100;
    positionTitre.w = 500;
    positionTitre.h = 100;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTitre);

    //Afficher le texte d'information
    font_im.setSurface(TTF_RenderText_Solid(font, " Le but de jeu est de survivre dans le monde la duree la plus longue possible,", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexte;
    positionTexte.x = 100;
    positionTexte.y = 350;
    positionTexte.w = 1600;
    positionTexte.h = 80;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTexte);

   //Afficher le texte d'information supplémentaire
    font_im.setSurface(TTF_RenderText_Solid(font, "en evitant les monstres, et en utilisant des techniques et des strategies appropriees !", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTexteSupp;
    positionTexteSupp.x = 100;
    positionTexteSupp.y = 550;
    positionTexteSupp.w = 1600;
    positionTexteSupp.h = 80;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTexteSupp);

    SDL_RenderPresent(renderer);

    bool quitter = false;
    while (!quitter) {
        SDL_Event evenement;
        while (SDL_PollEvent(&evenement)) {
            switch (evenement.type) {
                case SDL_KEYDOWN:
                    if (evenement.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                        quitter = true;
                    }
                    break;
                case SDL_QUIT:
                    Mix_PlayChannel(-1,s_choix_menu,0);
                    quitter = true;
                    break;
                default:
                    break;
            }
        }
    }
}

void SDLSimple::menuAfficheGameOver() {
    SDL_Event event;
    bool quit_gameover = false;
    SDL_RenderClear(renderer);
    im_menu.draw(renderer, 0,0,1800 ,900);                  //Image menu
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    font_color.r = 255;
    font_color.g = 255;
    font_color.b = 255;

    //Afficher GAME OVER
    font_im.setSurface(TTF_RenderText_Solid(font, "GAME OVER", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionGameOver;
    positionGameOver.x = 600;
    positionGameOver.y = 200;
    positionGameOver.w = 600;
    positionGameOver.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionGameOver);

    //Afficher le message
    font_im.setSurface(TTF_RenderText_Solid(font, "Vous avez perdu . . .", font_color));
    font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionMessage;
    positionMessage.x = 600;
    positionMessage.y = 400;
    positionMessage.w = 600;
    positionMessage.h = 50;
    SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionMessage);

    SDL_RenderPresent(renderer);

    while (!quit_gameover) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit_gameover = true;
            }
            else if (event.type == SDL_KEYDOWN) {
               if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    //Mix_PlayChannel(-1,s_choix_menu,0);
                    //resetJeu();
                    quit_gameover = true;
                    //menuBoucle(); // Revenir au menu
                   // menuAff();
                }
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// BOUCLE MENU ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void SDLSimple::menuBoucle ()  {
    SDL_Event events;
	bool quit_menu = false;
    
    while (!quit_menu) { 
        
        if (withSound && !Mix_Playing(menu_active_channel)) { //Pour résoudre le problème du son, on vérifier si le son n'est pas déja actif
        menu_active_channel= Mix_PlayChannel(-1,s_menu_musique,0); //Musique menu
        }

        while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit_menu = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {                   // Si une touche est enfoncee
				    switch (events.key.keysym.scancode) {
				        case SDL_SCANCODE_1: 
                            Mix_HaltChannel(menu_active_channel);   //Arreter la musique du menu
                            Mix_PlayChannel(-1,s_choix_menu,0);     // son des touches
                            //sleep(1);
                            if (withSound) Mix_PlayChannel(-1,s_start_effect,0);
                            if (withSound) jeu_active_channel= Mix_PlayChannel(-1,s_jeu_musique,0); // On joue la musique du jeu
                            sdlBoucle();  
                            //sleep(1);
                            break;
                        case SDL_SCANCODE_2: Mix_PlayChannel(-1,s_choix_menu,0);
                              menuAfficheDescription();
                            break;
                        case SDL_SCANCODE_3: Mix_PlayChannel(-1,s_choix_menu,0);
                            menuAfficheInfoDev();  
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            quit_menu = true;
                            break;
				            default: break;
                    }
                }
            }
	    menuAff();
    }		
    SDL_RenderPresent(renderer);	
}
    
                  
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// BOUCLE SDL ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////   

void SDLSimple::sdlBoucle () {
    SDL_Event events;
	bool quit_jeu = false;

    Uint32 t = SDL_GetTicks(), nt;
    Uint32 t_auto, t_monstre, t_projectile;
    t_auto = t_monstre = t_projectile = t;

    srand(time(NULL));
    int start_time = SDL_GetTicks(); // temps en millisecondes depuis le lancement du programme
    char timer_string[50]; // chaîne de caractères pour stocker le temps
    char number_string[50];
    int minutes = 0;
    int seconds = 0;


	// tant que ce n'est pas la fin ...
	while (!quit_jeu) {
/*
        for(unsigned int i=0;i<proj.size();i++)
            {
                if (proj.at(i).col_proj_mob) Mix_PlayChannel(-1,s_degat_projectile,0); //colision = son
            }
*/
        nt = SDL_GetTicks();
        if (nt-t_auto>40) {
            jeu.actionAutomatiques();
            t_auto = nt;
        }

        jeu.verifierLimitesJoueur(jeu.getTerrain()); // Verifier la position du personnage pour le placer dans l'écran
        
		if (nt-t_monstre>=500){ // On ajout un monstre chaque seconde
			t_monstre=nt;
			jeu.genereMonstre(jeu.getTerrain());
		}	
        if (nt-t_projectile>=1500){ // On ajoute un projectile chaque 3 secondes
			t_projectile=nt;
           jeu.genereProjectile(jeu.getPersonnage());
            Mix_PlayChannel(-1,s_tire_projectile,0);
		}

		// tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit_jeu= true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
				switch (events.key.keysym.scancode) {
				case SDL_SCANCODE_UP:
					jeu.actionClavier('z');    
					break;
				case SDL_SCANCODE_DOWN:
					jeu.actionClavier('s');   
					break;
				case SDL_SCANCODE_LEFT:
					jeu.actionClavier('q');
					break;
				case SDL_SCANCODE_RIGHT:
					jeu.actionClavier('d');
					break;
                case SDL_SCANCODE_SPACE:
                    jeu.actionClavier('o');
                    break;
                
                case SDL_SCANCODE_ESCAPE:
                    Mix_HaltChannel(jeu_active_channel);   //Arreter la musique du jeu
                    quit_jeu = true;
                    break;
				default: break;
				}
			}
		}

        if(!jeu.FinJeu(jeu.getPersonnage())) {
            Mix_PlayChannel(-1,s_fin_jeu,0);
			quit_jeu = true;
            //sleep(1);
            menuAfficheGameOver();
		}
		// on affiche le jeu sur le buffer cach�
		sdlAff();

    // Afficher le timer :
            // Calculer le temps écoulé en minutes et secondes
            int elapsed_time = (SDL_GetTicks() - start_time) / 1000; // temps écoulé en secondes
            minutes = elapsed_time / 60;
            seconds = elapsed_time % 60;
            // Mettre à jour la chaîne de caractères pour afficher le temps
            sprintf(timer_string, " T I M E : %02d : %02d", minutes, seconds);
            // Créer la surface de texte et la charger dans la texture
            font_im.setSurface(TTF_RenderText_Solid(font, timer_string, font_color));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionTimer; // position du texte sur l'écran
            positionTimer.x = 20; positionTimer.y = 100; positionTimer.w =150;positionTimer.h = 30;
            SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionTimer);

            int nb_mob = jeu.getVectorMonstre().size();
            sprintf(number_string, " M O N S T E R S  A L I V E : %d  " ,nb_mob);
            font_im.setSurface(TTF_RenderText_Solid(font, number_string, font_color));
            font_im.loadFromCurrentSurface(renderer);
            SDL_Rect positionNumber; // position du texte sur l'écran
            positionNumber.x = 20; positionNumber.y = 60; positionNumber.w =300;positionNumber.h = 30;
            SDL_RenderCopy(renderer, font_im.getTexture(), nullptr, &positionNumber);

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
    }
	
}

