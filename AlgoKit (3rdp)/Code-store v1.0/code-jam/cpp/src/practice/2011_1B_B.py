#!/usr/bin/env python
from __future__ import division
from sys import stdin

def solve(D, C, V):
    def can(t):
        pos = float("-inf")
        for p,v in V:
            pos = max(pos + D, p - t) + (v - 1)*D
            if pos > p + t: return False
        return True

    lo, hi = 0, D*sum(v for p,v in V)
    for _ in range(50):
        mid = (lo + hi)/2
        if can(mid): hi = mid
        else: lo = mid
    return (hi + lo)/2

T = int(stdin.readline())
for t in range(T):
    C, D = map(int, stdin.readline().split())
    V = [tuple(map(int, stdin.readline().split())) for _ in range(C)]
    print("Case #" + str(t + 1) + ": " + str(solve(D, C, V)))
