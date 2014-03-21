#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

void main()
{
	int type;
	Game *game;

	srand((unsigned int)time(0));

	printf("Players vs player (1)\nPlayer vs computer (2)\nComputer vs computer (3)\n");
	scanf("%d", &type);
	fflush(stdin);

	game = newGame();

	if(type == PvP)
	{
		while(!gameOver(game))
		{
			printPosition(game);
			playerMove(game);
		}
	}
	else if(type == PvC)
	{
		chooseColor(game);
		while(!gameOver(game))
		{
			printPosition(game);

			if(game->player == game->pos->moves)
				playerMove(game);
			else
				computerMove(game);
		}
	}
	else if(type == CvC)
	{
		while(!gameOver(game))
		{
			printPosition(game);
			computerMove(game);
			//getchar();
		}
	}

	printPosition(game);
	printWinner(game);
	deleteGame(game);
	getchar();
}
