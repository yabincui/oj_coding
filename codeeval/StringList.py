import sys

first = False


def enumString(s, index, num, chars):
    global first
    if index == num:
        s = ''.join(s)
        if first:
            first = False
        else:
            sys.stdout.write(',')
        sys.stdout.write(s)
        return
    for c in chars:
        s[index] = c
        enumString(s, index + 1, num, chars)


with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        (num, s) = test.split(',')
        num = int(num)
        chars = {}
        for c in s:
            chars[c] = True
        chars = sorted(chars.keys())
        first = True
        s = ['?' for x in range(num)]
        enumString(s, 0, num, chars)
        print

