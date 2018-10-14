import sys

inputFile = open("input.txt", 'r')
# inputFile = open(sys.argv[1], 'r')

for expression in inputFile:
    expression = expression.strip()

    if len(expression) == 0:
        continue

    ops = []
    for ch in reversed(expression.split(' ')):
        if ch.isdigit():
            ops.append(ch)
        else:
            opA = float(ops.pop())
            opB = float(ops.pop())

            if ch == '+':
                rtv = opA + opB
            elif ch == '*':
                rtv = opA * opB
            else:
                rtv = opA / opB

            ops.append(rtv)

    print(int(ops.pop()))

inputFile.close()