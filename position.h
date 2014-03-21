#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED

#define WHITE 0
#define BLACK 1

#define EMPTY 0
#define PAWN  2

#define COLOR(x) ((x)&1)

#define WHITE_WINS 1
#define BLACK_WINS 2
#define DRAW       3

typedef struct {
	int moves;
	char board[8][8];
} Position;

typedef struct {
	int from_r, from_c;
	int to_r, to_c;
} Move;

typedef struct {
	int from_r, from_c;
	int to_r, to_c;
} uMove;

Position* initPos();

void printPos(Position *pos);

int movesList(Position *pos, Move *marray);

int pawnMovesList(int r, int c, Position *pos, Move *marray);

int isLegalMove(Position *pos, Move *mov);

void playMove(Position *pos, Move *mov);

//void undoMove(Position *pos, Move *mov);

void randomMove(Position *pos, Move *mov);

int checkWinner(Position *pos);

void stringToMove(char *str, Move *mov);

void moveToString(Move *mov, char *str);

#endif // POSITION_H_INCLUDED
