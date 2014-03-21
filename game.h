#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "position.h"

#define PvP 1
#define PvC 2
#define CvC 3

typedef struct {
	int player, computer;
	int nmove;
	Position *pos;
} Game;

Game* newGame();

void chooseColor(Game *game);

void deleteGame(Game *game);

void printPosition(Game *game);

void playerMove(Game *game);

void computerMove(Game *game);

int gameOver(Game *game);

void printWinner(Game *game);

#endif // GAME_H_INCLUDED
