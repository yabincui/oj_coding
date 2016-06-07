import sys

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if test == '':
            continue
        nums = test.split(',')
        n = int(nums[0])
        p1 = int(nums[1]) - 1
        p2 = int(nums[2]) - 1
        a = (n >> p1) & 1
        b = (n >> p2) & 1
        if a == b:
            print 'true'
        else:
            print 'false'
