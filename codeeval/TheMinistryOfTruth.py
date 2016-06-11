# I think the required solution doesn't match requirement:
#  The required solution finds substr instead of sub sequence, but the requirement
#  hints us to find sub sequence.
# For example, I thought BCD:BD should match. But it doesn't.

import sys

def remove_extra_spaces(s):
    result = []
    cur = []
    for i in range(len(s)):
        if s[i] == ' ':
            if i > 0 and s[i - 1] == ' ':
                continue
            if len(cur) > 0:
                result.append(cur)
            cur = []
        else:
            cur.append(s[i])
    if len(cur) > 0:
        result.append(cur)
    return result

def match_block(a, b):
#    j = 0
#    for c in b:
#        while j < len(a) and a[j] != c:
#            j += 1
#        if j == len(a):
#            return False
#        j += 1
#    return True
    return ''.join(b) in ''.join(a)

def mark_block(a, b):
#    j = 0
#    for c in b:
#        while j < len(a) and a[j] != c:
#            a[j] = '_'
#            j += 1
#        j += 1
#    while j < len(a):
#        a[j] = '_'
#        j += 1
    t = ''.join(a).index(''.join(b))
    for i in range(len(a)):
        if i < t or i >= t + len(b):
            a[i] = '_'

    

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        (a, b) = test.split(';')
        a = remove_extra_spaces(a)
        b = remove_extra_spaces(b)
        j = 0
        ok = True
        for b_block in b:
            while j < len(a) and not match_block(a[j], b_block):
                a[j] = '_' * len(a[j])
                j += 1
            if j == len(a):
                ok = False
                break
            mark_block(a[j], b_block)
            j += 1
        if ok:
            while j < len(a):
                a[j] = '_' * len(a[j])
                j += 1
            out = []
            for block in a:
                out.append(''.join(block))
            out = ' '.join(out)
            print out
        else:
            print 'I cannot fix history'

