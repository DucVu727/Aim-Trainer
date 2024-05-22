#include <iostream>
#include <ctime>
#include <SDL.h>

using namespace std;

const int screenWidth = 1366;
const int screenHeight = 768;
const int noteSize = 100;
const int noteSizeHard = 50;
const int timeLimit = 727;

Uint32 startTime;
Uint32 endTime;

SDL_Rect getRandomPosition(){
    SDL_Rect normalRect;
    normalRect.x = rand() % (screenWidth - noteSize);
    normalRect.y = rand() % (screenHeight - noteSize);
    normalRect.w = normalRect.h = noteSize;
    return normalRect;
}

SDL_Rect getRandomPositionHard(){
    SDL_Rect hardRect;
    hardRect.x = rand() % (screenWidth - noteSizeHard);
    hardRect.y = rand() % (screenHeight - noteSizeHard);
    hardRect.w = hardRect.h = noteSizeHard;
    return hardRect;
}

int main(int argc, char* argv[]){
    SDL_Window *window = SDL_CreateWindow("Aim Trainer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Surface *background = SDL_LoadBMP("resources//background.bmp");
    SDL_Surface *gameTitle = SDL_LoadBMP("resources//title.bmp");
    SDL_Surface *gameNormal = SDL_LoadBMP("resources//normal.bmp");
    SDL_Surface *gameHard = SDL_LoadBMP("resources//hard.bmp");
    SDL_Surface *gameQuit = SDL_LoadBMP("resources//quit.bmp");
    SDL_Surface *note = SDL_LoadBMP("resources//note.bmp");

    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, background);
    SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, gameTitle);
    SDL_Texture *normalTexture = SDL_CreateTextureFromSurface(renderer, gameNormal);
    SDL_Texture *hardTexture = SDL_CreateTextureFromSurface(renderer, gameHard);
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, gameQuit);
    SDL_Texture *noteTexture = SDL_CreateTextureFromSurface(renderer, note);

    SDL_Rect title;
    title.x = 483;
    title.y = 100;
    title.w = 400;
    title.h = 100;


    SDL_Rect normal;
    normal.x = 583;
    normal.y = 300;
    normal.w = 200;
    normal.h = 50;


    SDL_Rect hardRock;
    hardRock.x = 583;
    hardRock.y = 400;
    hardRock.w = 200;
    hardRock.h = 50;


    SDL_Rect quit;
    quit.x = 583;
    quit.y = 500;
    quit.w = 200;
    quit.h = 50;

    SDL_Rect pos = getRandomPosition();

    bool inGame = false;
    bool quitGame = false;

    while(!quitGame){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitGame = true;
            }

            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE){
                if (inGame == true){
                    inGame = false;
                }else{
                    quitGame = true;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_KEYDOWN){
                int mousePosX, mousePosY;
                SDL_GetMouseState(&mousePosX, &mousePosY);

                if (!inGame){
                    if (mousePosX >= 583 && mousePosX <= 783 && mousePosY >= 300 && mousePosY <= 350){
                        inGame = true;
                        pos = getRandomPosition();
                        startTime = SDL_GetTicks();
                    }

                    if (mousePosX >= 583 && mousePosX <= 783 && mousePosY >= 400 && mousePosY <= 450){
                        inGame = true;
                        pos = getRandomPositionHard();
                        startTime = SDL_GetTicks();
                    }

                    if (mousePosX >= 583 && mousePosX <= 783 && mousePosY >= 500 && mousePosY <= 550){
                        quitGame = true;
                    }

                }else{
                    if (mousePosX >= pos.x && mousePosX <= pos.x + pos.w && mousePosY >= pos.y && mousePosY <= pos.y + pos.h){
                        if (inGame == true){
                            if (pos.w == noteSize){
                                pos = getRandomPosition();
                                endTime = SDL_GetTicks();

                                if (endTime - startTime >= timeLimit){
                                    inGame = false;
                                }

                                startTime = endTime;

                            }else{
                                pos = getRandomPositionHard();
                                endTime = SDL_GetTicks();

                                if (endTime - startTime >= timeLimit){
                                    inGame = false;
                                }

                                startTime = endTime;
                            }
                        }
                    }else{
                        inGame = false;
                    }
                }
            }

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if (inGame == true && pos.w == noteSize){
            SDL_RenderCopy(renderer, noteTexture, NULL, &pos);
            SDL_RenderPresent(renderer);
        }else if(inGame == true && pos.w == noteSizeHard){
            SDL_RenderCopy(renderer, noteTexture, NULL, &pos);
            SDL_RenderPresent(renderer);
        }else{
            SDL_RenderCopy(renderer, titleTexture, NULL, &title);

            SDL_RenderCopy(renderer, normalTexture, NULL, &normal);

            SDL_RenderCopy(renderer, hardTexture, NULL, &hardRock);

            SDL_RenderCopy(renderer, quitTexture, NULL, &quit);

            SDL_RenderPresent(renderer);
        }
    }
}
    return 0;
}
