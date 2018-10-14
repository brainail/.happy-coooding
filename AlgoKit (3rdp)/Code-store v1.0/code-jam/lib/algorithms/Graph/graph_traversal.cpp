#include <stdio.h>
#include <stdlib.h>
struct linkedList
{
	struct node* head;
	struct node* tail;
	int size;
};
struct node
{
	int content;
	struct node* next;
};
void enqueue(int n,struct linkedList* q)
{
	struct node* new = malloc(sizeof(struct node));
	new->content = n;
	new->next = 0;
	if(!q->size)
	{
		q->head = new;
		q->tail = new;
	}
	else
	{
		q->tail->next = new;
		q->tail = new;
	}
	q->size++;

}
void push(int n,struct linkedList* s)
{
	struct node* new = malloc(sizeof(struct node));
	new->content = n;
	new->next = s->head;
	s->head = new;
	s->size++;
}
int pop(struct linkedList* s)
{
	struct node* t = s->head;
	int temp = t->content;
	s->head = s->head->next;
	s->size--;
	free(t);
	if(!s->size)
		s->tail = 0;
	return temp;
}
struct linkedList* newLinkedList()
{
	struct linkedList* r = malloc(sizeof(struct linkedList));
	r->size = 0;
	return r;
}
char isEmpty(struct linkedList* s)
{
	return !s->size;
}
void print(struct lminkedList l)
{
	struct node* t = l.head;
	while(t)
	{
		printf("%d ",t->content);
		t = t->next;
	}
}
void reGround(struct linkedList*l)
{
	l->head = 0;
	l->tail = 0;
	l->size = 0;
}
//Depth first search using stack and adjacency list
void dfsStackAdList(struct linkedList** adlist,int first,int n)
{
	int i;
	char* v = (char*)malloc(n);
	struct node* t;
	for(i=0;i<n;i++)
		v[i] = 0;
	struct linkedList* stack = newLinkedList();
	push(first,stack);
	while(!isEmpty(stack))
	{
		i = pop(stack);
		v[i] = 1;
		printf("%d ",i);
		t = adlist[i]->head;
		while(t)
		{
			if(!v[t->content])
				push(t->content,stack);
			t = t->next;
		}
	}
}
//Breadth first search using stack and adjacency list
void bfsAdList(struct linkedList** adlist,int first,int n)
{
	int i;
	char* v = (char*)malloc(n);
	struct node* t;
	for(i=0;i<n;i++)
		v[i] = 0;
	struct linkedList* queue = newLinkedList();
	enqueue(first,queue);
	while(!isEmpty(queue))
	{
		i = pop(queue);
		v[i] = 1;
		printf("%d ",i);
		t = adlist[i]->head;
		while(t)
		{
			if(!v[t->content])
				enqueue(t->content,queue);
			t = t->next;
		}
	}
}
//DFS for adjacency list using recursion
void dfsRecAdList(struct linkedList** adlist,int target,int n,char* v)
{
	struct node* t;
	v[target] = 1;
	printf("%d ",target);
	t = adlist[target]->head;
	while(t)
	{
		if(!v[t->content])
			dfsRecAdList(adlist,t->content,n,v);
		t = t->next;
	}
}
void dfsAdMatrixRec(char** map,int cur,char* v,int n)
{
	int i;
	v[cur] = 1;
	printf("%d ",cur);
	for(i=0;i<n;i++)
		if(map[cur][i]&&!v[i])
			dfsAdMatrixRec(map,i,v,n);
}
void dfsAdMatrixStack(char** map,int start,int n)
{
	int i,c;
	char* v = (char*)malloc(n);
	for(i=0;i<n;i++)
		v[i] = 0;
	struct linkedList* s = newLinkedList();
	push(start,s);
	while(!isEmpty(s))
	{
		c  = pop(s);
		v[c] = 1;
		printf("%d ",c);
		for(i=0;i<n;i++)
		{
			if(!v[i]&&map[c][i])
				push(i,s);
		}
	}
}
void bfsAdMatrixQueue(char** map,int start,int n)
{
	int i,c;
	char* v = (char*)malloc(n);
	for(i=0;i<n;i++)
		v[i] = 0;
	struct linkedList* q = newLinkedList();
	enqueue(start,q);
	while(!isEmpty(q))
	{
		c  = pop(q);
		v[c] = 1;
		printf("%d ",c);
		for(i=0;i<n;i++)
		{
			if(!v[i]&&map[c][i])
				enqueue(i,q);
		}
	}
}
int main()
{
	int i;
	struct linkedList** adList = (struct linkedList**) malloc(5*sizeof(struct linkedList*));
	for(i=0;i<5;i++)
		adList[i] = newLinkedList();
	char* v = (char*) malloc(5);
	char** map = (char**) malloc(5*sizeof(char*));
	for(i=0;i<5;i++)
		map[i] = (char*) malloc(5);
	map[0][1] = 1;
	map[0][3] = 1;
	map[3][4] = 1;
	map[3][2] = 1;
	map[4][2] = 1;
	bfsAdMatrixQueue(map,0,5);
	return 0;
}
