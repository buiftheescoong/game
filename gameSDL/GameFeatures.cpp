#include "GameFeatures.h"
#include "HandleButtons.h"

    void DrawEndGameSelection(TextObject GameOverTex[2], Button& NewGameButton, TextObject NewGameButtonTex[BUTTON_STATES],
                         Button& QuitButton, TextObject QuitGameButtonTex[BUTTON_STATES], Button& MenuButton,
                        TextObject MenuButtonTex[BUTTON_STATES], SDL_Event* e, SDL_Renderer* Renderer, bool &Play, int score,
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

                if(score > highscore){
                    GameOverTex[1].Render(Renderer,350, 300);
                }
                else{
                    GameOverTex[0].Render(Renderer,350, 300);
                }

                NewGameButton.Render(NULL,Renderer, NewGameButtonTex[NewGameButton.currentState]);
                MenuButton.Render(NULL,Renderer, MenuButtonTex[MenuButton.currentState]);
                QuitButton.Render(NULL,Renderer,QuitGameButtonTex[QuitButton.currentState]);
                SDL_RenderPresent(Renderer);
            }
        }
    }
