#include "Button.h"

Button::Button(int x, int y)
{
	position.x = x;
	position.y = y;

	currentState = BUTTON_MOUSE_OUT;
}

bool Button::IsInside(SDL_Event *e, int size_)
{
    int x, y;
    int button_width, button_height;
    if (size_ == SMALL_BUTTON){
        button_width = SMALL_BUTTON_WIDTH;
        button_height = SMALL_BUTTON_HEIGHT;
    }
    else{
        button_width = BIG_BUTTON_WIDTH;
        button_height = BIG_BUTTON_HEIGHT;
    }

    SDL_GetMouseState(&x, &y);

    bool inside = true;
    if (x < position.x || x > position.x + button_width){
        inside = false;
    }

    if (y < position.y || y > position.y + button_height){
        inside = false;
    }

    return inside;
}

void Button::Render(SDL_Rect* currentClip, SDL_Renderer* gRenderer, TextObject gButtonTexture)
{
	gButtonTexture.Render(gRenderer,position.x, position.y , currentClip);
}

