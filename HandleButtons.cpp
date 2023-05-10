
#include "HandleButtons.h"
void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play){
    if (e->type == SDL_QUIT){
        exit(1);
	}

	if (PlayButton.IsInside(e, BIG_BUTTON)){
        PlayButton.currentState = BUTTON_MOUSE_OVER;
		if(e->type == SDL_MOUSEBUTTONDOWN){
                Play = true;
                QuitMenu = true;
		}
    }

	else {
        PlayButton.currentState = BUTTON_MOUSE_OUT;

    }
}

void HandleExitButton(SDL_Event* e, Button& ExitButton){
    if (ExitButton.IsInside(e, BIG_BUTTON)){
        ExitButton.currentState = BUTTON_MOUSE_OVER;
        if(e->type == SDL_MOUSEBUTTONDOWN){
            exit(1);
        }
    }
	else{
        ExitButton.currentState = BUTTON_MOUSE_OUT;
    }
}

void HandleContinueButton(Button ContinueButton, TextObject ContinueButtonTex[BUTTON_STATES], SDL_Event* e,
                          SDL_Renderer* Renderer,   bool& GameState)
{
    bool BackToGame = false;
	while (!BackToGame){
		do{
			if (ContinueButton.IsInside(e, SMALL_BUTTON)){
                ContinueButton.currentState = BUTTON_MOUSE_OVER;
				if(e->type == SDL_MOUSEBUTTONDOWN){
                        ContinueButton.currentState = BUTTON_MOUSE_OVER;
                        Mix_ResumeMusic();
                        GameState = true;
                        BackToGame = true;
				}
			}
			else{
				ContinueButton.currentState = BUTTON_MOUSE_OUT;
			}
            SDL_Rect continue_;
            continue_ = {ContinueButton.position.x, ContinueButton.position.y, ContinueButtonTex[ContinueButton.currentState].width_,
            ContinueButtonTex[ContinueButton.currentState].height_};
            SDL_RenderCopy(Renderer,ContinueButtonTex[ContinueButton.currentState].texture_,NULL,&continue_);


			SDL_RenderPresent(Renderer);
		}while (SDL_WaitEvent(e) != 0 && (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEMOTION));
	}
}


void HandlePauseButton(SDL_Event* e,  SDL_Renderer* Renderer,  Button& PauseButton, Button ContinueButton, TextObject ContinueButtonTex[BUTTON_STATES], bool& GameState)
{
    if (PauseButton.IsInside(e, SMALL_BUTTON)){
        PauseButton.currentState = BUTTON_MOUSE_OVER;
		switch (e->type){
            case SDL_MOUSEBUTTONDOWN:
                Mix_PauseMusic();
                break;
            case SDL_MOUSEBUTTONUP:
                GameState = false;
                HandleContinueButton(ContinueButton, ContinueButtonTex, e, Renderer, GameState);
                break;
		}
	}
	else PauseButton.currentState = BUTTON_MOUSE_OUT;
}
void HandleNewGameButton(SDL_Event* e, Button& NewGameButton, bool& Quit, bool& Play){
     if(NewGameButton.IsInside(e, BIG_BUTTON)){
        NewGameButton.currentState = BUTTON_MOUSE_OVER;
        if(e->type == SDL_MOUSEBUTTONDOWN){
            Quit = true;
            Play = true;
        }
     }
    else NewGameButton.currentState = BUTTON_MOUSE_OUT;
}

void HandleMenuButton(SDL_Event* e, Button& MenuButton, bool& Quit, bool& Play, bool& QuitMenu){
    if(MenuButton.IsInside(e, BIG_BUTTON)){
        MenuButton.currentState = BUTTON_MOUSE_OVER;
        if(e->type == SDL_MOUSEBUTTONDOWN){
            Quit = true;
            QuitMenu = false;
            Play = false;
        }
    }
    else MenuButton.currentState = BUTTON_MOUSE_OUT;
}

void HandleQuitButton(SDL_Event* e, Button& QuitButton, bool& Quit, bool& Play, bool& MenuAndGameLoop){
    if(QuitButton.IsInside(e, BIG_BUTTON)){
        QuitButton.currentState = BUTTON_MOUSE_OVER;
        if(e->type == SDL_MOUSEBUTTONDOWN){
            Quit = true;
            Play = false;
            MenuAndGameLoop = false;
        }
    }
    else QuitButton.currentState = BUTTON_MOUSE_OUT;
}

