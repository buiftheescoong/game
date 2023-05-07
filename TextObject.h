
#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H
#include "Game.h"

class TextObject{
public:
  TextObject(){
   /* text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;*/
    texture_ = NULL;
    width_ = 0;
    height_= 0;
  }
  ~TextObject(){
    Free();
  }

  enum TextColor
  {
    RED_TEXT  = 0,
    WHITE_TEXT = 1,
    BLACK_TEXT = 2,
  };

  bool loadFromRenderedText(TTF_Font* gFont, SDL_Renderer* renderer){
     //Render text surface
      SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);
      if( textSurface != NULL )
      {
        //Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface(renderer, textSurface );
        if( texture_ != NULL )
        {
          //Get image dimensions
          width_ = textSurface->w;
          height_ = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
      }

      //Return success
      return texture_ != NULL;
  }
  bool LoadFromFile(string path, SDL_Renderer* Renderer)
    {
        //Free();

        SDL_Texture* tmpTexture = NULL;

        SDL_Surface* tmpSurface = IMG_Load(path.c_str());
        if (tmpSurface == NULL){
            cout << "Can not load image!" << endl;
        }
        else{
            tmpTexture = SDL_CreateTextureFromSurface(Renderer, tmpSurface);
            if (tmpTexture == NULL){
                cout << "Can not create texture from surface!" << endl;
            }
            else{
                width_ = tmpSurface->w;
                height_ = tmpSurface->h;
            }

            SDL_FreeSurface(tmpSurface);
        }

        texture_ = tmpTexture;

        return texture_ != NULL;
    }
  void Free(){
     if(texture_ != NULL)
      {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
      }
  }

  void setColor(int type){
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        text_color_ = color;
    }
    else
    {
        SDL_Color color = {0, 0, 0};
        text_color_ = color;
    }
  }

  void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL){
    //Set rendering space and render to screen
      SDL_Rect renderQuad = { x, y, width_, height_ };

      //Set clip rendering dimensions
      if( clip != NULL )
      {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
      }

      //Render to screen
      SDL_RenderCopy(renderer, texture_, clip, &renderQuad );

  }




  int getWidth() const {return width_;}
  int getHeight() const {return height_;}
  void SetText(const string& text) {str_val_ = text;}
  string GetText() const {return str_val_;}

private:
  string str_val_;
  SDL_Color text_color_;
  SDL_Texture* texture_;
  int width_;
  int height_;

};

#endif // TEXT_OBJECT_H
