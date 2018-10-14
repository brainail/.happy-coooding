#define MAX 1000 // adjust this properly (the max size of your set)

/* UNION-FIND library */
int p[MAX],rank[MAX];

// make a new set ID x
void make_set(int x) {
	p[x] = x;
	rank[x] = 0;
}

// don't call link directly, rather, use union_set
void link(int x,int y) {
	if (rank[x] > rank[y])
		p[y] = x;
	else {
		p[x] = y;
		if (rank[x] == rank[y])
			rank[y] = rank[y] + 1;
	}
}

// find the set ID of item x
int find_set(int x) {
	if (x != p[x])
		p[x] = find_set(p[x]);
	return p[x];
}

// union two set containing item x and item y
// see, this one calls find_set first!
void union_set(int x,int y) {
	link(find_set(x),find_set(y));
}
