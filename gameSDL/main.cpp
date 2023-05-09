#include "Base.h"
#include "TextObject.h"
#include "Score.h"
#include "Button.h"
#include "HandleButtons.h"
#include "GameFeatures.h"


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* gFont = NULL;
TTF_Font* GameOverFont = NULL;
Mix_Music *gMusic = NULL;
Mix_Chunk *over_Music = NULL;

SDL_Texture* background;
SDL_Texture* background1;
SDL_Texture* obs1;
SDL_Texture* obs2;
SDL_Texture* obs3;
SDL_Texture* obs4;
SDL_Texture* racer;
SDL_Texture* MenuTex;

SDL_Rect racerRect, obs1Rect, obs2Rect, obs3Rect, obs4Rect, backgroundRect, background1Rect;

double gameSpeed=3;
const int borderLeft=140;
const int borderRight=660;


TextObject PlayButtonTex[BUTTON_STATES];
TextObject ExitButtonTex[BUTTON_STATES];
TextObject PauseButtonTex[BUTTON_STATES];
TextObject ContinueButtonTex[BUTTON_STATES];
TextObject NewGameButtonTex[BUTTON_STATES];
TextObject MenuButtonTex[BUTTON_STATES];
TextObject QuitButtonTex[BUTTON_STATES];
TextObject GameOverTex[2];

TextObject high_score_game;
TextObject score_game;
using namespace std;



Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);
Button ExitButton(EXIT_BUTTON_POSX, EXIT_BUTTON_POSY);
Button PauseButton(PAUSE_BUTTON_POSX, PAUSE_BUTTON_POSY);
Button ContinueButton(CONTINUE_BUTTON_POSX, CONTINUE_BUTTON_POSY);
Button NewGameButton(NEWGAME_BUTTON_POSX, NEWGAME_BUTTON_POSY);
Button MenuButton(MENU_BUTTON_POSX, MENU_BUTTON_POSY);
Button QuitButton(QUIT_BUTTON_POSX, QUIT_BUTTON_POSY);


int getRandomNumber(int a, int b)
{
    static bool first = true; if (first){srand( time(NULL) );first = false;}
    return a + rand() % ( b + 1 - a);

}
SDL_Texture* loadTexture( string path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}
void Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
		cout << "Cannot initialise SDL!" << endl;
	}

	else{
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
								   SCREEN_WIDTH, SCREEN_HEIGHT,
								   SDL_WINDOW_SHOWN);
		if (window == NULL){
			cout << "Cannot create game window!" << endl;
		}

		else{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL){
				cout << "Cannot create game renderer!" << endl;
			}

			else{
				//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
					cout << "Cannot initialise SDL mixer!" << endl;
				}

				if (TTF_Init() == -1){
					cout << "Cannot initialise SDL ttf!" << endl;
				}
			}
		}
	}
}
void LoadMedia(){
        background = loadTexture( "cars/background.png", renderer);
        background1 = loadTexture( "cars/background.png", renderer);
        obs1 = loadTexture( "cars/obs1.png", renderer);
        obs2 = loadTexture( "cars/obs2.png", renderer);
        obs3 = loadTexture( "cars/obs3.png", renderer);
        obs4 = loadTexture( "cars/obs4.png", renderer);
        racer = loadTexture( "cars/racer.png", renderer);
        MenuTex =loadTexture("imgs/menu.jpg", renderer);
        //game_over = loadTexture("cars/over.png", renderer);

        SDL_QueryTexture(racer, NULL, NULL, &racerRect.w, &racerRect.h);
        SDL_QueryTexture(obs1, NULL, NULL, &obs1Rect.w, &obs1Rect.h);
        SDL_QueryTexture(obs2, NULL, NULL, &obs2Rect.w, &obs2Rect.h);
        SDL_QueryTexture(obs3, NULL, NULL, &obs3Rect.w, &obs3Rect.h);
        SDL_QueryTexture(obs4, NULL, NULL, &obs4Rect.w, &obs4Rect.h);
        SDL_QueryTexture(background, NULL, NULL, &backgroundRect.w, &backgroundRect.h);
        SDL_QueryTexture(background1, NULL, NULL, &background1Rect.w, &background1Rect.h);

        gFont = TTF_OpenFont("font/xirod.ttf",15);
        if( gFont == NULL )
        {
            printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        }

        GameOverFont = TTF_OpenFont("font/xirod.ttf",40);
        if( GameOverFont == NULL )
        {
            printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        }

       /* if (!MenuTex.LoadFromFile("imgs/menu.jpg", renderer)){
            cout << "Failed to load menu image!" << endl;
        }*/

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
        string s1 = "GAME OVER!";
        string s2 = "NEW HIGH SCORE!";
        GameOverTex[0].setColor(1);
        GameOverTex[0].SetText(s1);

        GameOverTex[1].setColor(1);
        GameOverTex[1].SetText(s2);

        if (! GameOverTex[0].loadFromRenderedText(GameOverFont, renderer)
            || ! GameOverTex[1].loadFromRenderedText(GameOverFont, renderer)){
            cout << "Failed to load game over text!" << endl;
            }
}
void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
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
void Close(){
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
    SDL_DestroyTexture(MenuTex);
    MenuTex = NULL;

    for(int i = 0; i < BUTTON_STATES; i++){
        PlayButtonTex[i].Free();
        ExitButtonTex[i].Free();
        PauseButtonTex[i].Free();
        ContinueButtonTex[i].Free();
        GameOverTex[i].Free();
	}

    high_score_game.Free();
    score_game.Free();


    Mix_FreeMusic( gMusic );
    gMusic = NULL;
    Mix_FreeChunk(over_Music);
    over_Music = NULL;
    SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();

}


