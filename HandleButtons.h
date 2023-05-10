#ifndef HANDLE_BUTTONS_H
#define HANDLE_BUTTONS_H
#include "Button.h"
#include "GameFeatures.h"
void HandlePlayButton(SDL_Event* e, Button& PlayButton, bool& QuitMenu, bool& Play);

void HandleExitButton(SDL_Event* e, Button& ExitButton);

void HandleContinueButton(Button ContinueButton, TextObject ContinueButtonTex[BUTTON_STATES], SDL_Event* e,
                          SDL_Renderer* Renderer,   bool& GameState);

void HandlePauseButton(SDL_Event* e,  SDL_Renderer* Renderer,  Button& PauseButton, Button ContinueButton, TextObject ContinueButtonTex[BUTTON_STATES], bool& GameState);

void HandleNewGameButton(SDL_Event* e, Button& NewGameButton, bool& Quit, bool& Play);

void HandleMenuButton(SDL_Event* e, Button& MenuButton, bool& Quit, bool& Play, bool& QuitMenu);

void HandleQuitButton(SDL_Event* e, Button& QuitButton, bool& Quit, bool& Play, bool& MenuAndGameLoop);

#endif // HANDLE_BUTTONS_H
