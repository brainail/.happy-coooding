#include<stdio.h>
#include<conio.h>
#include<graphics.h>

void main()
{
	int gd = DETECT,gm;
	initgraph(&gd,&gm,"E:\\TC\\BGI");
	setbkcolor(BLUE);
	setcolor(RED);
	rectangle(100,100,400,300);
	setfillstyle(SOLID_FILL,GREEN);
	floodfill(120,120,RED);
	circle(250,200,50);
	setfillstyle(SOLID_FILL,RED);
	floodfill(250,200,RED);
	getch();
	closegraph();
}