#include "Game.h"
#include "TextObject.h"
#include "Score.h"
#include "Button.h"
#include "HandleButtons.h"
const int PLAY_BUTTON_POSX = 515;
const int PLAY_BUTTON_POSY= 400;
const int EXIT_BUTTON_POSX = 515;
const int EXIT_BUTTON_POSY = 600;
const int PAUSE_BUTTON_POSX = 30;
const int PAUSE_BUTTON_POSY = 30;
const int CONTINUE_BUTTON_POSX = 30;
const int CONTINUE_BUTTON_POSY = 30;
const int NEWGAME_BUTTON_POSX = 515;
const int NEWGAME_BUTTON_POSY = 400;
const int MENU_BUTTON_POSX = 515;
const int MENU_BUTTON_POSY = 500;
const int QUIT_BUTTON_POSX = 515;
const int QUIT_BUTTON_POSY = 600;

using namespace std;
void LoadMedia();
void DrawEndGameSelection(TextObject GameOverTex[2], Button& NewGameButton, TextObject NewGameButtonTex[BUTTON_STATES],
                         Button& QuitButton, TextObject QuitGameButtonTex[BUTTON_STATES], Button& MenuButton,
                        TextObject MenuButtonTex[BUTTON_STATES], SDL_Event* e, SDL_Renderer* Renderer, bool &Play, int score,
                          int highscore, bool& QuitMenu, bool& MenuAndGameLoop);
