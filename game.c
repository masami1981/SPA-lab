#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "game.h"

Game* newGame()
{
	Game *game;
	game = (Game*) malloc(sizeof(Game));
	game->nmove = 0;
	game->pos = initPos();
	return game;
}

void chooseColor(Game *game)
{
	char inbuff[128];
	while(1)
	{
		printf("Play with (w)hite or (b)lack? ");
		fgets(inbuff, 127, stdin);
		if(inbuff[0] == 'w')
		{
			game->player = WHITE;
			game->computer = BLACK;
			break;
		}
		else if(inbuff[0] == 'b')
		{
			game->player = BLACK;
			game->computer = WHITE;
			break;
		}
	}
}

void deleteGame(Game *game)
{
	free(game->pos);
	free(game);
}

void printPosition(Game *game)
{
	printf("Move #%d\n", 1 + game->nmove / 2);
	printPos(game->pos);
}

void playerMove(Game *game)
{
	Move mov;
	char inbuff[128];

	do {
		printf("Enter move: ");
		fgets(inbuff, 127, stdin);
		stringToMove(inbuff, &mov);
	} while(!isLegalMove(game->pos, &mov));

	playMove(game->pos, &mov);
	game->nmove++;
}

void computerMove(Game *game)
{
	char outbuff[128];
	Move mov;
	randomMove(game->pos, &mov);
	moveToString(&mov, outbuff);
	if(!isLegalMove(game->pos, &mov))
	{
		printf("Illegal random move %s!\n", outbuff);
		getchar();
	}
	else
		printf("Computer move: %s\n", outbuff);
	playMove(game->pos, &mov);
	game->nmove++;
}

int gameOver(Game *game)
{
	return checkWinner(game->pos);
}

void printWinner(Game *game)
{
	int w = checkWinner(game->pos);

	if(w == WHITE_WINS)
		printf("White wins!\n");
	else if(w == BLACK_WINS)
		printf("Black wins!\n");
	else
		printf("Draw!\n");
}
