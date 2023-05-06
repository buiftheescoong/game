#ifndef GAME__H_
#define GAME__H_
#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include<SDL_ttf.h>
#include<cstdlib>
#include<ctime>
#include "SDL_utlis.h"

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* gFont = NULL;
TTF_Font* Font_Menu = NULL;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
enum Action {LEFT, RIGHT, UP, DOWN, NONE, QUIT, PAUSE};
struct Game{

    const char * WINDOW_TITLE = "CAR GAME";
    const int borderLeft=140;
    const int borderRight=660;

    double gameSpeed=4;
    int score= 0;

    SDL_Texture* background;
    SDL_Texture* background1;
    SDL_Texture* obs1;
    SDL_Texture* obs2;
    SDL_Texture* obs3;
    SDL_Texture* obs4;
    SDL_Texture* racer;
    SDL_Texture* game_over;
    SDL_Rect racerRect, obs1Rect, obs2Rect, obs3Rect, obs4Rect, backgroundRect, background1Rect;

    Mix_Music *gMusic = NULL;
    Mix_Chunk *over_Music = NULL;


    void init(){

        initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);


        background = loadTexture( "cars/background.png", renderer);
        background1 = loadTexture( "cars/background.png", renderer);
        obs1 = loadTexture( "cars/obs1.png", renderer);
        obs2 = loadTexture( "cars/obs2.png", renderer);
        obs3 = loadTexture( "cars/obs3.png", renderer);
        obs4 = loadTexture( "cars/obs4.png", renderer);
        racer = loadTexture( "cars/racer.png", renderer);
        game_over = loadTexture("cars/over.png", renderer);

        SDL_QueryTexture(racer, NULL, NULL, &racerRect.w, &racerRect.h);
        SDL_QueryTexture(obs1, NULL, NULL, &obs1Rect.w, &obs1Rect.h);
        SDL_QueryTexture(obs2, NULL, NULL, &obs2Rect.w, &obs2Rect.h);
        SDL_QueryTexture(obs3, NULL, NULL, &obs3Rect.w, &obs3Rect.h);
        SDL_QueryTexture(obs4, NULL, NULL, &obs4Rect.w, &obs4Rect.h);
        SDL_QueryTexture(background, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
        SDL_QueryTexture(background1, NULL, NULL, &background1Rect.w, &background1Rect.h);
        racerRect.x = SCREEN_WIDTH/2;
        racerRect.y = SCREEN_HEIGHT - racerRect.h;
        obs1Rect.y=0;obs2Rect.y=-100; obs3Rect.y=-200;obs4Rect.y=-300; backgroundRect.x = 0; background1Rect.x = 0;
        backgroundRect.y=0;
        background1Rect.y=-600;
        obs1Rect.x=getRandomNumber(borderLeft,borderRight);
        obs2Rect.x=getRandomNumber(borderLeft,borderRight);
        obs3Rect.x=getRandomNumber(borderLeft,borderRight);
        obs4Rect.x=getRandomNumber(borderLeft,borderRight);
        gFont = TTF_OpenFont("font/xirod.ttf",15);
        if( gFont == NULL )
        {
            printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        }

         Font_Menu = TTF_OpenFont("font/xirod.ttf",35);
         if( gFont == NULL )
         {
            printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
         }


        gMusic = Mix_LoadMUS( "sound/game.wav");
        if( gMusic == NULL )
        {
            printf( "Failed to load gMusic! SDL_mixer Error: %s\n", Mix_GetError() );

        }
        over_Music = Mix_LoadWAV("sound/crash.wav");
         if( over_Music == NULL )
        {
            printf( "Failed to load over_music sound! SDL_mixer Error: %s\n", Mix_GetError() );
        }

    }
    void clearScreen() {
        SDL_RenderClear(renderer);
    }

    void Music(){
        if( Mix_PlayingMusic() == 0 ){
            //Play the music
            Mix_PlayMusic( gMusic, -1 );
        }
    }
    void stopMusic(){
        Mix_HaltMusic();
    }

    void scrollBackground(){
        if (background1Rect.y>0)
        {
           backgroundRect.y=0;
           background1Rect.y=backgroundRect.y-500;
        }
        backgroundRect.y+=1;
        background1Rect.y+=1;
    }


    void random_obs(){
        if(obs1Rect.y>SCREEN_HEIGHT)
            {obs1Rect.y=0;obs1Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs1Rect.y=obs1Rect.y+gameSpeed;}
        if (obs2Rect.y>SCREEN_HEIGHT)
            {obs2Rect.y=0;obs2Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs2Rect.y=obs2Rect.y+gameSpeed;}
        if (obs3Rect.y > SCREEN_HEIGHT)
            {obs3Rect.y=0;obs3Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs3Rect.y=obs3Rect.y+gameSpeed;}
        if (obs4Rect.y>SCREEN_HEIGHT)
            {obs4Rect.y=0;obs4Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs4Rect.y=obs4Rect.y+gameSpeed;}
    }

