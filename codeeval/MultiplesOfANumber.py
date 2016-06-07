import sys

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if test == '':
            continue
        nums = test.split(',')
        x = int(nums[0])
        n = int(nums[1])
        a = x & ~(n - 1)
        b = n if x & (n - 1) else 0
        print '%d' % (a + b)
