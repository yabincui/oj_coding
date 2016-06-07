
import sys

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        words = test.split()
        for i in range(len(words)-1, -1, -1):
            if i != len(words) - 1:
                sys.stdout.write(' ')
            sys.stdout.write(words[i])
        print
