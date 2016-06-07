import sys

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if test == '':
            continue
        (step_a, step_b, n) = test.split()
        step_a = int(step_a)
        step_b = int(step_b)
        n = int(n)
        for i in range(1, n+1):
            if i != 1:
                sys.stdout.write(' ')
            if i % step_a == 0 and i % step_b == 0:
                sys.stdout.write('FB')
            elif i % step_a == 0:
                sys.stdout.write('F')
            elif i % step_b == 0:
                sys.stdout.write('B')
            else:
                sys.stdout.write('%d' % i)
        print

