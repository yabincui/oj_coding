import sys

first = False

def enumerateS(s, last_count, output):
    if last_count == 0:
        global first
        if first:
            first = False
        else:
            sys.stdout.write(',')
        sys.stdout.write(output)
        return
    for i in range(0, len(s)):
        if s[i][1] != 0:
            s[i][1] -= 1
            enumerateS(s, last_count - 1, output + s[i][0])
            s[i][1] += 1

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        word = test.strip()
        word = sorted(word)
        s = []
        for i in range(0, len(word)):
            if i != 0 and word[i] == word[i - 1]:
                s[-1][1] += 1
            else:
                s.append([word[i], 1])
        first = True
        enumerateS(s, len(word), '')
        print

