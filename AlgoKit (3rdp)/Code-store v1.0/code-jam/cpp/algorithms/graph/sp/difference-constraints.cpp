// System of difference constraints problem.
// This problem can be converted to shortest path problem
// using bellman-ford algorithm.

Problem description:
Given 
			X1 - X2 <= 0
			X1 - X5 <= -1
			X2 - X5 <= 1
			X3 - X1 <= 5
			X4 - X1 <= 4
			X4 - X3 <= -1
			X5 - X3 <= -3
			X5 - X4 <= -3
You're required to find a feasible solution.


In shortest path problem, the relax operation is:
	d(v) <= d(u) + w(u, v)

We can assume there is a virtual point X0, satisfying:
			X1 - X0 <= 0
			X2 - X0 <= 0
			X3 - X0 <= 0
			X4 - X0 <= 0
			X5 - X0 <= 0

For X[v] - X[u] <= C, we can add a edge from u to v. Using 
Bellman-Ford, we can get a feasible solution.

BE CAREFUL: In this solution, X[i] is the MAX value it can rearch.
It is because at first X[i] is set to +OO. When doing relax, it is 
decreasing until there is no more relax operation. So X[i] is the
MAX value to itself.


When you want to get X[i]'s MIN value, you can just do it in a 
reverse way. 
			d(v) >= d(u) + w(u, v) 
			i.e. d(v) - d(u) >= w(u, v)
You can use bellman-ford to calculate the longest path. Thus X[i] 
is the MIN value.(X[i] is set to -OO initially)
