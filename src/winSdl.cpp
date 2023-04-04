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
        SDL_Quit();exit(1);
        withSound = false;
    }
    else withSound = true;

	int dimx = jeu.getTerrain().getDimx();
	int dimy = jeu.getTerrain().getDimy();
    cout<<" Taille fenetre en x --> "<<jeu.getTerrain().getDimx()<<endl;
    cout<<" Taille fenetre en y --> "<<jeu.getTerrain().getDimy()<<endl;

    // Creation de la fenetre
    window = SDL_CreateWindow("Survivor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl; 
        SDL_Quit(); 
        exit(1);
    }
    
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

     // IMAGES
    im_personnage.loadFromFile("data/wizard_.png",renderer);
    im_monstre.loadFromFile("data/monstre.png", renderer);
    im_terrain.loadFromFile("data/Black_blocs.jpg", renderer);
    im_projectile.loadFromFile("data/projectile.png", renderer);
   

  // FONTS
     font = TTF_OpenFont("data/leadcoat.ttf", 72);
    if (font == nullptr)
        font = TTF_OpenFont("../data/contrast.ttf",72);
    if (font == nullptr) {
            cout << "Failed to load contrast.ttf! SDL_TTF Error: " << TTF_GetError() << endl; 
            SDL_Quit(); 
            exit(1);
	    }


   /*   // SONS
    if (withSound)
    {
       sound = Mix_LoadWAV("data/son.wav");
        if (sound == nullptr) 
            sound = Mix_LoadWAV("../data/son.wav");
        if (sound == nullptr) {
                cout << "Failed to load son.wav! SDL_mixer Error: " << Mix_GetError() << endl; 
                SDL_Quit();
                exit(1);
        }
    }*/
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
	//Remplir l'écran de blanc
    const Terrain& ter = jeu.getTerrain();
    const Personnage& per = jeu.getPersonnage();
    const vector<Monstre> &mon = jeu.getVectorMonstre();
	const vector<Projectile> &proj= jeu.getVectorProjectile();
    


    SDL_SetRenderDrawColor(renderer, 255,255, 255, 255);
     SDL_RenderClear(renderer);
    font_color.r = 0;font_color.g = 0;font_color.b = 0;
    int pv=per.getPV();
    char pv_string[50];
    sprintf(pv_string, " pv : %d",pv);
	font_im.setSurface(TTF_RenderText_Solid(font,pv_string,font_color));
	font_im.loadFromCurrentSurface(renderer);
    SDL_Rect positionTitre;
    positionTitre.x = 50;positionTitre.y = 50;positionTitre.w =200;positionTitre.h = 72;
    SDL_RenderCopy(renderer,font_im.getTexture(),nullptr,&positionTitre);
    //Dessin Personnage
    im_personnage.draw(renderer, per.getPos().getX(), per.getPos().getY(), 100 ,100);
    
    //Dessin des Monstres
    for(unsigned int i=0;i<mon.size();i++)
    {
        im_monstre.draw(renderer, mon.at(i).getPos().getX(),mon.at(i).getPos().getY(),100,100);
    }

    //Dessin du terrain
    for(unsigned int i=0;i<ter.getDimx();i++) // 1ere ligne horizontale
	{
		im_terrain.draw(renderer,i,0,40,40);
	}

	for(unsigned int j=0;j<ter.getDimy();j++) //Les 2 lignes verticales
	{
		//win.print(0,j,'*');
        im_terrain.draw(renderer,0,j,40,40);

		//win.print(ter.getDimx()-1,j,'*');
        im_terrain.draw(renderer,ter.getDimx()-1,j,40,40);
	}

	for(unsigned int i=0;i<ter.getDimx();i++) // 2e ligne horizontale
	{
        im_terrain.draw(renderer,i,ter.getDimy()-1,40,40);
	}

    //Dessin projectile

    for(unsigned int i=0;i<proj.size();i++)
	{
		//win.print(proj.at(i).getpos().getX(),proj.at(i).getpos().getY(),'.');
        im_projectile.draw(renderer,proj.at(i).getpos().getX(),proj.at(i).getpos().getY(),20,20);
	}

}

void SDLSimple::sdlBoucle () {
    SDL_Event events;
	bool quit = false;

    Uint32 t = SDL_GetTicks(), nt;

    srand(time(NULL));
    clock_t debut = clock();


	// tant que ce n'est pas la fin ...
	while (!quit) {

        nt = SDL_GetTicks();
        if (nt-t>1) {
            jeu.actionAutomatiques();
            t = nt;
        }
        
        clock_t fin = clock();
      	int duree = (int)(fin - debut) / CLOCKS_PER_SEC;
		if (duree>=1){
			debut=fin;
			jeu.genereMonstre(jeu.getTerrain());
		}	
        cout <<"debut= "<<debut<<endl;
        cout <<"fin= "<<fin<<endl;
		// tant qu'il y a des évenements à traiter (cette boucle n'est pas bloquante)
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) quit = true;           // Si l'utilisateur a clique sur la croix de fermeture
			else if (events.type == SDL_KEYDOWN) {              // Si une touche est enfoncee
                //bool mangePastille = false;
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
                case SDL_SCANCODE_O:
                    jeu.actionClavier('o');
                    break;
                
                case SDL_SCANCODE_ESCAPE:

                    quit = true;
                    break;
				default: break;
				}
				/*if ((withSound) && (mangePastille))
                    Mix_PlayChannel(-1,sound,0);*/
			}
		}

		// on affiche le jeu sur le buffer cach�
		sdlAff();

		// on permute les deux buffers (cette fonction ne doit se faire qu'une seule fois dans la boucle)
        SDL_RenderPresent(renderer);
	}
}

