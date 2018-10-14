/* Red-Black Tree with Insert and Order Statistics */

# include <stdio.h>

typedef struct{
  int key,size,color;
  int left,right,p;
}RBNode;

const int red=0,black=1,nil=-1;
int root;
RBNode r[10000];

void LeftRotate(int x)
{
  int y=r[x].right;
  r[x].right=r[y].left;
  if(r[y].left!=nil) r[r[y].left].p=x;
  r[y].p=r[x].p;
  if(r[x].p==nil) root=y;
  else if(x==r[r[x].p].left) r[r[x].p].left=y;
  else r[r[x].p].right=y;
  r[y].left=x;
  r[x].p=y;
  r[y].size=r[x].size;
  r[x].size=1;
  if(r[x].left!=nil) r[x].size+=r[r[x].left].size;
  if(r[x].right!=nil) r[x].size+=r[r[x].right].size;
}

void RightRotate(int x)
{
  int y=r[x].left;
  r[x].left=r[y].right;
  if(r[y].right!=nil) r[r[y].right].p=x;
  r[y].p=r[x].p;
  if(r[x].p==nil) root=y;
  else if(x==r[r[x].p].right) r[r[x].p].right=y;
  else r[r[x].p].left=y;
  r[y].right=x;
  r[x].p=y;
  r[y].size=r[x].size;
  r[x].size=1;
  if(r[x].left!=nil) r[x].size+=r[r[x].left].size;
  if(r[x].right!=nil) r[x].size+=r[r[x].right].size;

}

void TreeInsert(int z)
{
  int x,y;
  y=nil;
  x=root;
  while(x!=nil){
    y=x;
    r[x].size++;
    if(r[z].key<r[x].key) x=r[x].left;
    else x=r[x].right;
  }
  r[z].p=y;
  if(y==nil) root=z;
  else if(r[z].key<r[y].key) r[y].left=z;
  else r[y].right=z;
}

void RBInsert(int x)
{
  int y;
  TreeInsert(x);
  r[x].color=red;
  while(x!=root && r[r[x].p].color==red){
    if(r[x].p==r[r[r[x].p].p].left){
      y=r[r[r[x].p].p].right;
      if(r[y].color==red){
	r[r[x].p].color=black;
	r[y].color=black;
	r[r[r[x].p].p].color=red;
	x=r[r[x].p].p;
      }
      else{
	if(x==r[r[x].p].right){
	  x=r[x].p;
	  LeftRotate(x);
	}
	r[r[x].p].color=black;
	r[r[r[x].p].p].color=red;
	RightRotate(r[r[x].p].p);
      }
    }
    else{
      y=r[r[r[x].p].p].left;
      if(r[y].color==red){
	r[r[x].p].color=black;
	r[y].color=black;
	r[r[r[x].p].p].color=red;
	x=r[r[x].p].p;
      }
      else{
	if(x==r[r[x].p].left){
	  x=r[x].p;
	  RightRotate(x);
	}
	r[r[x].p].color=black;
	r[r[r[x].p].p].color=red;
	LeftRotate(r[r[x].p].p);
      }
    }
  }
  r[root].color=black;
}

int OSRank(int x)
{
  int re=1;
  int y=x;
  if(r[x].left!=nil) re=r[r[x].left].size;
  while(y!=root){
    if(y==r[r[y].p].right){
      re++;
      if(r[r[y].p].left!=nil) re+=r[r[r[y].p].left].size;
    }
    y=r[y].p;
  }
  return re;
}

int main(void)
{
  int n,k;
  int key,maxrow,maxrank,rank;
  int i,j;
  scanf("%d%d",&n,&k);
  maxrow=-1;
  for(i=0;i<k;i++){
    rank=0;
    root=0;
    scanf("%d",&key);
    key=n-key;
    r[root].key=key;
    r[root].color=black;
    r[root].size=1;
    r[root].p=r[root].left=r[root].right=nil;
    for(j=1;j<n;j++){
      scanf("%d",&key);
      key=n-key;
      r[j].key=key;
      r[j].size=1;
      r[j].left=r[j].right=nil;
      RBInsert(j);
      rank+=OSRank(j)-1;
    }
    if(maxrow==-1 || rank>maxrank){
      maxrow=i;
      maxrank=rank;
    }
  }
  printf("%d\n",1+maxrow);
  return 0;
}
