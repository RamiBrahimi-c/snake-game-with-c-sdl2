#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


typedef struct ChoiceRectangle
{
    char text[10] ;
    SDL_Rect rect ;
    struct ChoiceRectangle* prev ;
    struct ChoiceRectangle* next ;
}ChoiceRectangle;

typedef struct MenuChoiceRectangle
{
    int size ;
    ChoiceRectangle *head ;
    ChoiceRectangle *current_choice;
}MenuChoiceRectangle;




void initSettingsMenuChoiceRectangle(MenuChoiceRectangle *settings , int size) ;


void addFifoChoiceRectangle(ChoiceRectangle **head ,ChoiceRectangle data) ;


void initMenuChoiceRectangle(MenuChoiceRectangle *menu , int size) ;

void renderMenu(SDL_Renderer *renderer , TTF_Font* font , MenuChoiceRectangle menu) ; 


int getWindowWidth() ;

int getWindowHeight() ; 

void setWindowWidth(int w) ;

void setWindowHeight(int h ) ;


int getGridDimension() ;

void setGridDimension(int gridDim) ;
