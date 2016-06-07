import sys

with open(sys.argv[1], 'r') as f:
    lines = f.readlines()
    n = int(lines[0])
    pairs = []
    for i in range(1, len(lines)):
        pairs.append((len(lines[i]), lines[i]))
    result = sorted(pairs, key = lambda value : value[0])
    i = 0
    while i < n:
        pos = len(result) - 1 - i
        sys.stdout.write(result[pos][1])
        i += 1