    void render(){
        clearScreen();
        SDL_RenderClear(renderer);


        SDL_RenderCopy(renderer, background, NULL, &backgroundRect);
        SDL_RenderCopy(renderer, background1, NULL, &background1Rect);
        SDL_RenderCopy(renderer, racer, NULL, &racerRect);
        SDL_RenderCopy(renderer, obs1, NULL, &obs1Rect);
        SDL_RenderCopy(renderer, obs2, NULL, &obs2Rect);
        SDL_RenderCopy(renderer, obs3, NULL, &obs3Rect);
        SDL_RenderCopy(renderer, obs4, NULL, &obs4Rect);


    }
    void rendergame_over(){
        clearScreen();
        SDL_RenderCopy(renderer, game_over, NULL, NULL);
        SDL_RenderPresent( renderer );
    }
    void destroy(){
        Mix_FreeChunk( over_Music );
        over_Music = NULL;
        Mix_FreeMusic( gMusic );
        gMusic = NULL;


        SDL_DestroyTexture(background);
        background = NULL;
        SDL_DestroyTexture(background1);
        background1 = NULL;
        SDL_DestroyTexture(racer);
        racer = NULL;
        SDL_DestroyTexture(obs1);
        obs1 = NULL;
        SDL_DestroyTexture(obs2);
        obs2 = NULL;
        SDL_DestroyTexture(obs3);
        obs3 = NULL;
        SDL_DestroyTexture(obs4);
        obs4 = NULL;
        quitSDL(window, renderer);
    }
    int getRandomNumber(int a, int b)
    {
        static bool first = true; if (first){srand( time(NULL) );first = false;}
        return a + rand() % ( b + 1 - a);

    }
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
    {
      int left_a = object1.x;
      int right_a = object1.x + object1.w;
      int top_a = object1.y;
      int bottom_a = object1.y + object1.h;

      int left_b = object2.x;
      int right_b = object2.x + object2.w;
      int top_b = object2.y;
      int bottom_b = object2.y + object2.h;

      // Case 1: size object 1 < size object 2
      if (left_a > left_b && left_a < right_b)
      {
        if (top_a > top_b && top_a < bottom_b)
        {
          return true;
        }
      }

      if (left_a > left_b && left_a < right_b)
      {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
          return true;
        }
      }

      if (right_a > left_b && right_a < right_b)
      {
        if (top_a > top_b && top_a < bottom_b)
        {
          return true;
        }
      }

      if (right_a > left_b && right_a < right_b)
      {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
          return true;
        }
      }

      // Case 2: size object 1 > size object 2
      if (left_b > left_a && left_b < right_a)
      {
        if (top_b > top_a && top_b < bottom_a)
        {
          return true;
        }
      }

      if (left_b > left_a && left_b < right_a)
      {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
          return true;
        }
      }

      if (right_b > left_a && right_b < right_a)
      {
        if (top_b > top_a && top_b < bottom_a)
        {
          return true;
        }
      }

      if (right_b > left_a && right_b < right_a)
      {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
          return true;
        }
      }

       // Case 3: size object 1 = size object 2
      if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
      {
        return true;
      }

      return false;
    }
    bool Collision(){
      if(CheckCollision(racerRect, obs1Rect)){
        stopMusic();
        Mix_PlayChannel( -1, over_Music, 0);
        return true;
      }
      if(CheckCollision(racerRect, obs2Rect)){
        stopMusic();
        Mix_PlayChannel( -1, over_Music, 0);
        return true;
      }
      if(CheckCollision(racerRect, obs3Rect)){
        stopMusic();
        Mix_PlayChannel( -1, over_Music, 0);
        return true;
      }
      if(CheckCollision(racerRect, obs4Rect)){
        stopMusic();
        Mix_PlayChannel( -1, over_Music, 0);
        return true;
      }
      return false;

    }
    Action move(){
        SDL_Event e;
        if (SDL_PollEvent(&e) == 0) return NONE;
        if (e.type == SDL_QUIT) return QUIT;
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE: return QUIT;
                case SDLK_LEFT:
                    if(racerRect.x > borderLeft){racerRect.x =racerRect.x - 20;};
                    return LEFT;
                case SDLK_RIGHT:
                    if(racerRect.x < borderRight){racerRect.x =racerRect.x + 20;};
                    return RIGHT;
                case SDLK_DOWN:
                    if(racerRect.y < SCREEN_HEIGHT - 70){racerRect.y = racerRect.y + 20;};
                    return DOWN;
                case SDLK_UP:
                    if(racerRect.y > 0){racerRect.y = racerRect.y - 20;};
                    return UP;
                case SDLK_p:
                   // SDL_Delay(5000);
                    //SDL_PumpEvents();
                    return PAUSE;
                default: return NONE;
            }
        }
        return NONE;
    }

    };

#endif
