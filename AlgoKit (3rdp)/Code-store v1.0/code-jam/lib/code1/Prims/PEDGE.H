/* PEDGE.H */

#ifndef _PEDGE_H
#define _PEDGE_H

#ifndef NIL
#define NIL 0
#endif

struct list {
	int dst, wt, next;
} *edgelist;

int *nodehead, edgecount, edgelimit, nodelimit, cnext;

void edgelisterror(int i)
{
	switch(i)
	{
		case 1:
		printf("\nEdge List Error 1: Node Limit Cross\n");
		break;
		case 2:
		printf("\nEdge List Error 2: Node Limit Cross\n");
		break;
		case 3:
		printf("\nEdge List Error 3: Node Limit must be greater then 0\n");
		break;
		case 4:
		printf("\nEdge List Error 4: Node Limit must be greater then 0\n");
		break;
		default:
		printf("\nEdge List Error 5: Unknown\n");
		break;
	}
	exit(0);
}

void edgeinit(int n,int e)
{
	int i;
	if(n<=0) edgelisterror(3);
	if(e<=0) edgelisterror(4);
	edgecount=NIL, edgelimit=e, nodelimit=n;
	if(n>NIL) nodehead=new int[n+1];
	if(e>NIL) edgelist=new list[e+1];
	for(i=1;i<=n;i++) nodehead[i]=NIL;
}

void linkwithsource(int src)
{
	int j=nodehead[src];
	if(j==NIL)
		nodehead[src]=edgecount;
	else
	{
		while(edgelist[j].next) j=edgelist[j].next;
		edgelist[j].next=edgecount;
	}
}

void insertedge(int src,int dst,int wt)
{
	if(src>nodelimit || dst>nodelimit) edgelisterror(1);
	if(edgecount==edgelimit) edgelisterror(2);
	edgecount++;
	edgelist[edgecount].wt=wt;
	edgelist[edgecount].dst=dst;
	edgelist[edgecount].next=NIL;
	linkwithsource(src);
}

void setsource(int i)
{
	cnext=nodehead[i];
}

int getnextedge(int *dst,int *wt)
{
	int next=cnext;
	*wt=edgelist[cnext].wt;
	*dst=edgelist[cnext].dst;
	cnext=edgelist[cnext].next;
	return next;
}

#endif