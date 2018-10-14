#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import time
import math

if __name__ == '__main__':
    t0 = time.time()
    _i = sys.stdin
    _o = sys.stdout
    T = int(_i.readline().strip())
    for _t in xrange(T):
        line = _i.readline().strip().split()

        N, M = line
        N = int(N)
        M = int(M)
        exists = []
        for i in xrange(N):
            exists.append(_i.readline().strip())
        need = set()
        for i in xrange(M):
            line = _i.readline().strip().split('/')
            path = line[1:]
            accum = '/'
            for a_dir in path:
                accum += a_dir + '/'
                need.add(accum[:-1])

        num_mkdir = 0
        for p in need:
            if p not in exists:
                num_mkdir += 1

        result = 'Case #%d: %d' % (_t + 1, num_mkdir)
        print >> _o, result
    _i.close()
    _o.close()
    #print >> sys.stderr, '%lf seconds' % (time.time() - t0)
