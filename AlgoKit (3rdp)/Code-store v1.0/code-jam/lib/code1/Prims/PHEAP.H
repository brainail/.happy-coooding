/* PHEAP.H */

#ifndef _PHEAP_H
#define _PHEAP_H
#include<stdlib.h>

int hn, heaplimit, *heap;
int (*CMP) (int ,int );

void heaperror(int i)
{
	switch(i)
	{
		case 1:
		printf("\nHeap Error 01: Heap Empty\n");
		break;
		case 2:
		printf("\nHeap Error 02: Heap Full\n");
		break;
		default:
		printf("\nHeap Error 03: Unknown\n");
		break;
	}
	exit(0);
}

void heapinit(int n,int (*C) (int ,int ))
{
	heap=new int[n];
	hn=0, CMP=C, heaplimit=n;
}

void adjust(int i)
{
	int p,c,ele=heap[i];
	p=i, c=p*2;
	while(c<=hn)
	{
		if(c<hn && CMP(heap[c+1],heap[c])) c++;
		if(CMP(heap[c],ele))
		{
			heap[p]=heap[c];
			p=c, c=p*2;
		}
		else break;
	}
	heap[p]=ele;
}

void heapify()
{
	int i;
	for(i=hn/2;i>0;i--) adjust(i);
}

int deleteroot()
{
	int ele=heap[1];
	if(!hn) heaperror(2);
	heap[1]=heap[hn--];
	return ele;
}

int heapempty()
{
	return (hn==0);
}

void heapinsert(int ele)
{
	int c=++hn, p=c/2;
	if(hn==heaplimit) heaperror(1);
	heap[hn]=ele;
	while(p>0)
	{
		if(CMP(ele,heap[p]))
		{
			heap[c]=heap[p];
			c=p, p=c/2;
		}
		else break;
	}
	heap[c]=ele;
}

int extractroot()
{
	int ele=deleteroot();
	adjust(1);
	return ele;
}

void heapassign(int ele)
{
	if(hn==heaplimit) heaperror(1);
	heap[++hn]=ele;
}

int heapvalue(int i)
{
	return heap[i];
}

#endif

