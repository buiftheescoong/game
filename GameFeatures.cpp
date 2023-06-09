#include "GameFeatures.h"
#include "HandleButtons.h"

    void DrawEndGameSelection(TextObject GameOverTex[2], Button& NewGameButton, TextObject NewGameButtonTex[BUTTON_STATES],
                         Button& QuitButton, TextObject QuitButtonTex[BUTTON_STATES], Button& MenuButton,
                        TextObject MenuButtonTex[BUTTON_STATES], SDL_Event* e, SDL_Renderer* renderer, bool &Play, int score,
                          int highscore, bool& QuitMenu, bool& MenuAndGameLoop)
    {


        if(Play){
            bool Quit = false;
            while (!Quit){
                while(SDL_PollEvent(e) != 0){
                    if (e->type == SDL_QUIT){
                        Quit = true;
                        Play = false;
                        MenuAndGameLoop = false;
                    }

                    HandleNewGameButton(e, NewGameButton, Quit, Play);
                    HandleMenuButton(e, MenuButton, Quit, Play, QuitMenu);
                    HandleQuitButton(e, QuitButton, Quit, Play, MenuAndGameLoop);
                }
                SDL_RenderClear(renderer);
                if(score > highscore){
                    GameOverTex[1].Render(renderer,180, 200);
                }
                else{
                    GameOverTex[0].Render(renderer,220, 200);
                }
                 SDL_Rect newgame;
                 newgame = {NewGameButton.position.x,NewGameButton.position.y,NewGameButtonTex[NewGameButton.currentState].width_,
                        NewGameButtonTex[NewGameButton.currentState].height_};
                 SDL_RenderCopy(renderer,NewGameButtonTex[NewGameButton.currentState].texture_,NULL,&newgame);
                 SDL_Rect menu;
                 menu = {MenuButton.position.x,MenuButton.position.y,MenuButtonTex[MenuButton.currentState].width_,
                        MenuButtonTex[MenuButton.currentState].height_};
                 SDL_RenderCopy(renderer,MenuButtonTex[MenuButton.currentState].texture_,NULL,&menu);
                 SDL_Rect quit;
                 quit = {QuitButton.position.x,QuitButton.position.y,QuitButtonTex[QuitButton.currentState].width_,
                             QuitButtonTex[QuitButton.currentState].height_};
                 SDL_RenderCopy(renderer,QuitButtonTex[QuitButton.currentState].texture_,NULL,&quit);


                SDL_RenderPresent(renderer);
            }
        }
    }
