#include <SDL/SDL.h>
#define SDL_main main

#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

enum ColorNumber
{
    Rich = 32,
    Medium = 16,
    Poor = 8
};

int main(int argc, char const *argv[])
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Error while initialising SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Load window
    SDL_Surface *icon = SDL_LoadBMP("pack_images_sdz/sdl_icone.bmp");
    // Set window title
    SDL_WM_SetCaption("Display BMP", NULL);
    // Set window icon + transparency
    SDL_WM_SetIcon(icon, NULL);

    SDL_Surface *screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, Rich, SDL_HWSURFACE | SDL_DOUBLEBUF); 
    
    if(screen == NULL) {
        fprintf(stderr, "Error while setting Video Mode: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);   
    }

/// Background
    // Position
    int backgroundX = 0;
    int backgroundY = 0;
    SDL_Rect backgroundPosition = {backgroundX, backgroundY};    
    SDL_Surface *backgroundImg = SDL_LoadBMP("pack_images_sdz/lac_en_montagne.bmp");

/// Zozor
    int zozorX = 100;
    int zozorY = 50;
    SDL_Rect zozorPosition = {zozorX, zozorY};
    SDL_Surface *zozor = SDL_LoadBMP("pack_images_sdz/zozor.bmp");
    Uint32 blue = SDL_MapRGB(zozor->format, 0, 0, 255);
    // Apply TOTAL transparency on blue
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, blue);
    // Apply opacity on zozor (value range: 0 - 255)
    SDL_SetAlpha(zozor, SDL_SRCALPHA, 255);

/// Update window
    SDL_BlitSurface(backgroundImg, NULL, screen, &backgroundPosition);
    SDL_BlitSurface(zozor, NULL, screen, &zozorPosition);
    SDL_Flip(screen);

    SDL_Event event;
    // Enable key repeat
    int delayBeforeEnablingKeyRepeat = 10;
    int intervalOfRepetition = 10;
    SDL_EnableKeyRepeat(delayBeforeEnablingKeyRepeat, intervalOfRepetition);
    // Hide mouse
    SDL_ShowCursor(SDL_DISABLE);
    int run = 1;

    while(run){
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                run = 0;
                break;
        
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        run = 0;
                        break;
                    case SDLK_UP:
                        zozorPosition.y--;
                        break;
                    case SDLK_DOWN:
                        zozorPosition.y++;
                        break;
                    case SDLK_RIGHT:
                        zozorPosition.x++;
                        break;
                    case SDLK_LEFT:
                        zozorPosition.x--;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                zozorPosition.x = event.button.x;
                zozorPosition.y = event.button.y;
                break;
            case SDL_MOUSEMOTION:
                zozorPosition.x = event.motion.x;
                zozorPosition.y = event.motion.y;
                break;
            default:
                break;
        }
        
        // Clear screen
        SDL_BlitSurface(backgroundImg, NULL, screen, &backgroundPosition);
        // Draw Zozor
        SDL_BlitSurface(zozor, NULL, screen, &zozorPosition);
        // Update screen
        SDL_Flip(screen);
    }
    
    
    SDL_FreeSurface(backgroundImg);
    SDL_Quit();

    return EXIT_SUCCESS;
}