TextObject MenuTex;
TextObject PlayButtonTex[BUTTON_STATES];
TextObject ExitButtonTex[BUTTON_STATES];
TextObject PauseButtonTex[BUTTON_STATES];
TextObject ContinueButtonTex[BUTTON_STATES];
TextObject NewGameButtonTex[BUTTON_STATES];
TextObject MenuButtonTex[BUTTON_STATES];
TextObject QuitButtonTex[BUTTON_STATES];
TextObject GameOverTex[2];

Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button NewGameButton(NEWGAME_BUTTON_POSX, NEWGAME_BUTTON_POSY);
Button MenuButton(MENU_BUTTON_POSX, MENU_BUTTON_POSY);
Button QuitButton(QUIT_BUTTON_POSX, QUIT_BUTTON_POSY);
int main(int argc, char *argv[]){
     srand(time(0));
    LoadMedia();
    bool QuitMenu = false;
    bool Play = false;
    bool MenuAndGameLoop = true;
    Game game;
    while(MenuAndGameLoop){
        //Menu Loop
        while(!QuitMenu){
            SDL_Event e_mouse;
            while (SDL_PollEvent(&e_mouse) != 0){
                if (e_mouse.type == SDL_QUIT){
                    Play = false;
                    QuitMenu = true;
                    MenuAndGameLoop = false;
                }

                HandlePlayButton(&e_mouse, PlayButton, QuitMenu, Play);
                HandleExitButton(&e_mouse, ExitButton, QuitMenu);
            }
            MenuTex.Render(renderer,0,0);
            PlayButton.Render(NULL,renderer,PlayButtonTex[PlayButton.currentState]);
            ExitButton.Render(NULL,renderer,ExitButtonTex[ExitButton.currentState]);
            SDL_RenderPresent(renderer);
        }
    //Game loop
        while(Play){
            SDL_Event e;

            string highscore = GetHighScoreFromFile("high_score.txt");
            bool Quit = false;
            bool GameState = true;

            while(!Quit){
                //In game
                if(GameState){

                    game.init();
                    game.Music();
                    game.scrollBackground();
                    game.random_obs();
                    TextObject time_game;
                    time_game.setColor(1);
                    string time = "Time : ";
                    Uint32 time_value = SDL_GetTicks()/1000;
                    string str_time_value = to_string(time_value);
                    time += str_time_value;
                    time_game.SetText(time);
                    time_game.loadFromRenderedText(gFont, renderer);
                    while (SDL_PollEvent(&e) != 0){
                        if (e.type == SDL_QUIT){
                            MenuAndGameLoop = false;
                            Quit = true;
                            Play = false;
                        }
                        HandlePauseButton(&e, renderer, PauseButton, ContinueButton,   ContinueButtonTex,  GameState);
                    }
                    game.clearScreen();
                    game.render();
                    PauseButton.Render (NULL,renderer, PauseButtonTex[PauseButton.currentState]);
                    DrawPlayerScore(renderer, gFont, game.score);
                    DrawPlayerHighScore(renderer, gFont, highscore);
                    time_game.Render(renderer, 700,0);

                    if(!game.Collision()){
                        UpdateHighScore("high_score.txt", game.score, highscore);
                        Quit = true;
                    }
                    SDL_RenderPresent(renderer);
                }
            }
        //POST GAME
        DrawEndGameSelection(GameOverTex, NewGameButton, NewGameButtonTex, QuitButton, QuitButtonTex, MenuButton, MenuButtonTex,
                              &e, renderer, Play, game.score, stoi(highscore), QuitMenu, MenuAndGameLoop);
        }
    }

     waitUntilKeyPressed();

     game.destroy();
     return 0;
}
     void LoadMedia(){
        if (!MenuTex.LoadFromFile("imgs/menu.jpg", renderer)){
            cout << "Failed to load menu image!" << endl;
        }
        //Load Buttons
        if (!PlayButtonTex[0].LoadFromFile("imgs/button/big_button/PlayButtonOff.png", renderer)
            || !PlayButtonTex[1].LoadFromFile("imgs/button/big_button/PlayButtonOn.png", renderer)){
            cout << "Failed to load play_button image" << endl;
        }

        if(!ExitButtonTex[0].LoadFromFile("imgs/button/big_button/ExitButtonOff.png", renderer)
            || !ExitButtonTex[1].LoadFromFile("imgs/button/big_button/ExitButtonOn.png", renderer)){
            cout << "Failed to load exit_button image" << endl;
        }

        if (!PauseButtonTex[0].LoadFromFile("imgs/button/small_button/PauseButtonOff.png", renderer)
            || !PauseButtonTex[1].LoadFromFile("imgs/button/small_button/PauseButtonOn.png", renderer)){
            cout << "Failed to load pause_button image " << endl;
        }

        if (!ContinueButtonTex[0].LoadFromFile("imgs/button/small_button/ResumeButtonOff.png", renderer)
            || !ContinueButtonTex[1].LoadFromFile("imgs/button/small_button/ResumeButtonOn.png", renderer)){
            cout << "Failed to load continue_button image " << endl;
        }

        if(!NewGameButtonTex[0].LoadFromFile("imgs/button/big_button/NewGameButtonOff.png", renderer)
           || !NewGameButtonTex[1].LoadFromFile("imgs/button/big_button/NewGameButtonOn.png", renderer)){
            cout << "Failed to load new game button image!" << endl;
        }

        if(!MenuButtonTex[0].LoadFromFile("imgs/button/big_button/MenuButtonOff.png", renderer)
           || !MenuButtonTex[1].LoadFromFile("imgs/button/big_button/MenuButtonOn.png", renderer)){
            cout << "Failed to load menu button image!" << endl;
        }

        if(!QuitButtonTex[0].LoadFromFile("imgs/button/big_button/QuitButtonOff.png", renderer)
           || !QuitButtonTex[1].LoadFromFile("imgs/button/big_button/QuitButtonOn.png", renderer)){
            cout << "Failed to load new game button image!" << endl;
        }

         //Load Game Over Screen
        GameOverTex[0].setColor(1);
        GameOverTex[0].SetText("GAME OVER!");

        GameOverTex[1].setColor(1);
        GameOverTex[1].SetText("GAME OVER!");

        if (! GameOverTex[0].loadFromRenderedText(GameOverFont, renderer)
            || ! GameOverTex[1].loadFromRenderedText(GameOverFont, renderer)){
            cout << "Failed to load game over text!" << endl;
            }
     }
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
                    GameOverTex[1].Render(Renderer,270, 150);
                }
                else{
                    GameOverTex[0].Render(Renderer,390, 150);
                }

                NewGameButton.Render(NULL,Renderer, NewGameButtonTex[NewGameButton.currentState]);
                MenuButton.Render(NULL,Renderer, MenuButtonTex[MenuButton.currentState]);
                QuitButton.Render(NULL,Renderer,QuitGameButtonTex[QuitButton.currentState]);
                SDL_RenderPresent(Renderer);
            }
        }
    }

