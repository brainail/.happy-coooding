class Graph {
	
	public Graph() {
		setSize(MAXV, MAXE);
	}
	
	public Graph(int V, int E) {
		setSize(V, E);	
	}
	
	public void setSize(int V, int E) {
		next = new int [E];
		last = new int [V];
		cap = new int [E];
		from = new int [E];
		to = new int [E];
		rev = new int [E];
		Arrays.fill(next, -1);
		Arrays.fill(last, -1);
		this.V = V;
		this.E = 0;
	}
	
	public int getV() {
		return V;
	}
	
	public int getE() {
		return E;
	}
	
	public void addEdge(int start, int finish, int capOf) {
		add(start, finish, capOf, E + 1);
		add(finish, start, 0, E - 1);
	}
	
	public void add(int start, int finish, int capOf, int revOf) {
		next[E] = last[start];
		last[start] = E;
		cap[E] = capOf;
		rev[E] = revOf;
		from[E] = start;
		to[E] = finish;
		++ E;
	}
	
	// The Ford Fulkerson algorithm
	public int maxFlowFordFulkerson(int s, int t) {
		int resultFlow = 0;
		
		was = new boolean [V];
		
		while(true) {
			Arrays.fill(was, false);
			int curFlow = findFlowFordFulkerson(s, t, INF);
			if(curFlow == 0)
				break;
			resultFlow += curFlow;
		}
		return resultFlow;
	}
	
	private int findFlowFordFulkerson(int v, int t, int curFlow) {
		if(v == t)
			return curFlow;
		was[v] = true;
		for(int i = last[v]; i != -1; i = next[i])
			if(!was[to[i]] && cap[i] > 0) {
				int resultFlow = findFlowFordFulkerson(to[i], t, Math.min(curFlow, cap[i]));
				if(resultFlow > 0) {
					cap[i] -= resultFlow;
					cap[rev[i]] += resultFlow;
					return resultFlow;
				}
			}
		return 0;
	}
	
	// The Edmonds Karp algorithm
	public int maxFlowEdmondsKarp(int s, int t) {
		int resultFlow = 0;
		
		// queue for vertex
		int [] q = new int [V];
		
		// previous edge for vertex
		int [] p = new int [V];
		
		while(true) {
			int cq = 0, nq = 0;
			q[++ nq] = s;
			Arrays.fill(p, -1);
			
			while(cq < nq && p[t] == -1) {
				for(int i = last[q[cq ++]]; i != -1; i = next[i])
					if(p[to[i]] == -1 && cap[i] > 0) {
						p[to[i]] = i;
						q[nq ++] = to[i];
					}
			}
			
			if(p[t] == -1) 
				break;
			
			int curFlow = INF;
			
			for(int v = t; v != s; v = from[p[v]])
				if(cap[p[v]] < curFlow)
					curFlow = cap[p[v]];
			
			for(int v = t; v != s; v = from[p[v]]) {
				cap[p[v]] -= curFlow;
				cap[rev[p[v]]] += curFlow;
			}
			
			resultFlow += curFlow;
		}
		
		return resultFlow;
	}
	
	// next edge in the list of edges
	public int [] next;
	
	// last edge for vertex
	public int [] last;
	
	// capability of edges
	public int [] cap;
	
	// reverse edges
	public int [] rev;
	
	// begin and end of edge
	public int [] from;
	public int [] to;
	
	// visited the vertex or not
	public boolean [] was;
	
	// size of graph
	private int V, E;
	
	final static int MAXV = 100000;
	final static int MAXE = 200000;
	final static int INF = 2000000000;
}
