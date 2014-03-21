#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "position.h"

Position* initPos()
{
	int r, c;
	Position *pos = (Position*) malloc(sizeof(Position));
	pos->moves = BLACK;
	for(r=0; r < 8; r++)
		for(c=0; c < 8; c++)
			if(r < 3 && (r+c)%2 == 1)
				pos->board[r][c] = PAWN|BLACK;
			else if(r > 4 && (r+c)%2 == 1)
				pos->board[r][c] = PAWN|WHITE;
			else
				pos->board[r][c] = EMPTY;
	return pos;
}

void printPos(Position *pos)
{
	int r, c, n, i;
	char outbuff[256];
	Move marray[256];

	if(pos->moves == WHITE)
		printf("White moves:");
	else
		printf("Black moves:");

	n = movesList(pos, marray);
	for(i = 0; i < n; i++)
	{
		moveToString(marray+i, outbuff);
		if(isLegalMove(pos, marray+i))
			printf(" %s", outbuff);
		else
			printf(" !%s", outbuff);
	}
	printf("\n");

	printf("  ");
	for(c=0; c < 8; c++)
		printf(" %c", 'a' + c);
	printf("\n");
	for(r=0; r < 8; r++)
	{
		printf(" %d", r+1);
		for(c=0; c < 8; c++)
			if(pos->board[r][c] == (PAWN|BLACK))
				printf(" B");
			else if(pos->board[r][c] == (PAWN|WHITE))
				printf(" W");
			else
				printf(" -");
		printf("\n");
	}
}

int movesList(Position *pos, Move *marray)
{
	// TODO:
	// Funkcija generira sve legalne poteze u poziciji i sprema ih u niz marray
	// (marray je alociran). Funkcija se oslanja na funkciju pawnMovesList.
	// Funkcija vraæa broj legalnih poteza.
	return 0;
}

int pawnMovesList(int r, int c, Position *pos, Move *marray)
{
	// Funkcija generira sve poteze za pjeaka na (r,c) koordinatama
	// i sprema ih u niz marray.
	int count=0;
	if(pos->board[r][c] == (PAWN|BLACK) && (r<7))
	{
		if((pos->board[r+1][c-1] == EMPTY) && (c>0) )
		{
			(marray+count)->from_c = c;
			(marray+count)->from_r = r;
			(marray+count)->to_r = r+1;
			(marray+count)->to_c= c-1;
			count++;
		}
		if((pos->board[r+1][c+1] == EMPTY) && (c<7) )
		{
			(marray+count)->from_c = c;
			(marray+count)->from_r = r;
			(marray+count)->to_r = r+1;
			(marray+count)->to_c= c+1;
			count++;
		}
	}
	else if(pos->board[r][c] == (PAWN|WHITE) && (r>0))
	{
		if((pos->board[r-1][c-1] == EMPTY) && (c>0) )
		{
			(marray+count)->from_c = c;
			(marray+count)->from_r = r;
			(marray+count)->to_r = r-1;
			(marray+count)->to_c= c-1;
			count++;
		}
		if((pos->board[r-1][c+1] == EMPTY) && (c<7) )
		{
			(marray+count)->from_c = c;
			(marray+count)->from_r = r;
			(marray+count)->to_r = r-1;
			(marray+count)->to_c= c+1;
			count++;
		}
	}
	return count;
}

int isLegalMove(Position *pos, Move *mov)
{
	// out of board ?
	if( !((0 <= mov->from_r && mov->from_r <= 7) &&
		(0 <= mov->from_c && mov->from_c <= 7) &&
		(0 <= mov->to_r && mov->to_r <= 7) &&
		(0 <= mov->to_c && mov->to_c <= 7)) )
		return 0;

	// white
	if( pos->moves == WHITE &&
		pos->board[mov->from_r][mov->from_c] == (PAWN|WHITE) &&
		pos->board[mov->to_r][mov->to_c] == EMPTY )
	{
		// normal move
		if( mov->from_r == mov->to_r+1 &&
			(mov->from_c == mov->to_c+1 || mov->from_c == mov->to_c-1) )
			return 1;
		// jump
		if( (mov->from_r == mov->to_r+2 &&
			 mov->from_c == mov->to_c+2 &&
			 pos->board[mov->to_r+1][mov->to_c+1] == (PAWN|BLACK)) ||
			(mov->from_r - 2 == mov->to_r &&
			 mov->from_c == mov->to_c-2 &&
			 pos->board[mov->to_r+1][mov->to_c-1] == (PAWN|BLACK)) )
			return 1;
	}

	// black
	if( pos->moves == BLACK &&
		pos->board[mov->from_r][mov->from_c] == (PAWN|BLACK) &&
		pos->board[mov->to_r][mov->to_c] == EMPTY )
	{
		// normal move
		if( mov->from_r == mov->to_r-1 &&
			(mov->from_c == mov->to_c+1 || mov->from_c == mov->to_c-1) )
			return 1;
		// jump
		if( (mov->from_r == mov->to_r-2 &&
			 mov->from_c == mov->to_c+2 &&
			 pos->board[mov->to_r-1][mov->to_c+1] == (PAWN|WHITE)) ||
			(mov->from_r == mov->to_r-2 &&
			 mov->from_c == mov->to_c-2 &&
			 pos->board[mov->to_r-1][mov->to_c-1] == (PAWN|WHITE)) )
			return 1;
	}
	return 0;
}

