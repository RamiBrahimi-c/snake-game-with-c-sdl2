#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_PLAYER_NAME 20
#define PLAYERS_FILE_NAME ".players.data"

typedef struct Player
{
    int id ;
    char name[20] ;
    int score ;
    int gamesPlayed ;
}Player;



void initPlayers(FILE *) ;
void addPlayer(FILE * , Player) ; 
int getPlayersNumber(FILE *) ;

int initPlayersFile() ;



void addPlayer(FILE *ptr, Player player) ;

void deletePlayer(FILE *ptr , int id) ;

void sortPlayers(Player *arr ,int length) ;
// players file
// mode 1
// metadata / player 1 / player 2 / player 3 / .. / player n  
// or   
// player 1 / player 2 / player 3 / .. / player n  

void swapPlayers(Player  *, Player *) ;

void printPlayers(FILE *) ;

void assignPlayer(Player*  , Player* ) ;

