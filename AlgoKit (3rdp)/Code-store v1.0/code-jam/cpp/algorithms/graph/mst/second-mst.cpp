// The second Miniumn Spaning Tree. You can also find the K-th MST.
// Algorithm:
// 1. Find MST T, O(VlogV + E).
// 2. Find the min sum weight spaning tree in the neighbour set. 
//    That is the second mst.
// 2.1 Enum every edge u-v which is not in MST. Add this edge to MST 
//     will cause a cycle. We need to find the max weight edge from 
//     u to v in the current mst. It is like the K-Degree MST problem.
