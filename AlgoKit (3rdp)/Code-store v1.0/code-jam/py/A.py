import sys
import math

if __name__ == "__main__":
    _i = open("/Users/lwy08/Downloads/A-large.in", "r")
    T = int(_i.readline())
    for _t in xrange(T):
        line = _i.readline().split()

        print "Case #%d: %s" % (_t + 1, ' '.join(map(str, required)))
    _i.close()
