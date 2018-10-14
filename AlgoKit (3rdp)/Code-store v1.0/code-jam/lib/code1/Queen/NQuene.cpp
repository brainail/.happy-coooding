#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<DOS.h>

#define SQSIZE 30
#define DELAY 500

long count = 0;
void initialize_graphics(int&, int&);
int** MakeChessBoard(int);
int PlaceQueens(int**, int, int);
int CheckKill(int**, int, int, int);
void CreateChessBoard(int**, int);
void DeleteChessBoard(int**, int);
void PlaceQueen(int, int);
void RemoveQueen(int, int) ;
void HomeQueen(int);

int max_x, max_y;

void main()
{
	int** chessboard;
	int i, j, size;
	printf("N-Queen Problem\nPress any Key to continue...");
	getch();
	do
	{
		clrscr();
		printf("Enter Size of chessBoard[Number of rows or columns ie. N]:");
		scanf("%d", &size);
		if (size < 4)
		{
			printf("\nThere is NO solution for N<4");
			getch();
		}
	}while (size < 4);
	chessboard = MakeChessBoard(size);
	initialize_graphics(max_x, max_y);
	CreateChessBoard(chessboard, size);
	PlaceQueens(chessboard, size, 0);
	getch();
	DeleteChessBoard(chessboard, size);
}
int** MakeChessBoard(int size)
{
	int** chessboard;
	int i, j;
	/*Allocate Double Dimention Array*/
	chessboard = (int * *) malloc(sizeof(int) * size);
	for (i = 0; i < size; i++)
		chessboard[i] = (int *) malloc(sizeof(int) * size);
		/*Initialize Double Dimention Array*/
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			chessboard[i][j] = 0;

	return chessboard;
}
int PlaceQueens(int** chessboard, int size, int level)
{
	count++;
	int Q_placed = 0; /*
	Q_placed is a flag reflecting that whether a Queen
	is placed on the current level or not.
	This value is returned to preceeding levels.
	*/
	int QNextLevel; /*
	QNextLevel is a flag reflecting that whether a Queen
	is placed on the next level or not.
	During recurssion this Flag will allow recurssion
	 */
	int flag;    /*
	Determines whether a Queen can be placed at current
	position or not.
	*/
	int i;
	for (i = 0; i < size; i++)
	{
		 /*Breaks the loops after all the Queens have been placed*/
		if (Q_placed == 1)
			break;
		 /*Check whether Queen can be placed or not*/
		 flag = CheckKill(chessboard, size, level, i);
		 /*If Queen can be placed*/
		 if (flag == 0)
		 {
			 /*Queen Placed. This will be changed if Next level Queen is
			 not placed succesfully*/
			 Q_placed = 1;
			 /*Queen Placed. */
			 chessboard[level][i] = 1;
			 PlaceQueen(level, i);
			  /*Check for Last level*/
			 if (level == size - 1)
				;
			 else /*Place a next level Queen*/
			 {
				QNextLevel = PlaceQueens(chessboard, size, level + 1);
				/*If next level Queen is not Placed.*/
				if (QNextLevel == 0)
				{
					  /*Mark this level Queen as Not Placed*/
					  Q_placed = 0;
					  chessboard[level][i] = 0;
					  RemoveQueen(level, i);
					  if (i == size - 1)
						HomeQueen(level);
				}
			 }
		 }
		 else if (flag == 1)
		 {
			PlaceQueen(level, i);
			RemoveQueen(level, i);
			if (i == size - 1)
				HomeQueen(level);
		 }
	}
	return Q_placed;
}
int CheckKill(int** chessboard, int size, int row, int column)
{
	int i, j;
	for (i = 0; i < row; i++)/*ROW Loop: Only From 0 to (Current Level - 1) */
		for (j = 0; j < size; j++)/*COLUMN Loop:From 0 to ChessBoardsize */
			if (chessboard[i][j] == 1)/*If there is a Queen*/
				if (j == column)
					return 1; /*If Queen is in the same column*/

			else if (abs(i - row) == abs(j - column))
				return 1;/*If it is Diagonal*/
		return 0;
}
void CreateChessBoard(int** chessboard, int size)
{
	setfillstyle(SOLID_FILL, LIGHTBLUE);
	setcolor(RED);
	bar(0, 0, max_x, max_y);
	for (int i = 0; i < size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			if (i % 2 == j % 2)
				setfillstyle(SOLID_FILL, WHITE);
			else
				setfillstyle(SOLID_FILL, YELLOW);
			bar(j * SQSIZE, i * SQSIZE, (j + 1) * SQSIZE, (i + 1) * SQSIZE);
		}
	}
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
	setcolor(WHITE);
	outtextxy(max_x - 300, max_y - 50, "N Queen -PCD-");
	setcolor(RED);
	setlinestyle(SOLID_LINE, 0, 1);
	for (int p = 0; p <= max_x; p += SQSIZE)
		line(p, 0, p, max_y);
	for (p = 0; p <= max_x; p += SQSIZE)
		line(0, p, max_x, p);
	}
void DeleteChessBoard(int** chessboard, int size)
{
	int i;
	for (i = 0; i < size; i++)
	free(chessboard[i]);
	free(chessboard);
}
void initialize_graphics(int& max_x, int& max_y)
{
	/*
	initialize_graphics() function initializes the graphic enviroment.
	*/
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "E:\\tc\\bgi");
	/* read result of initialization */
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error:",grapherrormsg(errorcode));
		printf( "Press any key to halt:");
		getch();
		exit(1); /* terminate with an error code */
	}
	max_x = getmaxx();
	max_y = getmaxy();
}
void PlaceQueen(int row, int column)
{
	if (column == 0)/*Queen was in HOme*/
	{
		setfillstyle(SOLID_FILL, LIGHTBLUE) ;
		setcolor(LIGHTBLUE);
		pieslice(SQSIZE / 2, row * SQSIZE + SQSIZE / 2, 0, 360, 4);
	}
	delay(100);sound(400);delay(DELAY);nosound();
	setfillstyle(SOLID_FILL, BLUE) ;
	setcolor(BLUE);
	pieslice((column + 1) * SQSIZE + SQSIZE / 2, row * SQSIZE + SQSIZE / 2, 0,360, 4);
}
void RemoveQueen(int row, int column)
{
	delay(500);
	sound(200);
	delay(DELAY+300);
	nosound();
	if (row % 2 != column % 2)
	{
		setcolor(WHITE); setfillstyle(SOLID_FILL, WHITE);
	}
	else
	{
		setcolor(YELLOW); setfillstyle(SOLID_FILL, YELLOW);
	}
	pieslice((column + 1) * SQSIZE + SQSIZE / 2, row * SQSIZE + SQSIZE / 2, 0,360, 4);
}
void HomeQueen(int row)
{
	setfillstyle(SOLID_FILL, BLUE) ;
	setcolor(BLUE);
	pieslice(SQSIZE / 2, row * SQSIZE + SQSIZE / 2, 0, 360, 4);
}
