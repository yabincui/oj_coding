import sys

STAR=','

def preprocess(s, no_star):
    global STAR
    l = []
    i = 0
    while i < len(s):
        if s[i] == '\\':
            i += 1
        elif s[i] == '*':
            if no_star or (i > 0 and s[i-1] == '\\'):
                l.append('*')
            else:
                l.append(STAR)
            i += 1
        else:
            l.append(s[i])
            i += 1
    return ''.join(l)
            

def isMatch(s, t):
    s = preprocess(s, True)
    t = preprocess(t, False)
    m = len(s)
    n = len(t)
    dp = [[False for x in range(n + 1)] for y in range(m + 1)]
    for i in range(0, m+1):
        dp[i][0] = True
    for i in range(1, n+1):
        if t[i - 1] == '\\':
            continue
        elif t[i - 1] == STAR:
            last_match = 0
            while last_match <= m:
                if dp[last_match][i-1]:
                    break
                last_match += 1
            if last_match == m + 1:
                return False
            while last_match <= m:
                dp[last_match][i] = True
                last_match += 1
        else:
            for j in range(1, m + 1):
                if dp[j-1][i-1] and s[j-1] == t[i-1]:
                    dp[j][i] = True
    for j in range(0, m+1):
        if dp[j][n]:
            return True
    return False

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        (s, t) = test.split(',')
        result = isMatch(s, t)
        print 'true' if result else 'false'
