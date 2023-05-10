
#ifndef SCORE_H
#define SCORE_H

#include "TextObject.h"
string GetHighScoreFromFile(string path){
    ifstream HighScoreFile(path);
	string highscore;

	if(HighScoreFile.is_open()){
        HighScoreFile >> highscore;
	}
	else cout << "Cannot open high score file!" << endl;

	return highscore;
}

void UpdateHighScore(string path, const int& score, const string& old_high_score){
    int oldHighScore = 0;
	string newHighScore;
	stringstream ConvertToInt(old_high_score);
    ConvertToInt >> oldHighScore;

	ofstream HighScoreFile(path);
	if(HighScoreFile.is_open()){
        if(score > oldHighScore){
            oldHighScore = score;
        }
        newHighScore = to_string(oldHighScore);
        HighScoreFile << newHighScore;
    }
	else cout << "Cannot open high score file!" << endl;
}


void DrawPlayerScore(TextObject score_game,SDL_Renderer* renderer, TTF_Font* Font, const int& score){

    score_game.setColor(1);
    string value_score_game = to_string(score);
    string str_score = "Score : ";
    str_score += value_score_game;
    score_game.SetText(str_score);
    score_game.loadFromRenderedText(Font, renderer);
    score_game.Render(renderer, 0,0);
}

void DrawPlayerHighScore(TextObject high_score_game, SDL_Renderer* Renderer, TTF_Font* Font, const string& HighScore){

    high_score_game.setColor(1);
    string str_high_score = "High Score : ";
    str_high_score += HighScore;
    high_score_game.SetText(str_high_score);
    high_score_game.loadFromRenderedText(Font, Renderer);
    high_score_game.Render(Renderer,600, 0);
}






#endif // SCORE_H
