#ifndef GAME_FEATURES_H
#define GAME_FEATURES_H

#include "Button.h"

//void LoadMedia();
void DrawEndGameSelection(TextObject GameOverTex[2], Button& NewGameButton, TextObject NewGameButtonTex[BUTTON_STATES],
                         Button& QuitButton, TextObject QuitGameButtonTex[BUTTON_STATES], Button& MenuButton,
                        TextObject MenuButtonTex[BUTTON_STATES], SDL_Event* e, SDL_Renderer* Renderer, bool &Play, int score,
                          int highscore, bool& QuitMenu, bool& MenuAndGameLoop);
#endif // GAME_FEATURES_H
