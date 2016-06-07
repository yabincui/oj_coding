import sys

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if test == '':
            continue
        words = test.split(';')
        a = words[0]
        b = words[1]
        m = len(a)
        n = len(b)
        #print 'a=%s, m = %d\nb=%s, n = %d' % (a, m, b, n)
        s = []
        for i in range(0, m):
            s.append(range(0, n))
            for j in range(0, n):
                if i == 0 or j == 0:
                    s[i][j] = 1 if (a[i] == b[j]) else 0
                    if i > 0:
                        s[i][j] = max(s[i][j], s[i-1][j])
                    elif j > 0:
                        s[i][j] = max(s[i][j], s[i][j-1])
                else:
                    t1 = s[i-1][j-1] if (a[i] != b[j]) else (s[i-1][j-1] + 1)
                    s[i][j] = max(t1, s[i-1][j], s[i][j-1])
                #print 's[%d][%d] = %d' % (i, j, s[i][j])
        prev_list = []
        i = m - 1
        j = n - 1
        while i > 0 and j > 0:
            if s[i-1][j] == s[i][j]:
                i -= 1
            elif s[i][j-1] == s[i][j]:
                j -= 1
            elif a[i] == b[j] and s[i-1][j-1] + 1 == s[i][j]:
                prev_list.append(a[i])
                i -= 1
                j -= 1
        while s[i][j] != 0:
            if a[i] == b[j]:
                prev_list.append(a[i])
                break
            i = max(i - 1, 0)
            j = max(j - 1, 0)
        prev_list.reverse()
        s = ''.join(prev_list) 
        print s

