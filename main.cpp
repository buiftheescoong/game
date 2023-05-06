#include <iostream>
#include <SDL.h>
#include "SDL_utlis.h"
#include "Game.h"
#include "TextObject.h"
#include "Score.h"

using namespace std;


int main(int argc, char *argv[]){
     srand(time(0));




     Game game;
     game.init();

     TextObject time_game;
     time_game.setColor(1);

     string highscore = GetHighScoreFromFile("high_score.txt");


   //  bool paused = false;
     do{
        game.Music();
        game.scrollBackground();
        game.random_obs();
        if(game.move()== QUIT){
            game.stopMusic();
            break;
        }
      //  if(game.move()== PAUSE){
        //    paused = !paused;
      //  }
        //if(paused) continue;

        game.render();


        string time = "Time : ";
        Uint32 time_value = SDL_GetTicks()/1000;
        string str_time_value = to_string(time_value);
        time += str_time_value;
        time_game.SetText(time);
        time_game.loadFromRenderedText(gFont, renderer);
        DrawPlayerScore(renderer, gFont, game.score);
        DrawPlayerHighScore(renderer, gFont, highscore);
        time_game.Render(renderer, 700,0);

        SDL_RenderPresent(renderer);

     }while(!game.Collision());
     game.rendergame_over();

     waitUntilKeyPressed();

     game.destroy();

     return 0;


}
