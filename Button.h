#ifndef BUTTON_H
#define BUTTON_H
#define SMALL_BUTTON 1
#define BIG_BUTTON 2

#include "TextObject.h"
const int BIG_BUTTON_WIDTH = 250;
const int BIG_BUTTON_HEIGHT = 83;
const int SMALL_BUTTON_WIDTH = 30;
const int SMALL_BUTTON_HEIGHT = 30;

using namespace std;
enum ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1
};

class Button
{
public:
	ButtonState currentState;
	Button(int x, int y);
	bool IsInside(SDL_Event *e, int size_);
	void Render(SDL_Rect* currentClip, SDL_Renderer* Renderer, TextObject ButtonTex);

private:
	SDL_Point position;
};
#endif // BUTTON_H


