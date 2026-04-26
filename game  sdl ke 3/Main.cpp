#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Test",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1000, 600,
        SDL_WINDOW_RESIZABLE // Keep this ON so the Maximize button stays active
    );

    // FIX: Instead of disabling resize, we lock the minimum size.
    // This prevents the user from shrinking the window.
    SDL_SetWindowMinimumSize(window, 1000, 600);

    // ONLY CREATE THE RENDERER ONCE
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Set logical size so the drawing scales when maximized
    SDL_RenderSetLogicalSize(renderer, 1000, 600);

    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) running = false;
            
            // OPTIONAL: If you want to toggle Maximize with a key (like 'M')
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
                Uint32 flags = SDL_GetWindowFlags(window);
                if (flags & SDL_WINDOW_MAXIMIZED) SDL_RestoreWindow(window);
                else SDL_MaximizeWindow(window);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);
        SDL_RenderClear(renderer);

        SDL_Rect rect = { 300, 200, 200, 150 };
        SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
