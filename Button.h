#ifndef BUTTON_H
#define BUTTON_H


#include "TextObject.h"
#include "Base.h"

using namespace std;

class Button
{
public:
	ButtonState currentState;
	Button(int x, int y);
	bool IsInside(SDL_Event *e, int size_);

	SDL_Point position;
};
#endif // BUTTON_H


