#ifndef BASE_H
#define BASE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <bits/stdc++.h>

using namespace std;
#define SMALL_BUTTON 1
#define BIG_BUTTON 2
const string WINDOW_TITLE = "CAR GAME";

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int BIG_BUTTON_WIDTH = 250;
const int BIG_BUTTON_HEIGHT = 83;
const int SMALL_BUTTON_WIDTH = 30;
const int SMALL_BUTTON_HEIGHT = 30;



const int PLAY_BUTTON_POSX = 5;
const int PLAY_BUTTON_POSY= 300;
const int EXIT_BUTTON_POSX = 5;
const int EXIT_BUTTON_POSY = 500;
const int PAUSE_BUTTON_POSX = 30;
const int PAUSE_BUTTON_POSY = 30;
const int CONTINUE_BUTTON_POSX = 30;
const int CONTINUE_BUTTON_POSY = 30;
const int NEWGAME_BUTTON_POSX = 5;
const int NEWGAME_BUTTON_POSY = 300;
const int MENU_BUTTON_POSX = 5;
const int MENU_BUTTON_POSY = 400;
const int QUIT_BUTTON_POSX = 5;
const int QUIT_BUTTON_POSY = 500;

const int BUTTON_STATES = 2;
enum ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1
};




#endif // BASE_H
