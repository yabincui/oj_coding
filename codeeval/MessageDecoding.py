import sys

def getString(bits, value):
    s = []
    i = 0
    while i < bits:
        if (value & 1) == 1:
            s.append('1')
        else:
            s.append('0')
        value >>= 1
        i += 1
    s.reverse()
    return ''.join(s)

with open(sys.argv[1], 'r') as test_cases:
    for test in test_cases:
        test = test.strip()
        if len(test) == 0:
            continue
        keys = {}
        i = 0
        cur_bits = 1
        cur_value = 0
        while i < len(test):
            c = test[i]
            if c in '01':
                break
            s = getString(cur_bits, cur_value)
            keys[s] = c
            #print 'keys[%s] = %s, cur_bits = %d, cur_value = %d' % (s, c, cur_bits, cur_value)
            cur_value += 1
            if cur_value == (1 << cur_bits) - 1:
                cur_bits += 1
                cur_value = 0
            i += 1
        while i < len(test):
            bits = 0
            k = i
            while k <= i + 2:
                bits = (bits << 1)
                if test[k] == '1':
                    bits += 1
                k += 1
            i += 3
            if bits == 0:
                break
            while i < len(test):
                key = test[i : i + bits]
                i += bits
                if not ('0' in key):
                    break
                c = keys[key]
                sys.stdout.write(c)
        print