int main(int argc, char *argv[]){

    // srand(time(0));

    Init();
    LoadMedia();


    bool QuitMenu = false;
    bool Play = false;
    bool MenuAndGameLoop = true;

    while(MenuAndGameLoop){
//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//        SDL_RenderClear(renderer);

        //Menu Loop
        while(!QuitMenu){
            SDL_Event e_mouse;
            while(SDL_PollEvent(&e_mouse) != 0){
                if (e_mouse.type == SDL_QUIT){
                    Play = false;
                    QuitMenu = true;
                    MenuAndGameLoop = false;
                }

                HandlePlayButton(&e_mouse, PlayButton, QuitMenu, Play);
                HandleExitButton(&e_mouse, ExitButton, QuitMenu);
            }

            SDL_RenderCopy(renderer,MenuTex,NULL,NULL);
            PlayButton.Render(NULL,renderer,PlayButtonTex[PlayButton.currentState]);
            ExitButton.Render(NULL,renderer,ExitButtonTex[ExitButton.currentState]);

            SDL_RenderPresent(renderer);
        }
    //Game loop
        while(Play){
            SDL_Event e;
            int score= 0;
            string highscore = GetHighScoreFromFile("high_score.txt");
            bool Quit = false;
            bool GameState = true;
            racerRect.x = SCREEN_WIDTH/2;
            racerRect.y = SCREEN_HEIGHT - racerRect.h;
            obs1Rect.y=0;obs2Rect.y=-100; obs3Rect.y=-200;obs4Rect.y=-300; backgroundRect.x = 0; background1Rect.x = 0;
            backgroundRect.y=0;
            background1Rect.y=-600;
            obs1Rect.x=getRandomNumber(borderLeft,borderRight);
            obs2Rect.x=getRandomNumber(borderLeft,borderRight);
            obs3Rect.x=getRandomNumber(borderLeft,borderRight);
            obs4Rect.x=getRandomNumber(borderLeft,borderRight);

            while(!Quit){
                //In game
                if(GameState){


                    if( Mix_PlayingMusic() == 0 ){
                        //Play the music
                        Mix_PlayMusic( gMusic, -1 );
                    }


                    while (SDL_PollEvent(&e) != 0){
                        if (e.type == SDL_QUIT  ){
                            MenuAndGameLoop = false;
                            Quit = true;
                            Play = false;
                        }
                        if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    MenuAndGameLoop = false;
                            Quit = true;
                            Play = false;
                }
                if(e.key.keysym.sym == SDLK_LEFT){if(racerRect.x > borderLeft){racerRect.x =racerRect.x - 20;}}
                if(e.key.keysym.sym==SDLK_RIGHT) {if(racerRect.x < borderRight){racerRect.x =racerRect.x + 20;}}
                if(e.key.keysym.sym == SDLK_DOWN) {if(racerRect.y < SCREEN_HEIGHT - 70){racerRect.y = racerRect.y + 20;}}
                if(e.key.keysym.sym == SDLK_UP) {if(racerRect.y > 0){racerRect.y = racerRect.y - 20;}}
            }
                        HandlePauseButton(&e, renderer, PauseButton, ContinueButton, ContinueButtonTex,  GameState);
                    }
                    SDL_RenderClear(renderer);
                    if (background1Rect.y>0)
                    {
                       backgroundRect.y=0;
                       background1Rect.y=backgroundRect.y-500;
                    }
                    backgroundRect.y+=1;
                    background1Rect.y+=1;
                    if(obs1Rect.y>SCREEN_HEIGHT)
                        {obs1Rect.y=0;obs1Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs1Rect.y=obs1Rect.y+gameSpeed;}
                    if (obs2Rect.y>SCREEN_HEIGHT)
                        {obs2Rect.y=0;obs2Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs2Rect.y=obs2Rect.y+gameSpeed;}
                    if (obs3Rect.y > SCREEN_HEIGHT)
                        {obs3Rect.y=0;obs3Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs3Rect.y=obs3Rect.y+gameSpeed;}
                    if (obs4Rect.y>SCREEN_HEIGHT)
                        {obs4Rect.y=0;obs4Rect.x=getRandomNumber(borderLeft,borderRight);score++;} else {obs4Rect.y=obs4Rect.y+gameSpeed;}

                    bool collide = false;
                    if(CheckCollision(racerRect, obs1Rect) || CheckCollision(racerRect, obs2Rect)
                       || CheckCollision(racerRect, obs3Rect) || CheckCollision(racerRect, obs4Rect)){
                            collide = true;
                    }

                    if(collide){
                        Mix_HaltMusic();
                        Mix_PlayChannel( -1, over_Music, 0);
                        UpdateHighScore("high_score.txt", score, highscore);
                        Quit = true;
                    }


                    SDL_RenderCopy(renderer, background, NULL, &backgroundRect);
                    SDL_RenderCopy(renderer, background1, NULL, &background1Rect);
                    SDL_RenderCopy(renderer, racer, NULL, &racerRect);
                    SDL_RenderCopy(renderer, obs1, NULL, &obs1Rect);
                    SDL_RenderCopy(renderer, obs2, NULL, &obs2Rect);
                    SDL_RenderCopy(renderer, obs3, NULL, &obs3Rect);
                    SDL_RenderCopy(renderer, obs4, NULL, &obs4Rect);


                    DrawPlayerScore(score_game,renderer, gFont, score);
                    DrawPlayerHighScore(high_score_game,renderer, gFont, highscore);


                    PauseButton.Render (NULL,renderer, PauseButtonTex[PauseButton.currentState]);


                    SDL_RenderPresent(renderer);

            }
        }
        //POST GAME

            DrawEndGameSelection(GameOverTex, NewGameButton, NewGameButtonTex, QuitButton, QuitButtonTex, MenuButton, MenuButtonTex,
                              &e, renderer, Play, score, stoi(highscore), QuitMenu, MenuAndGameLoop);

    }
}
     //waitUntilKeyPressed();

    Close();
     return 0;
}