void playMove(Position *pos, Move *mov)
{
	if(pos->moves == WHITE)
	{
		if(mov->from_r - 1 == mov->to_r)
		{
			// normal
			pos->board[mov->from_r][mov->from_c] = EMPTY;
			pos->board[mov->to_r][mov->to_c] = (PAWN|WHITE);
		}
		else if(mov->from_r - 2 == mov->to_r)
		{
			// jump
			pos->board[mov->from_r][mov->from_c] = EMPTY;
			pos->board[(mov->from_r+mov->to_r)/2][(mov->from_c+mov->to_c)/2] = EMPTY;
			pos->board[mov->to_r][mov->to_c] = (PAWN|WHITE);
		}
		else
		{
			char outbuff[256];
			moveToString(mov, outbuff);
			printf("Illegal move %s\n", outbuff);
			getchar();
		}
	}
	else
	{
		if(mov->from_r + 1 == mov->to_r)
		{
			// normal
			pos->board[mov->from_r][mov->from_c] = EMPTY;
			pos->board[mov->to_r][mov->to_c] = (PAWN|BLACK);
		}
		else if(mov->from_r + 2 == mov->to_r)
		{
			// jump
			pos->board[mov->from_r][mov->from_c] = EMPTY;
			pos->board[(mov->from_r+mov->to_r)/2][(mov->from_c+mov->to_c)/2] = EMPTY;
			pos->board[mov->to_r][mov->to_c] = (PAWN|BLACK);
		}
		else
		{
			char outbuff[256];
			moveToString(mov, outbuff);
			printf("Illegal move %s\n", outbuff);
			getchar();
		}
	}

	pos->moves = (pos->moves == WHITE)? BLACK: WHITE;
}

void undoMove(Position *pos, uMove *mov)
{

}

void randomMove(Position *pos, Move *mov)
{
	int n, i;
	Move marray[128];
	n = movesList(pos, marray);
	if(n > 0)
	{
		i = rand() % n;
		*mov = marray[i];
	}
	else
	{
		printf("Zero legal moves!\n");
		getchar();
	}
}

int checkWinner(Position *pos)
{
	int n;
	Move marray[128];
	n = movesList(pos, marray);
	if(n == 0)
	{
		int r, c;
		int wcnt, bcnt;
		wcnt = 0;
		bcnt = 0;
		for(r=0; r < 8; r++)
			for(c=0; c < 8; c++)
				if(pos->board[r][c] == (PAWN|WHITE))
					wcnt++;
				else if(pos->board[r][c] == (PAWN|BLACK))
					bcnt++;

		if(wcnt > bcnt)
			return WHITE_WINS;
		else if(wcnt < bcnt)
			return BLACK_WINS;
		else
			return DRAW;
	}
	else
		return 0;
}

void stringToMove(char *str, Move *mov)
{
	if(strlen(str) < 4)
	{
		printf("Illegal string move: %s!\n", str);
		getchar();
		return;
	}
	mov->from_c = (str[0]-'a');
	mov->from_r = (str[1]-'1');
	mov->to_c = (str[2]-'a');
	mov->to_r = (str[3]-'1');
}

void moveToString(Move *mov, char *str)
{
	str[0] = 'a' + mov->from_c;
	str[1] = '1' + mov->from_r;
	str[2] = 'a' + mov->to_c;
	str[3] = '1' + mov->to_r;
	str[4] = '\0';
}
