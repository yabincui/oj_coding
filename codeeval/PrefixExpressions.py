import sys

def evaluate(words, index):
    if words[index] == '+':
        (a, index) = evaluate(words, index + 1)
        (b, index) = evaluate(words, index)
        return (a+b, index)
    elif words[index] == '*':
        (a, index) = evaluate(words, index + 1)
        (b, index) = evaluate(words, index)
        return (a*b, index)
    elif words[index] == '/':
        (a, index) = evaluate(words, index + 1)
        (b, index) = evaluate(words, index)
        return (float(a)/float(b), index)
    else:
        return (int(words[index]), index + 1)

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        line = test.strip()
        if line == '':
            continue
        words = line.split()
        (result,next_index) = evaluate(words, 0)
        print int(result)

