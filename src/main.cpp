#include <iostream>
#include <time.h>
#include <glm/common.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

// Loads individual image
SDL_Surface *loadSurface(std::string path);

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window
SDL_Surface *gScreenSurface = NULL;

// The images that correspond to a keypress
SDL_Surface *gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

// Current displayed image
SDL_Surface *gCurrentSurface = NULL;

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }

    return success;
}

int main(int argc, char *argv[])
{
    std::cout << "test";
    std::cout << "argc == " << argc << '\n';

    for (int ndx{}; ndx != argc; ++ndx)
        std::cout << "argv[" << ndx << "] == " << argv[ndx] << '\n';
    std::cout << "argv[" << argc << "] == "
              << static_cast<void *>(argv[argc]) << '\n';

    std::cout << "Hello World!\n";
    std::cout << "We're about to start the procedural generation project!!!\n";

    /*...*/

    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }

    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    // Set default current surface
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    // While application is running
    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            // User presses a key
            else if (e.type == SDL_KEYDOWN)
            {
                // Select surfaces based on key press
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                    printf("UP\n");
                    break;

                case SDLK_DOWN:
                    printf("DOWN\n");
                    break;

                case SDLK_LEFT:
                    printf("LEFT\n");
                    break;

                case SDLK_RIGHT:
                    printf("RIGHT\n");
                    break;

                default:
                    printf("default\n");
                    break;
                }
            }
        }

        // //Apply the current image
        // SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

        // Update the surface
        SDL_UpdateWindowSurface(gWindow);
    }

    return argc == 3 ? EXIT_SUCCESS : EXIT_FAILURE; // optional return value
}